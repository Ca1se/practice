#pragma once

struct Camera
{
    float3 position;
    float3 u;
    float3 v;
    float3 w;

    float plane_distance;

    static Camera create(const float3& position, const float3& target, const float3& up, float vfov, float aspect_ratio, float plane_distance) noexcept;
};