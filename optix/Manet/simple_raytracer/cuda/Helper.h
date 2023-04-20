#pragma once

#include <optix_device.h>
#include <VectorMath.h>

#include "DeviceCamera.h"

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

    T* payload_ptr = static_cast<T*>(unpackPointer(i0, i1));
    return *payload_ptr;
}


static __forceinline__ __device__ void computeRay(const DeviceCamera& camera, float3& origin, float3& direction)
{
    const uint3 idx = optixGetLaunchIndex();
    const uint3 dim = optixGetLaunchDimensions();

    const float s = 2.0f * (static_cast<float>(idx.x) / static_cast<float>(dim.x)) - 1.0f;
    const float t = 2.0f * (static_cast<float>(idx.y) / static_cast<float>(dim.y)) - 1.0f;

    origin    = camera.position;
    direction = tputil::normalize(s * camera.u + t * camera.v + camera.w);
}

static __forceinline__ __device__ float3 plainNormal(const float3& a, const float3& b,const float3& c)
{
    return tputil::normalize(tputil::cross(b - a, c - a));
}