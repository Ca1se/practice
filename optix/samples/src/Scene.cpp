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
    cudaTextureAddressMode constexpr wrappingMode(int32_t tinygltf_mode)
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

    cudaTextureFilterMode constexpr filterMode(int32_t tinygltf_mode)
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

    CudaTriangleIndexBufferView::TriangleIndexFormat constexpr indexFormat(int32_t tinygltf_type)
    {
        switch (tinygltf_type) {
            case TINYGLTF_COMPONENT_TYPE_SHORT:
                return CudaTriangleIndexBufferView::TRIANGLE_INDEX_FORMAT_USHORT3;
            case TINYGLTF_COMPONENT_TYPE_INT:
                return CudaTriangleIndexBufferView::TRIANGLE_INDEX_FORMAT_UINT3;
            default:
                throw std::runtime_error{ EXCEPTION_MSG(std::format("unsupported index byte size: {}", tinygltf_type)) };
        }
    }
} g_mapper;

template <typename TextureInfo>
void loadTextureInfo(PbrMaterial::Texture& tex, const Scene& scene, const TextureInfo& gltf_tex)
{
    tex.texture        = 0;
    tex.texcoord_index = 0;
    if (gltf_tex.index >= 0) {
        if (tex.texcoord_index >= 1) {
            std::cerr << "\t\tUnsupported multiple texcoords" << std::endl;
            return;
        }

        tex.texture        = scene.getTextures()[gltf_tex.index];
        tex.texcoord_index = gltf_tex.texCoord;

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

template <typename T>
CudaBufferView<T> createBufferViewFromGltf(const tinygltf::Model& model,
                                           const std::vector<CudaDeviceBuffer>& buffers,
                                           int32_t attribute_index)
{
    if (attribute_index < 0)
        return CudaBufferView<T>{};

    const tinygltf::Accessor&   accessor    = model.accessors[attribute_index];
    const tinygltf::BufferView& buffer_view = model.bufferViews[accessor.bufferView];

    const auto& buffer = buffers[buffer_view.buffer];
    CudaBufferView<T> ret = {
        .buffer_ptr       = buffer.data() + accessor.byteOffset + buffer_view.byteOffset,
        .element_count    = static_cast<uint32_t>(accessor.count),
        .stride_byte_size = static_cast<uint32_t>(buffer_view.byteStride)
    };
    if constexpr (std::is_same_v<T, TriangleIndexType>) {
        ret.element_count /= 3;
        ret.index_format   = g_mapper.indexFormat(accessor.componentType);
    }
    return ret;
}

void loadAabb(Aabb& aabb, const tinygltf::Model& model, int32_t attribute_index)
{
    const tinygltf::Accessor& accessor = model.accessors[attribute_index];
    if (!accessor.minValues.empty() && !accessor.maxValues.empty()) {
        aabb.include(Aabb(make_float3(static_cast<float>(accessor.minValues[0]),
                                      static_cast<float>(accessor.minValues[1]),
                                      static_cast<float>(accessor.minValues[2])),
                          make_float3(static_cast<float>(accessor.maxValues[0]),
                                      static_cast<float>(accessor.maxValues[1]),
                                      static_cast<float>(accessor.maxValues[2]))));
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

        std::cerr << std::format("\t\tBase color: ({}, {}, {}, {})\n"
                                 "\t\tEmissive factor: ({}, {}, {})\n"
                                 "\t\tMetallic factor: {}\n"
                                 "\t\tRoughness factor: {}",
                                 pbr_material.base_color.x,
                                 pbr_material.base_color.y,
                                 pbr_material.base_color.z,
                                 pbr_material.base_color.w,
                                 pbr_material.emissive_factor.x,
                                 pbr_material.emissive_factor.y,
                                 pbr_material.emissive_factor.z,
                                 pbr_material.metallic,
                                 pbr_material.roughness) << std::endl;

        // normal texture
        loadTextureInfo(pbr_material.normal_texture, scene, material.normalTexture);
        // emissive texture
        loadTextureInfo(pbr_material.emissive_texture, scene, material.emissiveTexture);
        // base color texture
        loadTextureInfo(pbr_material.base_color_texture, scene, material.pbrMetallicRoughness.baseColorTexture);
        // metallic roughness texture
        loadTextureInfo(pbr_material.metallic_roughness_texture, scene, material.pbrMetallicRoughness.metallicRoughnessTexture);

        scene.addMaterial(pbr_material);
    }

    for (const auto& mesh: model.meshes) {
        std::cerr << std::format("\tLoading mesh '{}'\n"
                                 "\t\tNumber of mesh primitive groups: {}",
                                 mesh.name,
                                 mesh.primitives.size()) << std::endl;
        auto new_mesh = std::make_shared<Scene::Mesh>();
        size_t triangle_num = 0;
        for (const auto& primitive: mesh.primitives) {
            if (primitive.mode != TINYGLTF_MODE_TRIANGLES) {
                std::cerr << "\t\tSkipping primitive: non-triangle" << std::endl;
                continue;
            }

            const std::vector<CudaDeviceBuffer>& buffers = scene.getBuffers();
            
            // index
            new_mesh->indices.push_back(createBufferViewFromGltf<TriangleIndexType>(model, buffers, primitive.indices));
            triangle_num += new_mesh->indices.back().element_count;
            // position and aabb
            const auto& position_index_itr = primitive.attributes.find("POSITION");
            if (position_index_itr == primitive.attributes.end()) {
                std::cerr << "\t\tSkipping primitive: no position data" << std::endl;
                continue;
            }
            new_mesh->positions.push_back(createBufferViewFromGltf<float3>(model, buffers, position_index_itr->second));
            loadAabb(new_mesh->aabb, model, position_index_itr->second);
            // normal
            const auto& normal_index_itr = primitive.attributes.find("NORMAL");
            if (normal_index_itr != primitive.attributes.end()) {
                new_mesh->normals.push_back(createBufferViewFromGltf<float3>(model, buffers, normal_index_itr->second));
            } else {
                new_mesh->normals.push_back(CudaBufferView<float3>{});
            }
            // texcoord
            const auto& texcoord_index_itr = primitive.attributes.find("TEXCOORD_0");
            if (texcoord_index_itr != primitive.attributes.end()) {
                new_mesh->texcoords.push_back(createBufferViewFromGltf<float2>(model, buffers, texcoord_index_itr->second));
            } else {
                new_mesh->texcoords.push_back(CudaBufferView<float2>{});
            }
            // color
            const auto& color_index_itr = primitive.attributes.find("COLOR_0");
            if (color_index_itr != primitive.attributes.end()) {
                new_mesh->colors.push_back(createBufferViewFromGltf<float4>(model, buffers, color_index_itr->second));
            } else {
                new_mesh->colors.push_back(CudaBufferView<float4>{});
            }
            // material index
            new_mesh->material_indices.push_back(primitive.material);
        }
        std::cerr << std::format("\t\tNumber of triangles: {}", triangle_num) << std::endl;
    }

    std::vector<int32_t> is_root(model.nodes.size(), 1);
    for (const auto& node: model.nodes) {
        for (int32_t child: node.children) {
            is_root[child] = 0;
        }
    }
    for (size_t i = 0; i < is_root.size(); i++) {
        if (!is_root[i])
            continue;
    }
}