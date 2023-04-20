#include "LaunchParams.h"
#include "Helper.h"

extern "C" __constant__ LaunchParams g_optix_launch_params;

extern "C" __global__ void __miss__shadow()
{
    float4& payload = getPayload<float4>();
    payload = make_float4(1.0f, 0.0f, 0.0f, 1.0f);
}