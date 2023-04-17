#pragma once

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
};