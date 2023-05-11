#include <cuda_runtime_api.h>
#include <optix_device.h>

#include "Manet.h"
#include "random.h"
#include "Helper.h"
#include "Record.h"
#include "HitResult.h"

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
    const float2 subpixel_jitter = accum_count == 0 ? make_float2(0.5f, 0.5f) : make_float2(rnd(seed), rnd(seed));
    const float2 st = 2.0f
                    * make_float2((static_cast<float>(idx.x) + subpixel_jitter.x) / static_cast<float>(dim.x),
                                  (static_cast<float>(idx.y) + subpixel_jitter.y) / static_cast<float>(dim.y))
                    - 1.0f;
    const float3 ray_origin    = camera.position;
    const float3 ray_direction = normalize(st.x * camera.u + st.y * camera.v - camera.w);

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
    const HitResult result   = getHitResult(*data);

    float4 base_color = data->material->base_color * result.color;
    if (data->material->base_color_texture) {
        const float4 base_color_tex = sampleTexture<float4>(data->material->base_color_texture, result);
        const float3 base_color_tex_linear = linearize(make_float3(base_color_tex));
        base_color *= make_float4(base_color_tex_linear, base_color_tex.w);
    }

    const float cosdn = 0.2f + 0.8f * fabs(dot(optixGetWorldRayDirection(), result.normal));

    float3& payload = getPayload<float3&>();
    payload = cosdn * make_float3(base_color);
}

extern "C" __global__ void __miss__radiance()
{
    float3& color = getPayload<float3&>();
    color = g_launch_params.background_color;
}

extern "C" __global__ void __closesthit__occlusion()
{
}

extern "C" __global__ void __miss__occlusion()
{
}