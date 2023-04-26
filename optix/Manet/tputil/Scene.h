#pragma once

#include <cstdint>
#include <vector>
#include <memory>

#include <vector_types.h>
#include <optix_types.h>

#include "Camera.h"
#include "CudaBufferView.h"
#include "CudaDeviceBuffer.h"
#include "Aabb.h"

namespace tputil
{

class Scene
{
public:
    struct Mesh
    {
        std::vector<CudaBufferView<uint32_t>> indices        = {};
        std::vector<CudaBufferView<float3>>   positions      = {};
        std::vector<CudaBufferView<float3>>   normals        = {};
        std::vector<CudaBufferView<float2>>   texcoords[2]   = {};
        std::vector<CudaBufferView<float4>>   diffuse_colors = {};

        std::vector<int32_t> material_indices = {};

        OptixTraversableHandle gas_handle = 0;
        CudaDeviceBuffer       gas_buffer = {};

        Aabb aabb;
    };

    Scene() = default;
    ~Scene() noexcept;

private:
    std::vector<Camera>                m_camera;
    std::vector<std::shared_ptr<Mesh>> m_meshes;
    // std::vector<

    std::vector<CudaDeviceBuffer> m_device_buffers;
};

}