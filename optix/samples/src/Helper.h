#pragma once

#include <vector_types.h>
#include <optix_device.h>

#include "VectorMath.h"
#include "random.h"

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

static __forceinline__ __device__ void packPointer(const void* ptr, uint32_t& i0, uint32_t& i1)
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
static __forceinline__ __device__ T& getPayload()
{
    const uint32_t i0 = optixGetPayload_0();
    const uint32_t i1 = optixGetPayload_1();

    return *static_cast<T*>(unpackPointer(i0, i1));
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