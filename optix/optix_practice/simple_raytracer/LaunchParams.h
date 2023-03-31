#pragma once

struct LaunchParams
{
    int32_t width;
    int32_t height;

    struct
    {
        uint64_t id;
        uchar4* color_buffer;
    } frame;

    OptixTraversableHandle handle;
};