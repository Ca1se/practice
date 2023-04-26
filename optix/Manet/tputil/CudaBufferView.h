#pragma once

#include <cuda.h>

#include "Preprocessor.h"

namespace tputil
{

template <typename T>
class CudaBufferView
{
public:
    TPUTIL_DECL CudaBufferView()  = default;
    TPUTIL_DECL ~CudaBufferView() = default;

    TPUTIL_DECL CudaBufferView(const CudaBufferView&) = default;
    TPUTIL_DECL CudaBufferView& operator=(const CudaBufferView&) = default;

    TPUTIL_DECL CudaBufferView(CUdeviceptr buffer_ptr) : m_buffer_ptr(buffer_ptr) {}

    TPUTIL_DECL void setBufferPtr(CUdeviceptr buffer_ptr) { m_buffer_ptr = buffer_ptr; }
    TPUTIL_DECL bool isValid() const { return (m_buffer_ptr != 0); }
    TPUTIL_DECL operator bool() const { return isValid(); }
    TPUTIL_INLINE TPUTIL_DEVICE const T& operator[](size_t index) const { return (reinterpret_cast<T*>(m_buffer_ptr))[index]; }
private:
    CUdeviceptr m_buffer_ptr;
};

} // namespace tputil