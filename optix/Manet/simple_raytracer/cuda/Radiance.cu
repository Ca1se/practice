#include <optix_device.h>
#include <VectorMath.h>

#include "LaunchParams.h"
#include "Helper.h"

extern "C"
{
    __constant__ LaunchParams g_optix_launch_params;
}

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
    const float3 intersection = optixGetWorldRayOrigin() + optixGetRayTmax() * ray_direction;
    const float3 normal   = nid.x != -1
                            ? tputil::normalize(b0 * data->normals[nid.x]
                                              + b1 * data->normals[nid.y]
                                              + b2 * data->normals[nid.z])
                            : plainNormal(data->vertices[vid.x], data->vertices[vid.y], data->vertices[vid.z]);
    const float2 texcoord = tid.x != -1
                            ? b0 * data->texcoords[tid.x]
                            + b1 * data->texcoords[tid.y]
                            + b2 * data->texcoords[tid.z]
                            : make_float2(0.0f, 0.0f);

    const float3 light_position = make_float3(115.57f, 923.70f, -11.59f);
    const float3 shadow_direction = light_position - intersection;

    float light_visibility = 0.0f;
    uint32_t i0, i1;
    packPointer(static_cast<void*>(&light_visibility), i0, i1);

    optixTrace(g_optix_launch_params.handle,
               intersection,
               shadow_direction,
               0.001f,
               1.0f - 0.001f,
               0.0f,
               OptixVisibilityMask{ 255 },
               OPTIX_RAY_FLAG_TERMINATE_ON_FIRST_HIT 
               | OPTIX_RAY_FLAG_DISABLE_ANYHIT 
               | OPTIX_RAY_FLAG_DISABLE_CLOSESTHIT,
               0,
               1,
               1,
               i0,
               i1);
    
    float3 color = data->diffuse_color;
    if(data->texture != 0) {
        const float4 tex = tex2D<float4>(data->texture, texcoord.x, texcoord.y);
        color *= make_float3(tex.x, tex.y, tex.z);
    }

    const float cosdn = 0.1f + 0.8f * -tputil::dot(ray_direction, normal);
    color = (0.2f + (0.2f + 0.8f * light_visibility) * cosdn) * color;

    float4& payload = getPayload<float4>();
    payload = make_float4(color, 1.0f);
}

extern "C" __global__ void __anyhit__back_culling()
{
    const HitgroupData* data = reinterpret_cast<HitgroupData*>(optixGetSbtDataPointer());

    const uint32_t primitive_id = optixGetPrimitiveIndex();
    const int3& vid = data->vertex_indices[primitive_id];
    const float3 normal = plainNormal(data->vertices[vid.x], data->vertices[vid.y], data->vertices[vid.z]);
    const float3 ray_direction = optixGetWorldRayDirection();
    if (tputil::dot(normal, ray_direction) >= 0.0f)
        optixIgnoreIntersection();
}

extern "C" __global__ void __miss__radiance()
{
    float4& payload = getPayload<float4>();
    payload = make_float4(0.5f, 0.7f, 1.0f, 1.0f);
}

extern "C" __global__ void __raygen__pinhole()
{
    const uint3 idx    = optixGetLaunchIndex();
    const uint3 dim    = optixGetLaunchDimensions();
    const auto& camera = g_optix_launch_params.camera;
    const uint32_t accum_id = g_optix_launch_params.frame.accum_id;
    const size_t pixel_index = dim.x * idx.y + idx.x;

    // Get ray direction
    uint32_t seed = tea<4>(pixel_index, accum_id);
    const float2 subpixel_jitter = accum_id == 0 ? make_float2(0.5f, 0.5f) : make_float2(rnd(seed), rnd(seed));
    const float2 st = 2.0f
                    * make_float2((static_cast<float>(idx.x) + subpixel_jitter.x) / static_cast<float>(dim.x),
                                  (static_cast<float>(idx.y) + subpixel_jitter.y) / static_cast<float>(dim.y))
                    - 1.0f;
    const float3 ray_origin    = g_optix_launch_params.camera.position;
    const float3 ray_direction = tputil::normalize(st.x * camera.u + st.y * camera.v + camera.w);

    // Pack payload pointer to 2 uints;
    float4 color;
    uint32_t i0, i1;
    packPointer(static_cast<void*>(&color), i0, i1);

    optixTrace(g_optix_launch_params.handle,
               ray_origin,
               ray_direction,
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

    uchar4& output_color = g_optix_launch_params.frame.color_buffer[pixel_index];
    float4& accum_color  = g_optix_launch_params.frame.accum_buffer[pixel_index];

    accum_color += color;
    if(accum_id == 0)
        accum_color = color;
    output_color = make_uchar4(255.99f * (accum_color / static_cast<float>(accum_id + 1)));
}