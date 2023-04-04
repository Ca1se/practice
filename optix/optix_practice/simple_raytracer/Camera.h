#pragma once

struct Camera
{
    float3 position;
    float3 target;
    float3 up;
    float vfov;
    float aspect_ratio;

    static void computeUVW(const Camera& camera, float3& u, float3& v, float3& w);
};