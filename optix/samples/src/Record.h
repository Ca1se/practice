#pragma once

#include <optix_types.h>

#include "CudaBufferView.h"
#include "CudaObjectView.h"
#include "PbrMaterial.h"

template <typename T>
struct Record
{
    alignas(OPTIX_SBT_RECORD_ALIGNMENT) char header[OPTIX_SBT_RECORD_HEADER_SIZE];
    T data;
};

struct EmptyData {};

struct HitgroupData
{
    CudaTriangleIndexBufferView indices;
    CudaBufferView<float3>      positions;
    CudaBufferView<float3>      normals;
    CudaBufferView<float2>      texcoords;
    CudaBufferView<float4>      colors;
    CudaObjectView<PbrMaterial> material;
};

using EmptyRecord = Record<EmptyData>;
using HitgroupRecord = Record<HitgroupData>;