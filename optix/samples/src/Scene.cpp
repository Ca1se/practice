#include "Scene.h"

#include <iostream>
#include <format>
#include <cmath>

#include <channel_descriptor.h>
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <tiny_gltf.h>

#include "Util.h"

namespace
{

struct
{
    cudaTextureAddressMode constexpr wrappingMode(int tinygltf_mode)
    {
        switch (tinygltf_mode) {
        case TINYGLTF_TEXTURE_WRAP_CLAMP_TO_EDGE:
            return cudaAddressModeClamp;
        case TINYGLTF_TEXTURE_WRAP_MIRRORED_REPEAT:
            return cudaAddressModeMirror;
        default:
            std::cerr << std::format("Unsupported GLTF wrapping mode '{}', using the default wrapping mode 'Wrap'", tinygltf_mode) << std::endl;
            return cudaAddressModeWrap;
        }
    }

    cudaTextureFilterMode constexpr filterMode(int tinygltf_mode)
    {
        switch (tinygltf_mode) {
        case TINYGLTF_TEXTURE_FILTER_NEAREST:
            return cudaFilterModePoint;
        default:
            std::cerr << std::format("Unsupported GLTF filter mode '{}', using the default filter mode 'Linear'", tinygltf_mode) << std::endl;
            return cudaFilterModeLinear;
        }
    }

    PbrMaterial::AlphaMode constexpr alphaMode(const std::string& tinygltf_mode)
    {
        PbrMaterial::AlphaMode alpha_mode = PbrMaterial::ALPHA_MODE_OPAQUE;

        if (tinygltf_mode == "MASK") {
            return PbrMaterial::ALPHA_MODE_MASK;
        } else if (tinygltf_mode == "BLEND") {
            return PbrMaterial::ALPHA_MODE_BLEND;
        } else if (tinygltf_mode != "OPAQUE"){
            std::cerr << std::format("Unsupported GLTF alpha mode '{}', using the default alpha mode 'OPAQUE'", tinygltf_mode) << std::endl;
        }

        return alpha_mode;
    }
} g_mapper;

template <typename TextureInfo>
void loadTextureInfo(const Scene& scene, const TextureInfo& gltf_tex, PbrMaterial::Texture& tex)
{
    tex.texture        = 0;
    tex.texcoord_index = 0;
    if (gltf_tex.index >= 0) {
        tex.texture        = scene.getTextures()[gltf_tex.index];
        tex.texcoord_index = gltf_tex.texCoord;
        if (tex.texcoord_index >= 1) {
            std::cerr << "\t\tMultiple texcoords are not supported" << std::endl;
            tex.texcoord_index = 0;
        }

        float2& offset   = tex.texcoord_offset;
        float2& rotation = tex.texcoord_rotation;
        float2& scale    = tex.texcoord_scale;
        if (const auto& itr = gltf_tex.extensions.find("KHR_texture_transform"); itr != gltf_tex.extensions.end()) {
            if (itr->second.Has("offset")) {
                auto offset_val = itr->second.Get("offset");
                offset = make_float2(static_cast<float>(offset_val.Get(0).GetNumberAsDouble()),
                                     static_cast<float>(offset_val.Get(1).GetNumberAsDouble()));
            }
            if (itr->second.Has("rotation")) {
                auto rotation_val = static_cast<float>(itr->second.Get("rotation").GetNumberAsDouble());
                rotation = make_float2(sinf(rotation_val), cosf(rotation_val));
            }
            if (itr->second.Has("scale")) {
                auto scale_val = itr->second.Get("scale");
                scale = make_float2(static_cast<float>(scale_val.Get(0).GetNumberAsDouble()),
                                    static_cast<float>(scale_val.Get(1).GetNumberAsDouble()));
            }
        }
    }
}

}

Scene::Scene()
{
    cudaFree(nullptr);
}

Scene::~Scene() noexcept
{
    try {
        
    } catch(std::exception& e) {
        std::cerr << std::format("Scene::~Scene(): cought a exception: {}", e.what()) << std::endl;
    }
}

void Scene::addImage(int32_t width,
                     int32_t height,
                     int32_t bits_per_component,
                     const void *data)
{
    static constexpr int32_t components_num = 4;

    int32_t pitch = sizeof(uint8_t) * components_num * width;
    cudaChannelFormatDesc channel_desc = cudaCreateChannelDesc<uchar4>();

    if(bits_per_component == 16) {
        pitch = sizeof(uint16_t) * components_num * width;
        channel_desc = cudaCreateChannelDesc<ushort4>();
    }else if(bits_per_component != 8) {
        throw std::runtime_error{ EXCEPTION_MSG("Unsupported bits per component") };
    }

    cudaArray_t cuda_array = nullptr;
    CUDA_CHECK(cudaMallocArray(&cuda_array, &channel_desc, width, height));
    CUDA_CHECK(cudaMemcpy2DToArray(cuda_array, 0, 0, data, pitch, pitch, height, cudaMemcpyHostToDevice));

    m_images.push_back(cuda_array);
}

