OPTIX_add_sample_executable(simple_raytracer target_name
    cuda/DeviceProgram.cu
    cuda/Helper.h
    cuda/LaunchParams.h
    cuda/RecordData.h
    Camera.h
    Camera.cpp 
    Sample.h
    Sample.cpp
    SimpleRaytracer.h
    SimpleRaytracer.cpp
)

target_link_libraries(${target_name}
    CUDA::cudart
    CUDA::cuda_driver
)

target_precompile_headers(${target_name} PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/Pch.h>
)