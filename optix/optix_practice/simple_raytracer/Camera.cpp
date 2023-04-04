#include "Camera.h"

Camera::Camera(const float3& position, const float3& target, const float3& up, float vfov, float aspect_ratio)
    : m_position{ position }
    , m_target{ target }
    , m_up{ up }
    , m_vfov{ vfov }
    , m_aspect_ratio{ aspect_ratio }
{
    computeUVW();
}

void
Camera::computeUVW()
{
    using namespace tputil;

    float3 ww = m_target - m_position;
    float3 uu = normalize(cross(m_up, ww));
    float3 vv = normalize(cross(ww, uu));

    float wlen = length(ww);
    float vlen = wlen * std::tanf(0.5f * m_vfov);
    float ulen = vlen * m_aspect_ratio;

    m_u = ulen * uu;
    m_v = vlen * vv;
    m_w = ww;
}

void
Camera::zoom(float zoom_length)
{
    // todo
}

void
Camera::move(float3 move_distance)
{
    // todo
}

void
Camera::rotate(int2 prior_mouse_pos, int2 now_mouse_pos, int2 screen_size)
{
    // todo

    m_rotated = true;
}

void
Camera::update()
{
}