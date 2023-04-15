#pragma once

#include "Camera.h"

struct State
{
    struct
    {
        int32_t width;
        int32_t height;
    } output_size;

    Camera camera;

    tputil::CudaOutputBuffer<uchar4> pixel_buffer;

    int2 prior_mouse_pos = {};

    bool button_pressed = false;
    bool window_resized = true;
    bool camera_changed = true;
    bool minimized      = false;
};