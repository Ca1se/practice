#pragma once

#include <cstdint>

#include <cuda.h>
#include <host_defines.h>

#include "ManetMacros.h"

template <typename T>
struct CudaBufferView
{
    CUdeviceptr m_buffer_ptr;
    uint32_t    count;

    MANET_DECL bool isValid() const { return (m_buffer_ptr != 0); }
    MANET_DECL operator bool() const { return isValid(); }
    __forceinline__ __device__ const T& operator[](size_t index) const { return (reinterpret_cast<T*>(m_buffer_ptr))[index]; }
};