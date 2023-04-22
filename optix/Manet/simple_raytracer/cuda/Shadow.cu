#include "LaunchParams.h"
#include "Helper.h"

extern "C"
{
    __constant__ LaunchParams g_optix_launch_params;
}

extern "C" __global__ void __miss__shadow()
{
    float& payload = getPayload<float>();
    payload = 1.0f;
}