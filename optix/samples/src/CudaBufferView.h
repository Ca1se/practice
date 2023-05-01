#pragma once

#include <cstdint>

#include <cuda.h>
#include <host_defines.h>

#include "ManetMacros.h"

/*
template <typename T>
struct CudaBufferView
{
    CUdeviceptr buffer_ptr = 0;
    uint32_t    count      = 0;

    MANET_DECL bool isValid() const { return (buffer_ptr != 0); }
    MANET_DECL operator bool() const { return isValid(); }
    __forceinline__ __device__ T& at(size_t index) const
    {
        return reinterpret_cast<T*>(buffer_ptr)[index];
    }
};
*/

template <typename T>
struct CudaBufferView
{
    CUdeviceptr buffer_ptr        = 0;
    uint32_t    count             = 0;

    MANET_DECL bool isValid() const { return (buffer_ptr != 0); }
    MANET_DECL operator bool() const { return isValid(); }
    template <typename AT = T>
    __forceinline__ __device__ AT& at(size_t index) const
    { return reinterpret_cast<AT*>(buffer_ptr)[index]; }
};

struct CudaIndexBufferView : public CudaBufferView<uint32_t>
{
    enum IndexSize
    {
        INDEX_SIZE_IN_BYTE_16 = 16,
        INDEX_SIZE_IN_BYTE_32 = 32
    };

    IndexSize index_size = INDEX_SIZE_IN_BYTE_32;
};
