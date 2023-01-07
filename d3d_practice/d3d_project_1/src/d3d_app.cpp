#include <d3dcommon.h>
#include <Windows.h>
#include <minwinbase.h>
#include <tchar.h>
#include <windef.h>
#include <wingdi.h>
#include <winnt.h>
#include <winuser.h>

#include "d3d_app.hpp"

#define RELEASE_COM(x) \
    if(x) { \
        x->Release(); \
        x = nullptr; \
    }


namespace {

d3df::D3DApp* g_d3d_app = nullptr;

}

inline LRESULT CALLBACK
main_window_proc(HWND hwnd, uint32_t msg, WPARAM wparam, LPARAM lparam)
{
    return g_d3d_app->msg_proc(hwnd, msg, wparam, lparam);
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
    RELEASE_COM(m_depth_buffer_view);
    RELEASE_COM(m_render_target_view);
    RELEASE_COM(m_depth_buffer);
    RELEASE_COM(m_swap_chain);

    if(m_d3d_context) {
        m_d3d_context->ClearState();
        m_d3d_context->Release();
    }

    RELEASE_COM(m_d3d_device);
}

inline HINSTANCE D3DApp::app_instance() const noexcept { return m_app_instance; }
inline HWND D3DApp::main_window() const noexcept { return m_main_window; }
inline float D3DApp::aspect_ratio() const noexcept { return static_cast<float>(m_client_width) / m_client_height; }

int D3DApp::run()
{

}

bool D3DApp::init()
{
    if(!init_main_window())
        return false;

    if(!init_direct3d())
        return false;

    return true;
}

LRESULT D3DApp::msg_proc(HWND hwnd, uint32_t msg, WPARAM wparam, LPARAM lparam)
{

}

void D3DApp::handle_resize()
{

}

bool D3DApp::init_main_window()
{
    WNDCLASSEXW wc;

    ZeroMemory(&wc, sizeof(WNDCLASSEXW));

    wc.cbSize       = sizeof(WNDCLASSEXW);
    wc.style        = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc  = main_window_proc;
    wc.cbClsExtra   = 0;
    // to do


    if(!RegisterClassExW(&wc)) {
        MessageBoxW(nullptr, L"RegisterClass Failed.", nullptr, 0);
        return false;
    }

    RECT r = {0, 0, m_client_width, m_client_height};
    AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, false);
    
    int width   = r.right - r.left;
    int height  = r.bottom - r.top;

    m_main_window = CreateWindowW(L"D3DWndClassName",
                                   m_window_title.c_str(),
                                   WS_OVERLAPPEDWINDOW,
                                   CW_USEDEFAULT,
                                   CW_USEDEFAULT,
                                   width,
                                   height,
                                   nullptr,
                                   nullptr,
                                   m_app_instance,
                                   nullptr);

    if(!m_main_window) {
        MessageBox(nullptr, _T("CreateWindow Failed."), nullptr, 0);
        return false;
    }

    ShowWindow(m_main_window, SW_SHOW);
    UpdateWindow(m_main_window);

    return true;
}

bool D3DApp::init_direct3d()
{

}

void D3DApp::calculate_frame_stats()
{

}

}