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

    int32_t mouse_button = -1;
    bool window_resized  = true;
    bool camera_changed  = true;
    bool minimized       = false;
};