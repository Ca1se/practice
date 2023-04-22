#pragma once

#include <device_types.h>
#include <optix_types.h>

template <typename T>
struct Record
{
    alignas(OPTIX_SBT_RECORD_ALIGNMENT) char header[OPTIX_SBT_RECORD_HEADER_SIZE];
    T data;
};

struct RaygenData
{
};

struct MissData
{
    float3 background_color;
};

struct HitgroupData
{
    float3* vertices;
    float3* normals;
    float2* texcoords;

    int3* vertex_indices;
    int3* normal_indices;
    int3* texcoord_indices;

    float3 diffuse_color;
    cudaTextureObject_t texture;
};

struct EmptyData
{
};

using RaygenRecord   = Record<RaygenData>;
using MissRecord     = Record<MissData>;
using HitgroupRecord = Record<HitgroupData>;
using EmptyRecord    = Record<EmptyData>;

struct LaunchParams
{
    struct
    {
        uint32_t accum_id;
        float4* accum_buffer;
        uchar4* color_buffer;
    } frame;

    struct
    {
        float3 position;
        float3 u;
        float3 v;
        float3 w;
    } camera;

    OptixTraversableHandle handle;
};