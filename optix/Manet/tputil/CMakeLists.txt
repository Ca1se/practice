set(sources
    ${CMAKE_BINARY_DIR}/Config.h
    CudaDeviceBuffer.h
    CudaDeviceBuffer.cpp
    CudaOutputBuffer.h
    Exception.h
    Exception.cpp
    GlDisplay.h
    GlDisplay.cpp
    Preprocessor.h
    TpUtil.h
    TpUtil.cpp
    Matrix.h
    Model.h
    Model.cpp
    Transform.h
    VectorMath.h
)

set(tputil_target "tputil")
add_library(${tputil_target} ${sources})
if(WIN32)
    target_compile_definitions(${tputil_target} PUBLIC GLAD_GLAPI_EXPORT)
endif()

target_link_libraries(${tputil_target} LINK_PRIVATE
    glfw3
    glad
    CUDA::cudart
)

if(WIN32)
  target_link_libraries(${tputil_target} LINK_PRIVATE winmm.lib)
endif()