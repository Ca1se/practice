#include <optix_device.h>
#include <VectorMath.h>

#include "LaunchParams.h"
#include "RecordData.h"
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
    const int3& nid = data->normal_indices[primitive_id];
    const int3& tid = data->texcoord_indices[primitive_id];

    const float2 barycentrics = optixGetTriangleBarycentrics();
    const float3 v0_normal = tputil::normalize(data->normals[nid.x]);
    const float3 v1_normal = tputil::normalize(data->normals[nid.y]);
    const float3 v2_normal = tputil::normalize(data->normals[nid.z]);
    const float3 face_normal = tputil::normalize(barycentrics.x * v0_normal + barycentrics.y * v1_normal + (1.0f - barycentrics.x - barycentrics.y) * v2_normal);

    const float3 ray_direction = optixGetWorldRayDirection();

    const float dotr = tputil::dot(ray_direction, face_normal);

    const float3 color = powf(fmaxf(0.0f, -dotr), 2.0f) * data->diffuse_color;

    float4& payload = getPayload<float4>();
    payload = make_float4(color, 1.0f);
}

extern "C" __global__ void
__anyhit__back_culling()
{
    const HitgroupData* data = reinterpret_cast<HitgroupData*>(optixGetSbtDataPointer());

    const uint32_t primitive_id = optixGetPrimitiveIndex();
    const int3& vid = data->vertex_indices[primitive_id];
    const float3& v0 = data->vertices[vid.x];
    const float3& v1 = data->vertices[vid.y];
    const float3& v2 = data->vertices[vid.z];
    const float3 ray_direction = optixGetWorldRayDirection();
    const float3 face_normal = tputil::cross(v2 - v0, v1 - v0);
    if(tputil::dot(ray_direction, face_normal) < 0.0f)
        optixIgnoreIntersection();
}

extern "C" __global__ void
__miss__radiance()
{
    const MissData* data = reinterpret_cast<MissData*>(optixGetSbtDataPointer());
    const float3& color   = data->background_color;

    float4& payload = getPayload<float4>();
    payload = make_float4(color, 1.0f);
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

    float4 color;
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

    g_optix_launch_params.frame.color_buffer[pixel_index] = make_uchar4(255.99f * color);
}