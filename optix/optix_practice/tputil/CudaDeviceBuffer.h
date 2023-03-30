#pragma once

#include <cuda.h>
#include <cstddef>

namespace tputil
{

class CudaDeviceBuffer
{
public:
    CudaDeviceBuffer();
    ~CudaDeviceBuffer() noexcept;

    CudaDeviceBuffer(const void* src, size_t byte_size);

    CudaDeviceBuffer(const CudaDeviceBuffer&)            = delete;
    CudaDeviceBuffer& operator=(const CudaDeviceBuffer&) = delete;
    CudaDeviceBuffer(CudaDeviceBuffer&&)                 = delete;
    CudaDeviceBuffer& operator=(CudaDeviceBuffer&&)      = delete;

    CUdeviceptr data() const noexcept { return m_data; }

    size_t size() const noexcept { return m_size; }

    void upload(const void* src, size_t byte_size);

    void download(void* dest, size_t buffer_size) const;

    void destory();

private:
    void resize(size_t byte_size);

    CUdeviceptr m_data;

    size_t m_size;
};

}  // namespace tputil
