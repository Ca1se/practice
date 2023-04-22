#pragma once

#include <optix_device.h>
#include <VectorMath.h>
#include <curand_kernel.h>

#include "random.h"

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