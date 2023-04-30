#pragma once

#include <vector>
#include <memory>

#include "Aabb.h"
#include "Camera.h"
#include "CudaBufferView.h"
#include "CudaDeviceBuffer.h"
#include "PbrMaterial.h"

struct Scene
{
public:
    struct Mesh
    {
        std::vector<CudaBufferView<uint32_t>> indices;
        std::vector<CudaBufferView<float3>>   positions;
        std::vector<CudaBufferView<float3>>   normals;
        std::vector<CudaBufferView<float2>>   texcoords;
        std::vector<CudaBufferView<float4>>   colors;
        std::vector<int32_t>                  material_indices;
        Aabb                                  aabb;
    };

    Scene();
    ~Scene() noexcept;

    auto& getCameras() const noexcept { return m_cameras; }
    auto& getMeshes() const noexcept { return m_meshes; }
    auto& getMaterials() const noexcept { return m_materials; }
    auto& getImages() const noexcept { return m_images; }
    auto& getTextures() const noexcept { return m_textures; }
    auto& getAabb() const noexcept { return m_aabb; }

    void addImage(int32_t width, int32_t height, int32_t bits_per_component, const void* data);
    void addTexture(cudaTextureAddressMode address_s,
                    cudaTextureAddressMode address_t,
                    cudaTextureFilterMode  filter_mode,
                    int32_t                image_index);

private:
    std::vector<Camera>                m_cameras    = {};
    std::vector<std::shared_ptr<Mesh>> m_meshes     = {};
    std::vector<PbrMaterial>           m_materials  = {};
    std::vector<cudaArray_t>           m_images     = {};
    std::vector<cudaTextureObject_t>   m_textures   = {};
    Aabb                               m_aabb       = {};

    std::vector<CudaDeviceBuffer> m_buffers = {};
};