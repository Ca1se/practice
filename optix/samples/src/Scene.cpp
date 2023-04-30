#include "Scene.h"

#include <iostream>
#include <format>

#include <channel_descriptor.h>

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <tiny_gltf.h>

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
            return cudaAddressModeWrap;
        }
    }

    cudaTextureFilterMode constexpr filterMode(int tinygltf_mode)
    {
        switch (tinygltf_mode) {
        case TINYGLTF_TEXTURE_FILTER_NEAREST:
            return cudaFilterModePoint;
        default:
            return cudaFilterModeLinear;
        }
    }
} g_mapper;

}

Scene::Scene()
{
    cudaFree(nullptr);
}

Scene::~Scene() noexcept
{
    try {
        for (auto texture: m_textures)
            CUDA_CHECK(cudaDestroyTextureObject(texture));
        for (auto image: m_images)
            CUDA_CHECK(cudaFreeArray(image));
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