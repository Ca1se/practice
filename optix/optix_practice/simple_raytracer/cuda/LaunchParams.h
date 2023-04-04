#pragma once

#include <cstdint>

#include <optix_types.h>

struct LaunchParams
{
    struct
    {
        uint64_t id;
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