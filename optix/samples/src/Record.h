#pragma once

#include <optix_types.h>

#include "CudaBufferView.h"

template <typename T>
struct Record
{
    alignas(OPTIX_SBT_RECORD_ALIGNMENT) char header[OPTIX_SBT_RECORD_HEADER_SIZE];
    T data;
};

struct HitgroupData
{
    CudaTriangleIndexBufferView indices;
    CudaBufferView<float3>      positions;
    CudaBufferView<float3>      normals;
    CudaBufferView<float2>      texcoords;
    CudaBufferView<float4>      colors;
};

struct EmptyData {};

using EmptyRecord = Record<EmptyData>;