cuda_compile_and_embed(embedded_ptx_code DeviceProgram.cu)

file(GLOB OPTIX_PRACTICE_SRCS
    *.cpp
    *.h
)

add_executable(PipelineAndRaygen
    ${embedded_ptx_code}
    ${OPTIX_PRACTICE_SRCS}
)

target_link_libraries(PipelineAndRaygen PRIVATE
    glad
    glfw3
    tputil
)

target_include_directories(PipelineAndRaygen PRIVATE
    ${OptiX_INCLUDE}
)

target_precompile_headers(PipelineAndRaygen PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/Pch.h>
)

cuda_optix_compile_configure(PipelineAndRaygen)