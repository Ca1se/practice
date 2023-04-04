cuda_compile_and_embed(embedded_ptx_code cuda/DeviceProgram.cu)

file(GLOB OPTIX_PRACTICE1_SRCS
    *.cpp
    *.h
)

add_executable(simple_raytracer
    ${embedded_ptx_code}
    ${OPTIX_PRACTICE1_SRCS}
)

target_link_libraries(simple_raytracer PRIVATE
    glad
    glfw3
    tputil
)

target_include_directories(simple_raytracer PRIVATE
    ${OptiX_INCLUDE}
)

target_precompile_headers(simple_raytracer PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/Pch.h>
)

cuda_optix_compile_configure(simple_raytracer)