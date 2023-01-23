#ifndef D3D_APP
#define D3D_APP


#include <cstdint>
#include <stdint.h>
#include <string>

#include <d3d11.h>
#include <d3dcommon.h>
#include <dxgi.h>
#include <windows.h>
#include <wrl/client.h>

#include "game_timer.hpp"


namespace t7d3d {

class D3DApp {
private:
    D3DApp(HINSTANCE inst);
public:
    virtual ~D3DApp();

    HINSTANCE app_instance() const noexcept;
    HWND main_window() const noexcept;
    float aspect_ratio() const noexcept;

    int run();

    virtual void update_scene(float dt) = 0;
    virtual void draw_scene() = 0;

    virtual bool init();
    virtual LRESULT msg_proc(HWND hwnd, uint32_t msg, WPARAM wparam, LPARAM lparam);
    virtual void handle_resize();

    virtual void handle_mouse_down(WPARAM btn_state, int x, int y) {}
    virtual void handle_mouse_up(WPARAM btn_state, int x, int y) {}
    virtual void handle_mouse_move(WPARAM btn_state, int x, int y) {}

protected:
    bool init_main_window();
    bool init_direct3d();
    
    void calculate_frame_stats();

protected:
    HINSTANCE m_app_instance;
    HWND m_main_window;

    bool m_paused;
    bool m_minimized;
    bool m_maximized;
    bool m_resizing;

    uint32_t m_msaa4x_quality;

    GameTimer m_timer;

    Microsoft::WRL::ComPtr<ID3D11Device>            m_d3d_device;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3d_context;
    Microsoft::WRL::ComPtr<IDXGISwapChain>          m_swap_chain;
    Microsoft::WRL::ComPtr<ID3D11Texture2D>         m_depth_buffer;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_render_target_view;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_depth_buffer_view;

    D3D11_VIEWPORT m_viewport;

    std::wstring m_window_title;

    D3D_DRIVER_TYPE m_d3d_driver_type;

    int m_client_width;
    int m_client_height;

    bool m_msaa4x_enabled;
};

}

#endif