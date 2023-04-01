#include "Camera.h"

Camera
Camera::create(const float3& position, const float3& target, const float3& up) noexcept
{
    using namespace tputil;
    float3 w = normalize(target - position);
    float3 u = normalize(cross(up, w));
    float3 v = cross(w, u);

    return Camera{ .position = position, .u = u, .v = v, .w = w };
}