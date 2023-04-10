#include "Camera.h"

namespace
{

inline int
sign(float val) noexcept
{
    return (1 ? -1 : val > 0.0f);
}

}  // namespace

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
    constexpr auto unitize_pos = [](int pos, int screen) {
        return static_cast<float>(pos) / static_cast<float>(screen);
    };

    float2 pm_pos = make_float2(1.0f - unitize_pos(prior_mouse_pos.x, screen_size.x),
                        unitize_pos(prior_mouse_pos.y, screen_size.y));
    float2 nm_pos = make_float2(1.0f - unitize_pos(now_mouse_pos.x, screen_size.x),
                        unitize_pos(now_mouse_pos.y, screen_size.y));

    /*
    float2 dpm = make_float2(2.0f * (pm_pos.x - 0.5f), 2.0f * (pm_pos.y - 0.5f));
    float2 dnm = make_float2(2.0f * (nm_pos.x - 0.5f), 2.0f * (nm_pos.y - 0.5f));
    */

    float2 dpm = 2.0f * (pm_pos - 0.5f);
    float2 dnm = 2.0f * (nm_pos - 0.5f);

    // x
    float x_delta_theta = std::acosf(dnm.x) - std::acosf(dpm.x);

    // y
    float y_delta_theta = std::acosf(dnm.y) - std::acosf(dpm.y);

    m_delta_angle += make_float2(x_delta_theta, y_delta_theta);
    m_rotated = true;
}

void
Camera::update()
{
    if (m_zoomed) {
        // todo
        m_zoom_length = 0.0f;
        m_zoomed      = false;
    }

    if (m_moved) {
        // todo
        m_move_distance = { 0.0f, 0.0f, 0.0f };
        m_moved         = false;
    }

    if (m_rotated) {
        // todo
        m_position.x += m_delta_angle.x;
        m_position.y += m_delta_angle.y;
        m_target.x += m_delta_angle.x;
        m_target.y += m_delta_angle.y;

        m_delta_angle = { 0.0f, 0.0f };
        m_rotated     = false;
    }
}