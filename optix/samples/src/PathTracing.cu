#include <cuda_runtime_api.h>
#include <optix_device.h>

extern "C" __global__ void __raygen__pinhole()
{ 
}

extern "C" __global__ void __closesthit__radiance()
{
}

extern "C" __global__ void __miss__radiance()
{
}

extern "C" __global__ void __closesthit__occlusion()
{
}

extern "C" __global__ void __miss__occlusion()
{
}