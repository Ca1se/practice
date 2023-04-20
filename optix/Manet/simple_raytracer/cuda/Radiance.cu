#include <optix_device.h>
#include <VectorMath.h>
#include <texture_fetch_functions.h>

#include "LaunchParams.h"
#include "Helper.h"

extern "C" __constant__ LaunchParams g_optix_launch_params;

extern "C" __global__ void __closesthit__radiance()
{
    const HitgroupData* data = reinterpret_cast<HitgroupData*>(optixGetSbtDataPointer());

    const uint32_t primitive_id = optixGetPrimitiveIndex();
    const int3& vid = data->vertex_indices[primitive_id];
    const int3& nid = data->normal_indices[primitive_id];
    const int3& tid = data->texcoord_indices[primitive_id];

    const float2 barycentrics = optixGetTriangleBarycentrics();
    const float b1 = barycentrics.x;
    const float b2 = barycentrics.y;
    const float b0 = 1.0f - b1 - b2;

    const float3 ray_direction = optixGetWorldRayDirection();
    const float3 normal   = tputil::normalize(b0 * data->normals[nid.x]
                                            + b1 * data->normals[nid.y]
                                            + b2 * data->normals[nid.z]);
    const float2 texcoord = b0 * data->texcoords[tid.x]
                          + b1 * data->texcoords[tid.y]
                          + b2 * data->texcoords[tid.z];
    const float dotv = tputil::dot(ray_direction, normal);

    float3 color = data->diffuse_color;
    if(data->texture != 0) {
        const float4 tex = tex2D<float4>(data->texture, texcoord.x, texcoord.y);
        color *= make_float3(tex.x, tex.y, tex.z);
    }

    const float factor = 0.2f + 0.8f * fmaxf(0.0f, -dotv);

    float4& payload = getPayload<float4>();
    payload = make_float4(factor * color, 1.0f);
}

extern "C" __global__ void __miss__radiance()
{
    float4& payload = getPayload<float4>();
    payload = make_float4(0.5f, 0.7f, 1.0f, 1.0f);
}

extern "C" __global__ void __raygen__pinhole()
{
    const uint3 idx = optixGetLaunchIndex();
    const uint3 dim = optixGetLaunchDimensions();

    float3 origin;
    float3 direction;
    computeRay(g_optix_launch_params.camera, origin, direction);

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
               OPTIX_RAY_FLAG_CULL_BACK_FACING_TRIANGLES,
               0,
               1,
               0,
               i0,
               i1);

    const size_t pixel_index = dim.x * idx.y + idx.x;

    g_optix_launch_params.frame.color_buffer[pixel_index] = make_uchar4(255.99f * color);
}