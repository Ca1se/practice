#pragma once

struct RaygenData
{
};

struct MissData
{
    uchar3 background_color;
};

struct HitgroupData
{
    float3* vertices;
    uint3* indices;
};