void Scene::addTexture(cudaTextureAddressMode address_s,
                       cudaTextureAddressMode address_t,
                       cudaTextureFilterMode  filter_mode,
                       int32_t                image_index)
{
    cudaResourceDesc res_desc = {
        .resType = cudaResourceTypeArray,
        .res = { .array = { .array = m_images[image_index] } }
    };

    cudaTextureDesc tex_desc = {
        .addressMode         = { address_s, address_t },
        .filterMode          = filter_mode,
        .readMode            = cudaReadModeNormalizedFloat,
        .sRGB                = 0,
        .borderColor         = { 1.0f },
        .normalizedCoords    = 1,
        .maxAnisotropy       = 1,
        .mipmapFilterMode    = cudaFilterModePoint,
        .minMipmapLevelClamp = 0,
        .maxMipmapLevelClamp = 99,
    };

    cudaTextureObject_t tex = 0;
    CUDA_CHECK(cudaCreateTextureObject(&tex, &res_desc, &tex_desc, nullptr));
    m_textures.push_back(tex);
}

void Scene::cleanup()
{
    for (auto texture: m_textures)
        CUDA_CHECK(cudaDestroyTextureObject(texture));
    for (auto image: m_images)
        CUDA_CHECK(cudaFreeArray(image));
    m_cameras.clear();
    m_meshes.clear();
    m_materials.clear();
    m_images.clear();
    m_textures.clear();
    m_buffers.clear();
    m_aabb.invalidate();
}

