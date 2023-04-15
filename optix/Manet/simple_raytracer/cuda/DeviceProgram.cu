#include <optix_device.h>
#include <VectorMath.h>

#include "../RecordData.h"
#include "LaunchParams.h"
#include "Helper.h"

extern "C"
{
    __constant__ LaunchParams g_optix_launch_params;
}

extern "C" __global__ void
__closesthit__radiance()
{
    const HitgroupData* data = reinterpret_cast<HitgroupData*>(optixGetSbtDataPointer());

    const uint32_t primitive_id = optixGetPrimitiveIndex();
    const uint3& vid = data->indices[primitive_id];
    const float3& A  = data->vertices[vid.x];
    const float3& B  = data->vertices[vid.y];
    const float3& C  = data->vertices[vid.z];

    const float3 ray_direction = optixGetWorldRayDirection();
    const float3 face_normal   = tputil::normalize(tputil::cross(C - A, B - A));

    const float3 gray_color = make_float3(211.0f, 211.0f, 211.0f);
    const float dotr = tputil::dot(ray_direction, face_normal);

    const float3 color = fmaxf(0.0f, -dotr) * gray_color;

    uchar4& payload = getPayload<uchar4>();
    payload = make_uchar4(static_cast<uint8_t>(color.x),
                          static_cast<uint8_t>(color.y),
                          static_cast<uint8_t>(color.z),
                          0xff);
}

extern "C" __global__ void
__miss__radiance()
{
    MissData* data = reinterpret_cast<MissData*>(optixGetSbtDataPointer());
    uchar3 color   = data->background_color;

    uchar4& payload = getPayload<uchar4>();
    payload = make_uchar4(color.x, color.y, color.z, 0xff);
}

static __device__ void
computeRay(float3& origin, float3& direction)
{
    const uint3 idx = optixGetLaunchIndex();
    const uint3 dim = optixGetLaunchDimensions();

    const float s = 2.0f * (static_cast<float>(idx.x) / static_cast<float>(dim.x)) - 1.0f;
    const float t = 2.0f * (static_cast<float>(idx.y) / static_cast<float>(dim.y)) - 1.0f;

    const auto& camera = g_optix_launch_params.camera;

    origin    = camera.position;
    direction = tputil::normalize(s * camera.u + t * camera.v + camera.w);
}

extern "C" __global__ void
__raygen__pinhole()
{
    const uint3 idx = optixGetLaunchIndex();
    const uint3 dim = optixGetLaunchDimensions();

    float3 origin;
    float3 direction;
    computeRay(origin, direction);

    uchar4 color;
    uint32_t i0, i1;
    packPointer(static_cast<void*>(&color), i0, i1);

    optixTrace(g_optix_launch_params.handle,
               origin,
               direction,
               0.0f,
               1e16f,
               0.0f,
               OptixVisibilityMask{ 255 },
               OPTIX_RAY_FLAG_NONE,
               0,
               1,
               0,
               i0,
               i1);

    const size_t pixel_index = dim.x * idx.y + idx.x;

    g_optix_launch_params.frame.color_buffer[pixel_index] = color;
}