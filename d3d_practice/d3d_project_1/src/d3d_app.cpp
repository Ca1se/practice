#include <cassert>

#include <WindowsX.h>
#include <d3d11.h>
#include <d3dcommon.h>
#include <Windows.h>
#include <dxgi.h>
#include <dxgiformat.h>
#include <dxgitype.h>
#include <minwinbase.h>
#include <tchar.h>
#include <winbase.h>
#include <windef.h>
#include <wingdi.h>
#include <winnt.h>
#include <winuser.h>
#include <wrl.h>
#include <wrl/client.h>

#include "d3d_app.hpp"
#include "log.hpp"
#include "util.hpp"


namespace {

t7d3d::D3DApp* g_d3d_app = nullptr;

}

inline LRESULT CALLBACK
main_window_proc(HWND hwnd, uint32_t msg, WPARAM wparam, LPARAM lparam)
{
    return g_d3d_app->msg_proc(hwnd, msg, wparam, lparam);
}

namespace t7d3d {

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
    assert(m_d3d_device);
    assert(m_d3d_context);
    assert(m_swap_chain);

    RELEASE_COM(m_render_target_view);
    RELEASE_COM(m_depth_buffer_view);
    RELEASE_COM(m_depth_buffer);

    HR_V(m_swap_chain->ResizeBuffers, 1,
        m_client_width, m_client_height,
        DXGI_FORMAT_R8G8B8A8_UNORM, 0);

    Microsoft::WRL::ComPtr<ID3D11Texture2D> back_buffer;
    HR_V(m_swap_chain->GetBuffer, 0, 
        __uuidof(ID3D11Texture2D), (void**) back_buffer.GetAddressOf());
    HR_V(m_d3d_device->CreateRenderTargetView, back_buffer.Get(), 
        nullptr, m_render_target_view.GetAddressOf());

    D3D11_TEXTURE2D_DESC depth_buffer_desc;
    
}

bool D3DApp::init_main_window()
{
    WNDCLASSEXW wc;

    ZeroMemory(&wc, sizeof(WNDCLASSEXW));

    wc.cbSize           = sizeof(WNDCLASSEXW);
    wc.style            = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc      = main_window_proc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hInstance        = m_app_instance;
    wc.hIcon            = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hCursor          = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground    = (HBRUSH) GetStockBrush(NULL_BRUSH);
    wc.lpszMenuName     = nullptr;
    wc.lpszClassName    = L"D3DWndClass";
    wc.hIconSm          = nullptr;

    if(!RegisterClassExW(&wc)) {
        LOGFMT_ERROR("Register class failed.");
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
        LOG_ERROR("CreateWindow Failed.");
        return false;
    }

    ShowWindow(m_main_window, SW_SHOW);
    UpdateWindow(m_main_window);

    return true;
}

bool D3DApp::init_direct3d()
{
    uint32_t device_flag = 0;
#if defined (DEBUG) || defined (_DEBUG)
    device_flag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_FEATURE_LEVEL check_level;
    HR_B(D3D11CreateDevice,
        nullptr,
        m_d3d_driver_type,
        nullptr,
        device_flag,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        m_d3d_device.GetAddressOf(),
        &check_level,
        m_d3d_context.GetAddressOf());

    if(check_level != D3D_FEATURE_LEVEL_11_0) {
        LOG_ERROR("Direct3D Feature Level 11 unsupported.");
        return false;
    }

    HR_B(m_d3d_device->CheckMultisampleQualityLevels,
        DXGI_FORMAT_R8G8B8A8_UNORM, 4, 
        &m_msaa4x_quality);
    assert(m_msaa4x_quality > 0);

    DXGI_SWAP_CHAIN_DESC sc_desc;
    sc_desc.BufferDesc.Width                    = m_client_width;
    sc_desc.BufferDesc.Height                   = m_client_height;
    sc_desc.BufferDesc.RefreshRate.Numerator    = 60;
    sc_desc.BufferDesc.RefreshRate.Denominator  = 1;
    sc_desc.BufferDesc.Format                   = DXGI_FORMAT_R8G8B8A8_UNORM;
    sc_desc.BufferDesc.ScanlineOrdering         = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    sc_desc.BufferDesc.Scaling                  = DXGI_MODE_SCALING_UNSPECIFIED;

    sc_desc.SampleDesc.Count            = 1;
    sc_desc.SampleDesc.Quality          = 0;
    if(m_msaa4x_enabled) {
        sc_desc.SampleDesc.Count        = 4;
        sc_desc.SampleDesc.Quality      = m_msaa4x_quality - 1;
    }

    sc_desc.BufferUsage         = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sc_desc.BufferCount         = 1;
    sc_desc.OutputWindow        = m_main_window;
    sc_desc.Windowed            = true;
    sc_desc.SwapEffect          = DXGI_SWAP_EFFECT_DISCARD;
    sc_desc.Flags               = 0;

    Microsoft::WRL::ComPtr<IDXGIDevice> dxgi_device;
    HR_B(m_d3d_device->QueryInterface, __uuidof(IDXGIDevice), (void**) dxgi_device.GetAddressOf());

    Microsoft::WRL::ComPtr<IDXGIAdapter> dxgi_adapter;
    HR_B(dxgi_device->GetParent, __uuidof(IDXGIAdapter), (void**) dxgi_adapter.GetAddressOf());

    Microsoft::WRL::ComPtr<IDXGIFactory> dxgi_factory;
    HR_B(dxgi_adapter->GetParent, __uuidof(IDXGIFactory), (void**) dxgi_factory.GetAddressOf());

    HR_B(dxgi_factory->CreateSwapChain,
        m_d3d_device.Get(), &sc_desc, 
        m_swap_chain.GetAddressOf());

    handle_resize();

    return true;
}

void D3DApp::calculate_frame_stats()
{

}

}