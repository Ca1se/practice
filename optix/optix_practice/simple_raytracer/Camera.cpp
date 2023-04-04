#include "Camera.h"

void
Camera::computeUVW(const Camera& camera, float3& u, float3& v, float3& w)
{
    using namespace tputil;

    float3 ww = camera.target - camera.position;
    float3 uu = normalize(cross(camera.up, ww));
    float3 vv = normalize(cross(ww, uu));

    float wlen = length(ww);
    float vlen = wlen * std::tanf(0.5f * camera.vfov);
    float ulen = vlen * camera.aspect_ratio;

    u = ulen * uu;
    v = vlen * vv;
    w = ww;
}