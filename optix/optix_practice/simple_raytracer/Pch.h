#pragma once

#include <array>
#include <cassert>
#include <cstdint>
#include <format>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

#include <glad/glad.h>

#include <CudaDeviceBuffer.h>
#include <CudaOutputBuffer.h>
#include <Exception.h>
#include <GlDisplay.h>
#include <GlUtil.h>
#include <VectorMath.h>
#include <Windows.h>
#include <cuda_runtime.h>
#include <glfw/glfw3.h>
#include <optix.h>
#include <optix_stubs.h>
#include <vector_functions.h>
#include <vector_types.h>

#define THROW_EXCEPTION(msg) throw std::exception(std::format("[{}, {}]: {}", __FILE__, __LINE__, msg).c_str())

#define LOG_INFO(msg) std::cerr << msg << "\n"
#define LOG_DEBUG(msg)                       \
    std::cerr << "\033[1;33m" << msg << "\n" \
              << "\033[0m"
#define LOG_ERROR(msg)                       \
    std::cerr << "\033[0;31m" << msg << "\n" \
              << "\033[0m"

inline void
ensureMinimumSize(int32_t& width, int32_t& height)
{
    if (width <= 0)
        width = 1;
    if (height <= 0)
        height = 1;
}
