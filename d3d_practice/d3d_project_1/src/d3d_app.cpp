#include <vector>

#include <d3dcommon.h>
#include <minwinbase.h>

#include "d3d_app.hpp"


namespace {
    d3df::D3DApp* g_d3d_app = nullptr;
}

namespace d3df {

D3DApp::D3DApp(HINSTANCE inst):
    m_app_instance(inst),
    m_main_window(nullptr),
    m_paused(false),
    m_minimized(false),
    m_maximized(false),
    m_resizing(false),
    m_msaa4x_quality(0),
    m_timer(),
    m_d3d_device(nullptr),
    m_d3d_context(nullptr),
    m_swap_chain(nullptr),
    m_depth_buffer(nullptr),
    m_render_target_view(nullptr),
    m_depth_buffer_view(nullptr),
    m_viewport(),
    m_window_title(L"D3D11 Application"),
    m_d3d_driver_type(D3D_DRIVER_TYPE_HARDWARE),
    m_client_width(800),
    m_client_height(600),
    m_msaa4x_enabled(false)
{
    ZeroMemory(&m_viewport, sizeof(D3D11_VIEWPORT));

    g_d3d_app = this;
}

D3DApp::~D3DApp()
{

}

inline HINSTANCE D3DApp::app_instance() const noexcept { return m_app_instance; }
inline HWND D3DApp::main_window() const noexcept { return m_main_window; }
inline float D3DApp::aspect_ratio() const noexcept { return static_cast<float>(m_client_width) / m_client_height; }

}