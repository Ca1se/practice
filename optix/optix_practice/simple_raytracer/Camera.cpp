#include "Camera.h"

Camera::Camera(const float3& position, const float3& target, const float3& up, float vfov, float aspect_ratio)
    : m_position{ position }
    , m_target{ target }
    , m_up{ tputil::normalize(up) }
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
Camera::zoom(int zoom_length)
{
    if(m_rotated)
        update();
    
    m_zoom_length += zoom_length;
    m_zoomed = true;
}

void
Camera::move(float3 move_offset)
{
    if(m_rotated)
        update();
    
    m_move_offset += move_offset;
    m_moved = true;
}

void
Camera::rotate(int2 prior_mouse_pos, int2 now_mouse_pos, int2 screen_size)
{
    if(m_zoomed || m_moved)
        update();

    constexpr auto unitize_pos = [](int pos, int screen) {
        return static_cast<float>(pos) / static_cast<float>(screen);
    };

    float2 pm_pos = make_float2(1.0f - unitize_pos(prior_mouse_pos.x, screen_size.x),
                        unitize_pos(prior_mouse_pos.y, screen_size.y));
    float2 nm_pos = make_float2(1.0f - unitize_pos(now_mouse_pos.x, screen_size.x),
                        unitize_pos(now_mouse_pos.y, screen_size.y));

    float2 dpm = 2.0f * (pm_pos - 0.5f);
    float2 dnm = 2.0f * (nm_pos - 0.5f);

    float x_delta_theta = std::acosf(dpm.x) - std::acosf(dnm.x);
    float y_delta_theta = std::acosf(dpm.y) - std::acosf(dnm.y);

    m_delta_angle += make_float2(x_delta_theta, y_delta_theta);
    m_rotated = true;
}

void
Camera::update()
{
    using namespace tputil;

    if (m_zoomed) {
        float3 new_position = m_position + 0.1f * m_zoom_length * m_w;

        if(length(new_position - m_target) >= 0.1f)
            m_position = new_position;

        m_zoom_length = 0;
        m_zoomed = false;
    }

    if (m_moved) {
        float3 move_offset = 0.1f * m_move_offset;

        m_position += move_offset.x * m_u + move_offset.y * m_v + move_offset.z * m_w;
        m_target   += move_offset.x * m_u + move_offset.y * m_v + move_offset.z * m_w;

        m_move_offset = { 0.0f, 0.0f, 0.0f };
        m_moved = false;
    }

    if (m_rotated) {
        auto yaw   = rotateAroundYAxis(m_delta_angle.x);
        auto pitch = rotateAroundXAxis(m_delta_angle.y);

        auto to_origin = translate(-m_target);
        auto to_position = translate(m_target);

        float3 new_position = to_position * pitch * yaw * to_origin * m_position;

        float3 idir = normalize(new_position - m_target);
        if(std::abs(1.0f - std::abs(tputil::dot(idir, m_up))) >= 0.1f)
            m_position = new_position;

        computeUVW();

        m_delta_angle = { 0.0f, 0.0f };
        m_rotated = false;
    }

}