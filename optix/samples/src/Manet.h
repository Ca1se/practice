#pragma once

#include <cstdint>

#include <vector_types.h>
#include <optix_types.h>

#include "CudaBufferView.h"

struct LaunchParams
{
    struct
    {
        uint32_t accum_count;
        CudaBufferView<float4> accum_buffer;
        CudaBufferView<uchar4> color_buffer;
    } frame;

    struct
    {
        float3 position;
        float3 u;
        float3 v;
        float3 w;
    } camera;

    float3 background_color;
    OptixTraversableHandle handle;
};