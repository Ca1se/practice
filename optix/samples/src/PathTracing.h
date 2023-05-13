#pragma once

#include <cstdint>

#include <vector_types.h>
#include <optix_types.h>

static constexpr uint32_t RAY_TYPE_COUNT = 2;

enum RayType
{
    RAY_TYPE_RADIANCE  = 0,
    RAY_TYPE_OCCLUSION = 1
};

enum PayloadType
{
    PAYLOAD_TYPE_RADIANCE,
    PAYLOAD_TYPE_OCCLUSION
};

struct RadiancePayload
{
    float3 attenuation   = { 1.0f, 1.0f, 1.0f };
    float3 radiance      = { 0.0f, 0.0f, 0.0f };
    float3 ray_origin;
    float3 ray_direction;

    uint32_t seed;
    uint32_t depth = 0;
    bool     done  = false;
};