void loadGltfScene(Scene& scene, const std::string &filename)
{
    scene.cleanup();

    std::cerr << std::format("Loading GLTF file {}", filename) << std::endl;

    std::string full_file_path = getModelPath(filename);

    tinygltf::Model model;
    tinygltf::TinyGLTF gltf_loader;
    std::string err;
    std::string warning;

    bool ok;
    if (filename.ends_with(".gltf")) {
        ok = gltf_loader.LoadASCIIFromFile(&model, &err, &warning, full_file_path);
    }else if (filename.ends_with(".glb")) {
        ok = gltf_loader.LoadBinaryFromFile(&model, &err, &warning, full_file_path);
    }else {
        throw std::runtime_error{ EXCEPTION_MSG(std::format("unrecognized filename: {}, the filename must end with '.gltf' or '.glb'", filename)) };
    }

    if (!ok)
        throw std::runtime_error{ EXCEPTION_MSG(std::format("failed to load GLTF file {}: {}", filename, err)) };

    if (!warning.empty())
        std::cerr << std::format("\tGLTF warning (when loading file {}): {}", filename, warning) << std::endl;

    for (const auto& buffer: model.buffers) {
        size_t byte_size = buffer.data.size();
        std::cerr << std::format("\tLoading buffer '{}'\n"
                                 "\t\tbyte size: {}\n"
                                 "\t\turi: {}",
                                 buffer.name,
                                 byte_size,
                                 buffer.uri) << std::endl;
        scene.addBuffer(buffer.data.data(), byte_size);
    }
    
    for (const auto& image: model.images) {
        std::cerr << std::format("\tLoading image '{}'\n"
                                 "\t\twidth: {}\n"
                                 "\t\theight: {}\n"
                                 "\t\tcomponents: {}\n"
                                 "\t\tbits: {}",
                                 image.name,
                                 image.width,
                                 image.height,
                                 image.component,
                                 image.bits) << std::endl;
        assert(image.component == 4 && (image.bits == 8 || image.bits == 16));
        scene.addImage(image.width,
                       image.height,
                       image.bits,
                       image.image.data());
    }

    for (const auto& texture: model.textures) {
        std::cerr << std::format("\tLoading texture '{}'", texture.name) << std::endl;
        if (texture.sampler == -1) {
            scene.addTexture(cudaAddressModeWrap, cudaAddressModeWrap, cudaFilterModeLinear, texture.source);
            continue;
        }
        const auto& sampler  = model.samplers[texture.sampler];
        const auto address_s = g_mapper.wrappingMode(sampler.wrapS);
        const auto address_t = g_mapper.wrappingMode(sampler.wrapT);
        const auto filter    = g_mapper.filterMode(sampler.minFilter);
        scene.addTexture(address_s, address_t, filter, texture.source);
    }

    for (const auto& material: model.materials) {
        std::cerr << std::format("\tLoading PBR material '{}'", material.name) << std::endl;

        PbrMaterial pbr_material;
        pbr_material.back_culling = (material.doubleSided == false);
        pbr_material.alpha_mode   = g_mapper.alphaMode(material.alphaMode);
        pbr_material.alpha_cutoff = static_cast<float>(material.alphaCutoff);

        /*
        // base color
        const auto& base_color_itr = material.values.find("baseColorFactor");
        if (base_color_itr != material.values.end()) {
            const tinygltf::ColorValue& base_color = base_color_itr->second.ColorFactor();
            pbr_material.base_color = make_float4(static_cast<float>(base_color[0]),
                                                  static_cast<float>(base_color[1]),
                                                  static_cast<float>(base_color[2]),
                                                  static_cast<float>(base_color[3]));
            std::cerr << std::format("\t\tBase color: ({}, {}, {}, {})",
                                     pbr_material.base_color.x,
                                     pbr_material.base_color.y,
                                     pbr_material.base_color.z,
                                     pbr_material.base_color.w) << std::endl;
        } else {
            std::cerr << "\t\tUsing default base color" << std::endl;
        }
        // emissive factor
        const auto& emissive_factor_itr = material.additionalValues.find("emissiveFactor");
        if (emissive_factor_itr != material.additionalValues.end()) {
            const tinygltf::ColorValue& emissive_factor = emissive_factor_itr->second.ColorFactor();
            pbr_material.emissive_factor = make_float3(static_cast<float>(emissive_factor[0]),
                                                       static_cast<float>(emissive_factor[1]),
                                                       static_cast<float>(emissive_factor[2]));
            std::cerr << std::format("\t\tEmissive factor: ({}, {}, {})",
                                     pbr_material.emissive_factor.x,
                                     pbr_material.emissive_factor.y,
                                     pbr_material.emissive_factor.z) << std::endl;
        } else {
            std::cerr << "\t\tUsing default emissive factor" << std::endl;
        }
        // metallic
        const auto& metallic_itr = material.values.find("metallicFactor");
        if (metallic_itr != material.values.end()) {
            pbr_material.metallic = static_cast<float>(metallic_itr->second.Factor());
            std::cerr << std::format("\t\tMetallic: {}", pbr_material.metallic) << std::endl;
        } else {
            std::cerr << "\t\tUsing default metallic factor" << std::endl;
        }
        // roughness
        const auto& roughness_itr = material.values.find("roughnessFactor");
        if (roughness_itr != material.values.end()) {
            pbr_material.roughness = static_cast<float>(roughness_itr->second.Factor());
            std::cerr << std::format("\t\tRoughness: {}", pbr_material.roughness) << std::endl;
        } else {
            std::cerr << "\t\tUsing default roughness factor" << std::endl;
        }
        */

        // base color
        const auto& base_color  = material.pbrMetallicRoughness.baseColorFactor;
        pbr_material.base_color = make_float4(static_cast<float>(base_color[0]),
                                              static_cast<float>(base_color[1]),
                                              static_cast<float>(base_color[2]),
                                              static_cast<float>(base_color[3]));
        // emissive factor
        const auto& emissive_factor  = material.emissiveFactor;
        pbr_material.emissive_factor = make_float3(static_cast<float>(emissive_factor[0]),
                                                   static_cast<float>(emissive_factor[1]),
                                                   static_cast<float>(emissive_factor[2]));
        // metallic
        pbr_material.metallic  = static_cast<float>(material.pbrMetallicRoughness.metallicFactor);
        // roughness
        pbr_material.roughness = static_cast<float>(material.pbrMetallicRoughness.roughnessFactor);

        std::cerr << std::format("\t\tBase color: ({}, {}, {}, {})",
                                 pbr_material.base_color.x,
                                 pbr_material.base_color.y,
                                 pbr_material.base_color.z,
                                 pbr_material.base_color.w) << std::endl
                  << std::format("\t\tEmissive factor: ({}, {}, {})",
                                 pbr_material.emissive_factor.x,
                                 pbr_material.emissive_factor.y,
                                 pbr_material.emissive_factor.z) << std::endl
                  << std::format("\t\tMetallic factor: {}", pbr_material.metallic) << std::endl
                  << std::format("\t\tRoughness factor: {}", pbr_material.roughness) << std::endl;

        // normal texture
        loadTextureInfo(scene, material.normalTexture, pbr_material.normal_texture);
        // emissive texture
        loadTextureInfo(scene, material.emissiveTexture, pbr_material.emissive_texture);
        // base color texture
        loadTextureInfo(scene, material.pbrMetallicRoughness.baseColorTexture, pbr_material.base_color_texture);
        // metallic roughness texture
        loadTextureInfo(scene, material.pbrMetallicRoughness.metallicRoughnessTexture, pbr_material.metallic_roughness_texture);

        scene.addMaterial(pbr_material);
    }

    for (const auto& mesh: model.meshes) {
        std::cerr << std::format("\tLoading mesh '{}'\n"
                                 "\t\tNumber of mesh primitive groups: {}",
                                 mesh.name,
                                 mesh.primitives.size()) << std::endl;
        auto new_mesh = std::make_shared<Scene::Mesh>();

    }
}