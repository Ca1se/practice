OPTIX_add_sample_executable(pathtracer target_name
    Aabb.h
    Camera.cpp
    Camera.h
    CudaBufferView.h
    CudaDeviceBuffer.cpp
    CudaDeviceBuffer.h
    CudaOutputBuffer.h
    Exception.cpp
    Exception.h
    GlDisplay.cpp
    GlDisplay.h
    Manet.cpp
    Manet.h
    Matrix.h
    PbrMaterial.h
    Scene.cpp
    Scene.h
    Transform.h
    Util.cpp
    Util.h
    VectorMath.h
    OPTIONS -rdc true
)

target_link_libraries(${target_name}
    CUDA::cudart
)