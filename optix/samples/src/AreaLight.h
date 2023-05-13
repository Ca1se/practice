#pragma once

#include <vector_types.h>

struct ParallelogramLight
{
    float3 center;
    float3 half_u;
    float3 half_v;
    float3 target;
    float3 emission;
};