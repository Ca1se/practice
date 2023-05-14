#pragma once

#include <vector_types.h>
#include <optix_device.h>

#include "VectorMath.h"
#include "random.h"
#include "PbrMaterial.h"
#include "HitResult.h"

template <typename T>
struct RawType {
    using type = T;
};

template <typename T>
struct RawType<T*>
{
    using type = T;
};

template <typename T>
struct RawType<const T*>
{
    using type = T;
};

template <typename T>
struct RawType<T&>
{
    using type = T;
};

template <typename T>
struct RawType<const T&>
{
    using type = T;
};

static __forceinline__ __device__ void packPointer(uint32_t& i0, uint32_t& i1, const void* ptr)
{
    const uint64_t uptr = reinterpret_cast<uint64_t>(ptr);
    i0 = static_cast<uint32_t>(uptr >> 32);
    i1 = static_cast<uint32_t>(0x00000000ffffffff & uptr);
}

static __forceinline__ __device__ void* unpackPointer(uint32_t i0, uint32_t i1)
{
    const uint64_t uptr = static_cast<uint64_t>(i0) << 32 | i1;
    return reinterpret_cast<void*>(uptr);
}

template <typename T>
static __forceinline__ __device__ T getPayload()
{
    const uint32_t i0 = optixGetPayload_0();
    const uint32_t i1 = optixGetPayload_1();

    return *static_cast<RawType<T>::type*>(unpackPointer(i0, i1));
}

static __forceinline__ __device__ float3 plainNormal(const float3& A, const float3& B, const float3& C)
{
    return normalize(cross(B - A, C - A));
}

static __forceinline__ __device__ uchar4 make_color(const float3& color)
{
    return make_uchar4(static_cast<uint8_t>(255.99f * color.x),
                       static_cast<uint8_t>(255.99f * color.y),
                       static_cast<uint8_t>(255.99f * color.z),
                       255);
}

static __device__ __forceinline__ float3 schlick(float3 spec_color, float V_dot_H)
{
    return spec_color + (make_float3(1.0f) - spec_color) * powf(1.0f - V_dot_H, 5.0f);
}

/*
static __device__ __forceinline__ float vis(const float N_dot_L, const float N_dot_V, const float alpha)
{
    const float alpha_sq = alpha * alpha;

    const float ggx0 = N_dot_L * sqrtf(N_dot_V * N_dot_V * (1.0f - alpha_sq) + alpha_sq);
    const float ggx1 = N_dot_V * sqrtf(N_dot_L * N_dot_L * (1.0f - alpha_sq) + alpha_sq);

    return 2.0f * N_dot_L * N_dot_V / (ggx0 + ggx1);
}
*/

static __device__ __forceinline__ float smiths(float N_dot_V, float N_dot_L, float roughness)
{
    const float k    = (roughness + 1.0f) * (roughness + 1.0f) / 8.0f;
    const float ggx0 = N_dot_V / (N_dot_V * (1.0f - k) + k);
    const float ggx1 = N_dot_L / (N_dot_L * (1.0f - k) + k);
    return ggx0 * ggx1;
}

static __device__ __forceinline__ float ggxNormal(float N_dot_H, float alpha)
{
    const float alpha_sq   = alpha * alpha;
    const float N_dot_H_sq = N_dot_H * N_dot_H;
    const float x          = N_dot_H_sq * (alpha_sq - 1.0f) + 1.0f;
    return alpha_sq / (MANET_PI * x * x);
}

static __forceinline__ __device__ void cosine_sample_hemisphere(const float u1, const float u2, float3& p)
{
  // Uniformly sample disk.
  const float r   = sqrtf(u1);
  const float phi = 2.0f * MANET_PI * u2;
  p.x = r * cosf(phi);
  p.y = r * sinf(phi);

  // Project up to hemisphere.
  p.z = sqrtf(fmaxf(0.0f, 1.0f - p.x*p.x - p.y*p.y));
}

static __device__ __forceinline__ float3 linearize(const float3& c)
{
    return make_float3(powf(c.x, 2.2f),
                       powf(c.y, 2.2f),
                       powf(c.z, 2.2f));
}

template <typename T>
static __forceinline__ __device__ T sampleTexture(const PbrMaterial::Texture& tex, const HitResult& result)
{
    if (tex) {
        const float2 uv = result.texcoord.uv * tex.texcoord_scale;
        const float2 rotation = tex.texcoord_rotation;
        const float2 uv_final = make_float2(dot(uv, make_float2(rotation.y, rotation.x)),
                                            dot(uv, make_float2(-rotation.x, rotation.y)))
                                + tex.texcoord_offset;
        return tex2D<T>(tex.texture, uv_final.x, uv_final.y);
    } else {
        return T{};
    }
}
