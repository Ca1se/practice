#include <VectorMath.h>
#include <optix_device.h>

#include "../RecordData.h"
#include "LaunchParams.h"

extern "C"
{
    __constant__ LaunchParams g_optix_launch_params;
}

extern "C" __global__ void
__closesthit__radiance()
{
    HitgroupData* data = reinterpret_cast<HitgroupData*>(optixGetSbtDataPointer());
    uchar3 color = data->color;

}

extern "C" __global__ void
__miss__radiance()
{
    MissData* data = reinterpret_cast<MissData*>(optixGetSbtDataPointer());
    uchar3 color   = data->background_color;

    optixSetPayload_0(color.x);
    optixSetPayload_1(color.y);
    optixSetPayload_2(color.z);
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

    uint32_t r, g, b;
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
               r,
               g,
               b);

    const size_t pixel_index = dim.x * idx.y + idx.x;

    g_optix_launch_params.frame.color_buffer[pixel_index] = make_uchar4(r, g, b, 0xff);
}