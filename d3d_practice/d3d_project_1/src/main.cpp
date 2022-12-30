#include <cstdint>
#include <cassert>

#include <d3d11.h>
#include <d3dcommon.h>

#include <dxgi.h>
#include <dxgiformat.h>
#include <dxgitype.h>
#include <minwindef.h>
#include <stdio.h>
#include <windows.h>
#include <windowsx.h>
#include <winerror.h>
#include <winnt.h>
#include <winuser.h>
#include <tchar.h>


const uint32_t client_width     = 640;
const uint32_t client_height    = 480;

LRESULT CALLBACK WindowProc(HWND hWnd,
                         UINT message,
                         WPARAM wParam,
                         LPARAM lParam);

int CALLBACK WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     pCmdLine,
    int       nShowCmd
) {
    // the handle for the window, filled by a function
    HWND hWnd;
    // this struct holds information for the window class
    WNDCLASSEX wc;

    // clear out the window class for use
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    // fill in the struct with the needed information
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
    wc.lpszClassName = _T("WindowClass1");

    // register the window class
    RegisterClassEx(&wc);

    // create the window and use the result as the handle
    hWnd = CreateWindowEx(0,
                          _T("WindowClass1"),    // name of the window class
                          _T("HelloWorld"),   // title of the window
                          WS_OVERLAPPEDWINDOW,    // window style
                          300,    // x-position of the window
                          300,    // y-position of the window
                          client_width,    // width of the window
                          client_height,    // height of the window
                          nullptr,    // we have no parent window, NULL
                          nullptr,    // we aren't using menus, NULL
                          hInstance,    // application handle
                          nullptr);    // used with multiple windows, NULL

    // display the window on the screen
    ShowWindow(hWnd, nShowCmd);

    

    uint32_t create_device_flag = D3D11_CREATE_DEVICE_DEBUG;

    ID3D11Device* d3d_device                = nullptr;
    ID3D11DeviceContext* d3d_device_context = nullptr;
    D3D_FEATURE_LEVEL check_result;

    {
        HRESULT hr = D3D11CreateDevice(nullptr,
                        D3D_DRIVER_TYPE_HARDWARE,
                        nullptr,
                        create_device_flag,
                        nullptr,
                        0,
                        D3D11_SDK_VERSION,
                        &d3d_device,
                        &check_result,
                        &d3d_device_context);
        
        if(FAILED(hr)) {
            MessageBox(0, _T("D3D11CreateDevice Failed."), 0, 0);
            return 0;
        }
        if(check_result != D3D_FEATURE_LEVEL_11_0) {
            MessageBox(0, _T("Direct3D Feature Level 11 unsupported."), 0, 0);
            return 0;
        }
    }

    uint32_t msaa4x_quality;

    {
        HRESULT hr = d3d_device->CheckMultisampleQualityLevels(
            DXGI_FORMAT_R8G8B8A8_UNORM, 4, &msaa4x_quality);
        if(FAILED(hr)) {
            MessageBox(0, "ID3D11Device::CheckMultisampleQualityLevels Failed.", 0, 0);
            return 0;
        }
        assert(msaa4x_quality > 0);
    }

    DXGI_SWAP_CHAIN_DESC swap_chain_desc;

    swap_chain_desc.BufferDesc.Width                    = client_width;
    swap_chain_desc.BufferDesc.Height                   = client_height;
    swap_chain_desc.BufferDesc.RefreshRate.Numerator    = 60;
    swap_chain_desc.BufferDesc.RefreshRate.Denominator  = 1;
    swap_chain_desc.BufferDesc.Format                   = DXGI_FORMAT_R8G8B8A8_UNORM;
    swap_chain_desc.BufferDesc.ScanlineOrdering         = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swap_chain_desc.BufferDesc.Scaling                  = DXGI_MODE_SCALING_UNSPECIFIED;

    swap_chain_desc.SampleDesc.Count                    = 4;
    swap_chain_desc.SampleDesc.Quality                  = msaa4x_quality - 1;

    swap_chain_desc.BufferUsage                         = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swap_chain_desc.BufferCount                         = 1;
    swap_chain_desc.OutputWindow                        = hWnd;
    swap_chain_desc.Windowed                            = true;
    swap_chain_desc.SwapEffect                          = DXGI_SWAP_EFFECT_DISCARD;
    swap_chain_desc.Flags                               = 0;

    IDXGIDevice* dxgi_device = nullptr;
    {
        HRESULT hr = d3d_device->QueryInterface(__uuidof(IDXGIDevice),
            (void**) &dxgi_device);
        if(FAILED(hr)) {
            MessageBox(0, _T("ID3D11Device::QueryInterface Failed."), 0, 0);
            return 0;
        }
    }

    IDXGIAdapter* dxgi_adapter = nullptr;
    {
        HRESULT hr = dxgi_device->GetParent(__uuidof(IDXGIAdapter),
            (void**) &dxgi_adapter);
        if(FAILED(hr)) {
            MessageBox(0, _T("IDXGIAdapter::GetParent Failed."), 0, 0);
            return 0;
        }
    }

    IDXGIFactory* dxgi_factory = nullptr;
    {
        HRESULT hr = dxgi_adapter->GetParent(__uuidof(IDXGIFactory),
            (void**) &dxgi_factory);
        if(FAILED(hr)) {
            MessageBox(0, _T("IDXGIFactory::GetParent Failed."), 0, 0);
            return 0;
        }
    }

    IDXGISwapChain* swap_chain = nullptr;
    {
        HRESULT hr = dxgi_factory->CreateSwapChain(d3d_device,
            &swap_chain_desc, &swap_chain);
        if(FAILED(hr)) {
            MessageBox(0, _T("IDXGIFactory::CreateSwapChain Failed."), 0, 0);
            return 0;
        }
    }

    dxgi_device->Release();
    dxgi_adapter->Release();
    dxgi_factory->Release();

    ID3D11RenderTargetView* back_buffer_view = nullptr;
    ID3D11Texture2D* back_buffer = nullptr;

    {
        HRESULT hr = swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**) &back_buffer);
        if(FAILED(hr)) {
            MessageBox(nullptr, "IDXGISwapChain::GetBuffer Failed.", nullptr, 0);
            return 0;
        }
    }

    {
        HRESULT hr = d3d_device->CreateRenderTargetView(back_buffer, nullptr, &back_buffer_view);
        if(FAILED(hr)) {
            MessageBox(nullptr, "ID3D11Device::CreateRenderTargetView Failed.", nullptr, 0);
            return 0;
        }
    }

    back_buffer->Release();

    D3D11_TEXTURE2D_DESC depth_buffer_desc;
    depth_buffer_desc.Width                 = client_width;
    depth_buffer_desc.Height                = client_height;
    depth_buffer_desc.MipLevels             = 1;
    depth_buffer_desc.ArraySize             = 1;
    depth_buffer_desc.Format                = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depth_buffer_desc.Usage                 = D3D11_USAGE_DEFAULT;
    depth_buffer_desc.BindFlags             = D3D11_BIND_DEPTH_STENCIL;
    depth_buffer_desc.CPUAccessFlags        = 0;
    depth_buffer_desc.MiscFlags             = 0;
    depth_buffer_desc.SampleDesc.Count      = 4;
    depth_buffer_desc.SampleDesc.Quality    = msaa4x_quality - 1;

    ID3D11Texture2D* depth_buffer           = nullptr;
    ID3D11DepthStencilView* depth_view      = nullptr;

    {
        HRESULT hr = d3d_device->CreateTexture2D(&depth_buffer_desc, nullptr, &depth_buffer);
        if(FAILED(hr)) {
            MessageBox(nullptr, "ID3D11Device::CreateTexture2D Failed.", nullptr, 0);
            return 0;
        }
    }

    {
        HRESULT hr = d3d_device->CreateDepthStencilView(depth_buffer, nullptr, &depth_view);
        if(FAILED(hr)) {
            MessageBox(nullptr, "ID3D11Device::CreateDepthStencilView Failed.", nullptr, 0);
            return 0;
        }
    }

    d3d_device_context->OMSetRenderTargets(1, &back_buffer_view, depth_view);

    D3D11_VIEWPORT viewport;
    viewport.TopLeftX   = 0;
    viewport.TopLeftY   = 0;
    viewport.Width      = (float) client_width;
    viewport.Height     = (float) client_height;
    viewport.MinDepth   = 0;
    viewport.MaxDepth   = 1;

    d3d_device_context->RSSetViewports(1, &viewport);

    // enter the main loop:

    // this struct holds Windows event messages
    MSG msg;

    // wait for the next message in the queue, store the result in 'msg'
    while(GetMessage(&msg, nullptr, 0, 0))
    {
        // translate keystroke messages into the right format
        TranslateMessage(&msg);

        // send the message to the WindowProc function
        DispatchMessage(&msg);
    }

    d3d_device->Release();
    d3d_device_context->Release();

    return msg.wParam;
}

// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // sort through and find what code to run for the message given
    switch(message)
    {
        // this message is read when the window is closed
        case WM_DESTROY:
            {
                // close the application entirely
                PostQuitMessage(0);
                return 0;
            } break;
    }

    // Handle any messages the switch statement didn't
    return DefWindowProc (hWnd, message, wParam, lParam);
}