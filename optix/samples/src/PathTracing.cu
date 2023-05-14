#include "PathTracing.h"

#include <vector_types.h>
#include <optix_device.h>

#include "Manet.h"
#include "random.h"
#include "Helper.h"
#include "Record.h"
#include "HitResult.h"

namespace
{

struct Onb
{
    __forceinline__ __device__ Onb(const float3& normal)
    {
        m_normal = normal;

        if(fabs(m_normal.x) > fabs(m_normal.z))
        {
            m_binormal.x = -m_normal.y;
            m_binormal.y =  m_normal.x;
            m_binormal.z =  0;
        }
        else
        {
            m_binormal.x =  0;
            m_binormal.y = -m_normal.z;
            m_binormal.z =  m_normal.y;
        }

        m_binormal = normalize(m_binormal);
        m_tangent = cross(m_binormal, m_normal);
    }

    __forceinline__ __device__ void inverse_transform(float3& p) const
    {
        p = p.x * m_tangent + p.y * m_binormal + p.z * m_normal;
    }

    float3 m_tangent;
    float3 m_binormal;
    float3 m_normal;
};

__constant__ struct
{
    __forceinline__ __device__ OptixPayloadTypeID constexpr payloadType(PayloadType payload_type)
    {
        switch (payload_type) {
        case PAYLOAD_TYPE_RADIANCE:
            return OPTIX_PAYLOAD_TYPE_ID_0;
        case PAYLOAD_TYPE_OCCLUSION:
            return OPTIX_PAYLOAD_TYPE_ID_1;
        }
    }

} g_mapper;

__forceinline__ __device__ RadiancePayload& getRadiancePayload()
{
    return getPayload<RadiancePayload&>();
}

__forceinline__ __device__ void
traceRadiance(OptixTraversableHandle handle,
              float                  tmin,
              float                  tmax,
              RadiancePayload&       payload)
{
    uint32_t u0, u1;
    packPointer(u0, u1, &payload);

    optixTrace(g_mapper.payloadType(PAYLOAD_TYPE_RADIANCE),
               handle,
               payload.ray_origin,
               payload.ray_direction,
               tmin,
               tmax,
               0.0f,  // ray time
               OptixVisibilityMask{ 255 },    // visibility mask
               OPTIX_RAY_FLAG_DISABLE_ANYHIT | OPTIX_RAY_FLAG_CULL_BACK_FACING_TRIANGLES,
               // OPTIX_RAY_FLAG_NONE,
               RAY_TYPE_RADIANCE,
               RAY_TYPE_COUNT,
               RAY_TYPE_RADIANCE,
               u0, u1);
}

__forceinline__ __device__ bool
traceOcclusion(OptixTraversableHandle handle,
               float3                 ray_origin,
               float3                 ray_direction,
               float                  tmin,
               float                  tmax)
{
    uint32_t occluded;
    optixTrace(g_mapper.payloadType(PAYLOAD_TYPE_OCCLUSION),
               handle,
               ray_origin,
               ray_direction,
               tmin,
               tmax,
               0.0f, // ray time
               OptixVisibilityMask{ 255 },    // visibility mask
               OPTIX_RAY_FLAG_DISABLE_ANYHIT | OPTIX_RAY_FLAG_TERMINATE_ON_FIRST_HIT,
               // OPTIX_RAY_FLAG_TERMINATE_ON_FIRST_HIT,
               RAY_TYPE_OCCLUSION,
               RAY_TYPE_COUNT,
               RAY_TYPE_OCCLUSION,
               occluded);
    return static_cast<bool>(occluded);
}

} // namespace

extern "C" __constant__ LaunchParams g_launch_params;

extern "C" __global__ void __raygen__pinhole()
{
    const uint3    idx               = optixGetLaunchIndex();
    const uint3    dim               = optixGetLaunchDimensions();
    const size_t   pixel_index       = dim.x * idx.y + idx.x;
    const uint32_t accum_count       = g_launch_params.frame.accum_count;
    const uint32_t samples_per_pixel = g_launch_params.samples_per_pixel;
    const uint32_t max_tracing_num   = g_launch_params.max_tracing_num;
    const auto     camera            = g_launch_params.camera;

    uint32_t seed = tea<4>(pixel_index, accum_count);
    float3 result = make_float3(0.0f);

    for (uint32_t i = 0; i < samples_per_pixel; i++) {
        const float2 subpixel_jitter = make_float2(rnd(seed), rnd(seed));
        const float2 st = 2.0f
                          * make_float2((static_cast<float>(idx.x) + subpixel_jitter.x) / static_cast<float>(dim.x),
                                        (static_cast<float>(idx.y) + subpixel_jitter.y) / static_cast<float>(dim.y))
                          - 1.0f;
        RadiancePayload payload = {};
        payload.ray_origin    = camera.position;
        payload.ray_direction = normalize(st.x * camera.u + st.y * camera.v - camera.w);
        payload.seed          = seed;

        do {
            traceRadiance(g_launch_params.handle, 0.01f, 1e16f, payload);
            result += payload.attenuation * payload.radiance;
            payload.depth++;
        } while (!payload.done && payload.depth < max_tracing_num);
    }

    float3 result_color = result / static_cast<float>(samples_per_pixel);
    float4 accum_color  = g_launch_params.frame.accum_buffer[pixel_index];

    if (accum_count > 0) {
        const float factor = 1.0f / static_cast<float>(accum_count + 1);
        result_color = clamp(lerp(make_float3(accum_color), result_color, factor), make_float3(0.0f), make_float3(1.0f));
    }

    g_launch_params.frame.accum_buffer[pixel_index] = make_float4(result_color, 1.0f);
    g_launch_params.frame.color_buffer[pixel_index] = make_color(result_color);
}

