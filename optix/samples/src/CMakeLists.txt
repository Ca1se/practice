OPTIX_add_sample_executable(pathtracer target_name
    PathTracing.cu
    Aabb.h
    Camera.cpp
    Camera.h
    CudaBufferView.h
    CudaDeviceBuffer.cpp
    CudaDeviceBuffer.h
    CudaObjectView.h
    CudaOutputBuffer.h
    Exception.cpp
    Exception.h
    GlDisplay.cpp
    GlDisplay.h
    Manet.cpp
    Manet.h
    ManetMacros.h
    Matrix.h
    PbrMaterial.h
    Record.h
    Scene.cpp
    Scene.h
    Tracer.cpp
    Tracer.h
    Transform.h
    Util.cpp
    Util.h
    VectorMath.h
    OPTIONS -rdc true
)

target_link_libraries(${target_name}
    CUDA::cudart
)