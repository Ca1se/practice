#pragma once

struct LaunchParams
{
    int frame_id;
    uchar4* color_buffer;
    struct
    {
        int width;
        int height;
    } size;
};