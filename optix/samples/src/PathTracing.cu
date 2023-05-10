#include <cuda_runtime_api.h>
#include <optix_device.h>

#include "Manet.h"
#include "random.h"
#include "Helper.h"
#include "Record.h"

extern "C" __constant__ LaunchParams g_launch_params;

extern "C" __global__ void __raygen__pinhole()
{
    const uint3    idx         = optixGetLaunchIndex();
    const uint3    dim         = optixGetLaunchDimensions();
    const size_t   pixel_index = dim.x * idx.y + idx.x;
    const uint32_t accum_count = g_launch_params.frame.accum_count;
    const auto&    camera      = g_launch_params.camera;

    // Get ray direction
    uint32_t seed = tea<4>(pixel_index, accum_count);
    const float2 subpixel_jitter = accum_count == 0
                                   ? make_float2(0.5f, 0.5f)
                                   : make_float2(rnd(seed), rnd(seed));
    const float2 st = 2.0f
                    * make_float2((static_cast<float>(idx.x) + subpixel_jitter.x) / static_cast<float>(dim.x),
                                  (static_cast<float>(idx.y) + subpixel_jitter.y) / static_cast<float>(dim.y))
                    - 1.0f;
    const float3 ray_origin    = camera.position;
    const float3 ray_direction = normalize(st.x * camera.u + st.y * camera.v + camera.w);

    // Pack payload pointer to 2 uints;
    float3 color;
    uint32_t i0, i1;
    packPointer(static_cast<void*>(&color), i0, i1);

    optixTrace(g_launch_params.handle,
               ray_origin,
               ray_direction,
               0.0f,
               1e16f,
               0.0f,
               OptixVisibilityMask{ 255 },
               OPTIX_RAY_FLAG_CULL_BACK_FACING_TRIANGLES | OPTIX_RAY_FLAG_DISABLE_ANYHIT,
               0,
               2,
               0,
               i0,
               i1);
    float4& accum_color  = g_launch_params.frame.accum_buffer[pixel_index];
    uchar4& output_color = g_launch_params.frame.color_buffer[pixel_index];
    
    if (accum_count > 0) {
        const float factor = 1.0f / static_cast<float>(accum_count + 1);
        color = lerp(make_float3(accum_color), color, factor);
    }

    accum_color  = make_float4(color, 1.0f);
    output_color = make_color(color);
}

extern "C" __global__ void __closesthit__radiance()
{
    const HitgroupData* data = reinterpret_cast<HitgroupData*>(optixGetSbtDataPointer());
    const uint32_t primitive_index = optixGetPrimitiveIndex();
    const float2 barycentrics = optixGetTriangleBarycentrics();
    const float b1 = barycentrics.x;
    const float b2 = barycentrics.y;
    const float b0 = 1.0f - b1 - b2;

    const uint3 index = data->indices[primitive_index];

    const float3 ray_origin    = optixGetWorldRayOrigin();
    const float3 ray_direction = optixGetWorldRayDirection();

    // position
    float3 intersection  = ray_origin + optixGetRayTmax() * ray_direction;
    intersection = optixTransformPointFromObjectToWorldSpace(intersection);
    
    // normal
    float3 normal;
    if (data->normals) {
        const float3 n0 = data->normals[index.x];
        const float3 n1 = data->normals[index.y];
        const float3 n2 = data->normals[index.z];
        normal = b0 * n0 + b1 * n1 + b2 * n2;
    } else {
        const float3 p0 = data->positions[index.x];
        const float3 p1 = data->positions[index.y];
        const float3 p2 = data->positions[index.z];
        normal = plainNormal(p0, p1, p2);
    }
    normal = optixTransformNormalFromObjectToWorldSpace(normal);
    normal = normalize(normal);

    // texcoord
    float3 texture_color;
    if (data->texcoords) {
        const float2 t0 = data->texcoords[index.x];
        const float2 t1 = data->texcoords[index.y];
        const float2 t2 = data->texcoords[index.z];
        const float2 texcoord = b0 * t0 + b1 * t1 + b2 * t2;
        texture_color = make_float3(tex2D<float4>(data->material->base_color_texture, texcoord.x, texcoord.y));
    } else {
        texture_color = make_float3(1.0f);
    }

    const float cosdn = 0.1f + 0.8f * fabs(dot(ray_direction, normal));
    const float3 color = make_float3(data->material->base_color) * texture_color * cosdn;

    // float3& payload = getPayload<float3>();
    // payload = color * 0.01f;
}

extern "C" __global__ void __miss__radiance()
{
    float3& color = getPayload<float3>();
    color = g_launch_params.background_color;
}

extern "C" __global__ void __closesthit__occlusion()
{
}

extern "C" __global__ void __miss__occlusion()
{
}