extern "C" __global__ void __closesthit__radiance()
{
    optixSetPayloadTypes(PAYLOAD_TYPE_RADIANCE);

    const HitgroupData*       data     = reinterpret_cast<HitgroupData*>(optixGetSbtDataPointer());
    const HitResult           result   = getHitResult(*data);
    const PbrMaterial&        material = *(data->material);
    const ParallelogramLight& light    = g_launch_params.light;
    RadiancePayload&          payload  = getRadiancePayload();
    uint32_t                  seed     = payload.seed;

    float4 base_color = material.base_color * result.color;
    if (material.base_color_texture) {
        const float4 texture_color        = sampleTexture<float4>(material.base_color_texture, result);
        const float3 texture_color_linear = linearize(make_float3(texture_color));
        base_color *= make_float4(texture_color_linear, texture_color.w);
    }

    float3 radiance    = make_float3(0.0f);
    float3 attenuation = make_float3(1.0f);

    // emission
    if (material.emissive_texture) {
        const float3 emissive_factor = material.emissive_factor;
        const float4 emissive_texture_color = sampleTexture<float4>(material.emissive_texture, result);
        radiance += emissive_factor * make_float3(emissive_texture_color);
    }

    // normal
    float3 normal = result.normal;
    if (material.normal_texture) {
        const float4 normal_sampled = 2.0f * sampleTexture<float4>(material.normal_texture, result) - make_float4(1.0f);
        const float2 rotation       = material.normal_texture.texcoord_rotation;
        const float2 tb             = make_float2(normal_sampled.x, normal_sampled.y);
        const float2 tb_trans       = make_float2(dot(tb, make_float2(rotation.y, -rotation.x)),
                                                  dot(tb, make_float2(rotation.x, rotation.y)));
        normal = normalize(tb_trans.x * result.texcoord.t + tb_trans.y * result.texcoord.b + normal_sampled.z * result.normal);
    }

    if (dot(normal, payload.ray_direction) > 0.0f)
        normal = -normal;

    float metallic  = material.metallic;
    float roughness = material.roughness;
    if (material.metallic_roughness_texture) {
        const float4 metallic_roughness = sampleTexture<float4>(material.metallic_roughness_texture, result);
        metallic  *= metallic_roughness.z;
        roughness *= metallic_roughness.y;
    }
    
    // BRDF
    const float  s = 2.0f * rnd(seed) - 1.0f;
    const float  t = 2.0f * rnd(seed) - 1.0f;
    const float3 sample_pos = light.center + s * light.half_u + t * light.half_v;
    const float3 sample_dir = normalize(sample_pos - result.intersection);
    const float3 half_vec   = normalize(sample_dir - payload.ray_direction);
    const float  N_dot_L    = dot(normal, sample_dir);
    const float  N_dot_V    = dot(normal, -payload.ray_direction);
    const float  N_dot_H    = dot(normal, half_vec);
    const float  V_dot_H    = dot(-payload.ray_direction, half_vec);

    const float  alpha  = roughness * roughness;
    const float3 albedo = make_float3(base_color);
    const float3 f0     = lerp(make_float3(0.04f), albedo, metallic);
    const float3 F      = schlick(f0, V_dot_H);
    const float  G      = smiths(N_dot_V, N_dot_L, roughness);
    const float  D      = ggxNormal(N_dot_H, alpha);
    const float3 ks     = F;
    const float3 kd     = (make_float3(1.0f) - ks) * (1.0f - metallic);
    
    const float3 f_r = kd * albedo / MANET_PI + ks * 0.25f * G * D / (N_dot_V * N_dot_L) * F;

    attenuation *= f_r * N_dot_L * 2.0f * MANET_PI / g_launch_params.p_rr;

    /*
    // direct light
    if (dot(normal, sample_dir) > 0.0f && dot(normal, -payload.ray_direction) > 0.0f) {
        const float distance = length(sample_pos - result.intersection);
        const bool  occluded = traceOcclusion(g_launch_params.handle,
                                              result.intersection,
                                              sample_dir,
                                              0.01f,
                                              distance - 0.01f);
                                            
        if (!occluded) {
            const float area = 4.0f * length(light.half_u) * length(light.half_v);
            radiance += light.emission * f_r * N_dot_L * dot(light.normal, -sample_dir) * area / (distance * distance);
        }
    }
    */

    payload.radiance = radiance;
    payload.attenuation *= attenuation;

    if (rnd(seed) > g_launch_params.p_rr) {
        payload.done = true;
        return;
    }

    // uniform hemisphere sample
    float3 sample_vec;
    cosine_sample_hemisphere(rnd(seed), rnd(seed), sample_vec);
    Onb onb(normal);
    onb.inverse_transform(sample_vec);

    payload.ray_origin    = result.intersection;
    payload.ray_direction = normalize(sample_vec);
}

extern "C" __global__ void __miss__radiance()
{
    optixSetPayloadTypes(PAYLOAD_TYPE_RADIANCE);
    RadiancePayload& payload = getRadiancePayload();

    payload.radiance = make_float3(0.0f); // if depth > 0 and ray missed, then no radiance
    if (payload.depth == 0) // directly hit the background
        payload.radiance = g_launch_params.background_color;

    payload.done = true;
}

extern "C" __global__ void __closesthit__occlusion()
{
    optixSetPayloadTypes(PAYLOAD_TYPE_OCCLUSION);
    optixSetPayload_0(1);
}

extern "C" __global__ void __miss__occlusion()
{
    optixSetPayloadTypes(PAYLOAD_TYPE_OCCLUSION);
    optixSetPayload_0(0);
}