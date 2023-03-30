#include "Sample.h"

extern "C"
{
    __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

struct State
{
    int32_t mouse_button  = -1;
    int32_t window_width  = 0;
    int32_t window_height = 0;

    bool window_resized   = false;
    bool camera_changed   = false;
    bool minimized        = false;
};

// glfw callback

static inline void
windowSizeCallback(GLFWwindow* window, int32_t width, int32_t height)
{
    auto state = static_cast<State*>(glfwGetWindowUserPointer(window));

    if (state->minimized)
        return;

    ensureMinimumSize(width, height);

    state->window_width   = width;
    state->window_height  = height;
    state->window_resized = true;
    state->camera_changed = true;
}

static inline void
windowIconifyCallback(GLFWwindow* window, int32_t iconified)
{
    auto state       = static_cast<State*>(glfwGetWindowUserPointer(window));

    state->minimized = (iconified > 0);
}

// render helper function

static inline void
update(State& state, tputil::CudaOutputBuffer<uchar4>& pixel_buffer, Sample& sample)
{
    if (state.window_resized) {
        pixel_buffer.resize(state.window_width, state.window_height);
        sample.resize(state.window_width, state.window_height);
        state.window_resized = false;
    }
}

static inline void
displaySubframe(tputil::CudaOutputBuffer<uchar4>& pixel_buffer, tputil::GlDisplay& gl_display, GLFWwindow* window)
{
    int32_t res_width;
    int32_t res_height;
    glfwGetFramebufferSize(window, &res_width, &res_height);
    gl_display.display(pixel_buffer.width(), pixel_buffer.height(), res_width, res_height, pixel_buffer.getPbo());
}

int
main()
{
    static constexpr int32_t output_width  = 800;
    static constexpr int32_t output_height = 600;

    try {
        GLFWwindow* window = tputil::initGl("optix_practice", output_width, output_height);

        auto state         = State{};
        auto sample        = Sample{ output_width, output_height };
        auto gl_display    = tputil::GlDisplay{};
        auto pixel_buffer  = tputil::CudaOutputBuffer<uchar4>{ output_width, output_height };

        glfwSetWindowSizeCallback(window, windowSizeCallback);
        glfwSetWindowIconifyCallback(window, windowIconifyCallback);
        glfwSetWindowUserPointer(window, static_cast<void*>(&state));

        do {
            glfwPollEvents();
            update(state, pixel_buffer, sample);
            sample.render(pixel_buffer);
            displaySubframe(pixel_buffer, gl_display, window);
            glfwSwapBuffers(window);
        } while (!glfwWindowShouldClose(window));

    } catch (std::exception& e) {
        LOG_ERROR(std::format("main function caught exception: {}", e.what()));
    }

    glfwTerminate();

    return 0;
}