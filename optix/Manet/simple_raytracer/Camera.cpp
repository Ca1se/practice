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

    m_w = m_target - m_position;
    m_u = normalize(cross(m_up, m_w));
    m_v = normalize(cross(m_w, m_u));

    m_wlen = length(m_w);
    m_vlen = m_wlen * std::tanf(0.5f * m_vfov);
    m_ulen = m_vlen * m_aspect_ratio;

    m_w = normalize(m_w);
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

    float x_delta_theta = std::acosf(dnm.x) - std::acosf(dpm.x);
    float y_delta_theta = std::acosf(dnm.y) - std::acosf(dpm.y);

    m_delta_angle += make_float2(x_delta_theta, y_delta_theta);
    m_rotated = true;
}

void
Camera::update()
{
    using namespace tputil;

    if (m_zoomed) {
        float3 new_position = m_position + 10.0f * m_zoom_length * m_w;

        if(length(new_position - m_target) >= 0.1f && dot(normalize(m_target - new_position), normalize(m_target - m_position)) > 0.0f)
            m_position = new_position;

        m_zoom_length = 0;
        m_zoomed = false;
    }

    if (m_moved) {
        float3 move_offset = 10.0f * m_move_offset;

        m_position += move_offset.x * m_u + move_offset.y * m_up + move_offset.z * m_w;
        m_target   += move_offset.x * m_u + move_offset.y * m_up + move_offset.z * m_w;

        m_move_offset = { 0.0f, 0.0f, 0.0f };
        m_moved = false;
    }

    if (m_rotated) {
        auto yaw = rotateAroundAxis(m_up, m_delta_angle.x);

        m_position = (yaw * (m_position - m_target)) + m_target;

        computeUVW();

        auto pitch = rotateAroundAxis(-m_u, m_delta_angle.y);

        float3 new_position = (pitch * (m_position - m_target)) + m_target;

        float3 idir = normalize(new_position - m_target);
        if (std::abs(1.0f - std::abs(tputil::dot(idir, m_up))) >= 0.001f) {
            m_position = new_position;
            m_uvw_changed = true;
        }

        m_delta_angle = { 0.0f, 0.0f };
        m_rotated = false;
    }

    if (m_uvw_changed) {
        computeUVW();
        m_uvw_changed = false;
    }
}