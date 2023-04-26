#pragma once

#include <cstdint>
#include <vector>

#include <vector_types.h>
#include <optix_types.h>

#include "CudaBufferView.h"
#include "CudaDeviceBuffer.h"

namespace tputil
{

class Scene
{
public:
    Scene() = default;
    ~Scene() noexcept;

    struct Mesh
    {
        std::vector<CudaBufferView<uint32_t>> indices;
        std::vector<CudaBufferView<float3>>   positions;
        std::vector<CudaBufferView<float3>>   normals;
        std::vector<CudaBufferView<float2>>   texcoords[2];
        std::vector<CudaBufferView<float4>>   diffuse_colors;

        std::vector<int32_t> material_indices;

        OptixTraversableHandle gas_handle = 0;
        CudaDeviceBuffer       gas_buffer = 0;
    };
private:
    std::vector<CudaDeviceBuffer> m_device_buffers;
};

}