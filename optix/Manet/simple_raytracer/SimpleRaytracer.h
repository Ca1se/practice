#pragma once

#include "cuda/LaunchParams.h"
#include "Camera.h"

struct State
{
    struct
    {
        int32_t width;
        int32_t height;
    } output_size = { 400, 300 };

    Camera camera;

    tputil::CudaDeviceBuffer accum_buffer = { sizeof(float4) * output_size.width * output_size.height };
    tputil::CudaOutputBuffer<uchar4> color_buffer = { output_size.width, output_size.height };

    LaunchParams launch_params = {};
    tputil::CudaDeviceBuffer launch_param_buffer  = { sizeof(LaunchParams) };

    int2 prior_mouse_pos = {};

    bool button_pressed = false;
    bool window_resized = false;
    bool camera_changed = true;
    bool minimized      = false;
};