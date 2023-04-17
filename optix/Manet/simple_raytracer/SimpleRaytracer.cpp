#include "SimpleRaytracer.h"

#include "Sample.h"

extern "C"
{
    __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

// glfw callback

static inline void
windowSizeCallback(GLFWwindow* window, int32_t width, int32_t height)
{
    auto state = static_cast<State*>(glfwGetWindowUserPointer(window));

    assert(state != nullptr);

    if (state->minimized)
        return;

    ensureMinimumSize(width, height);

    state->output_size.width  = width;
    state->output_size.height = height;
    state->window_resized     = true;
    state->camera_changed     = true;
}

static inline void
windowIconifyCallback(GLFWwindow* window, int32_t iconified)
{
    auto state = static_cast<State*>(glfwGetWindowUserPointer(window));

    assert(state != nullptr);

    state->minimized = (iconified > 0);
}

static inline void
mouseButtonCallback(GLFWwindow* window, int32_t button, int32_t action, int32_t mods)
{
    auto state = static_cast<State*>(glfwGetWindowUserPointer(window));

    assert(state != nullptr);

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT) {
        state->prior_mouse_pos = make_int2(static_cast<int>(xpos), static_cast<int>(ypos));
        state->button_pressed  = true;
    } else {
        state->button_pressed = false;
    }
}

static inline void
cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    auto state = static_cast<State*>(glfwGetWindowUserPointer(window));

    assert(state != nullptr);

    if (state->button_pressed) {
        if (!glfwGetWindowAttrib(window, GLFW_HOVERED)) {
            state->button_pressed = false;
            return;
        }

        int2 now_mouse_pos = make_int2(static_cast<int32_t>(xpos), static_cast<int32_t>(ypos));
        state->camera.rotate(state->prior_mouse_pos,
                             now_mouse_pos,
                             make_int2(state->output_size.width, state->output_size.height));
        state->prior_mouse_pos = now_mouse_pos;
        state->camera_changed  = true;
    }
}

static inline void
scrollCallback(GLFWwindow* window, double xscroll, double yscroll)
{
    auto state = static_cast<State*>(glfwGetWindowUserPointer(window));

    assert(state != nullptr);
    
    state->camera.zoom(static_cast<int>(yscroll));
    state->camera_changed = true;
}

static inline void
keyCallback(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods)
{
    auto state = static_cast<State*>(glfwGetWindowUserPointer(window));

    assert(state != nullptr);

    if(action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch(key) {
        case GLFW_KEY_W:
            state->camera.move(make_float3(0.0f, 0.0f, 1.0f));
            break;
        case GLFW_KEY_S:
            state->camera.move(make_float3(0.0f, 0.0f, -1.0f));
            break;
        case GLFW_KEY_A:
            state->camera.move(make_float3(-1.0f, 0.0f, 0.0f));
            break;
        case GLFW_KEY_D:
            state->camera.move(make_float3(1.0f, 0.0f, 0.0f));
            break;
        case GLFW_KEY_SPACE:
            state->camera.move(make_float3(0.0f, 1.0f, 0.0f));
            break;
        case GLFW_KEY_LEFT_SHIFT:
            state->camera.move(make_float3(0.0f, -1.0f, 0.0f));
            break;
        }
        state->camera_changed = true;
    }
}

// render helper function

static inline void
update(State& state, Sample& sample)
{
    auto [width, height] = state.output_size;

    if (state.window_resized) {
        state.pixel_buffer.resize(width, height);
        state.window_resized = false;
    }

    if (state.camera_changed) {
        state.camera.setAspectRatio(static_cast<float>(width) / static_cast<float>(height));
        state.camera.update();
        sample.updateCamera(state.camera);
        state.camera_changed = false;
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

int main()
{
    static constexpr int32_t output_width  = 800;
    static constexpr int32_t output_height = 600;

    try {
        GLFWwindow* window = tputil::initGl("simple raytracer", output_width, output_height);

        State state = {
            .output_size = { .width = output_width, .height = output_height },
            .camera = Camera{
                make_float3(10.0f, 10.0f, 0.0f),
                make_float3(0.0f, 10.0f, 0.0f),
                make_float3(0.0f, 1.0f, 0.0f),
                TP_PIDIV2,
                static_cast<float>(output_width) / static_cast<float>(output_height)
            },
            .pixel_buffer = tputil::CudaOutputBuffer<uchar4>{ output_width, output_height },
        };

        tputil::Model model;
        tputil::loadObjModel(model, "sponza/sponza.obj");

        Sample sample{ model };

        tputil::GlDisplay gl_display;

        glfwSetWindowSizeCallback(window, windowSizeCallback);
        glfwSetWindowIconifyCallback(window, windowIconifyCallback);
        glfwSetMouseButtonCallback(window, mouseButtonCallback);
        glfwSetCursorPosCallback(window, cursorPosCallback);
        glfwSetScrollCallback(window, scrollCallback);
        glfwSetKeyCallback(window, keyCallback);
        glfwSetWindowUserPointer(window, static_cast<void*>(&state));

        do {
            glfwPollEvents();
            update(state, sample);
            sample.render(state);
            displaySubframe(state.pixel_buffer, gl_display, window);
            glfwSwapBuffers(window);
        } while (!glfwWindowShouldClose(window));
    } catch (std::exception& e) {
        LOG_ERROR(std::format("main function caught exception: {}", e.what()));
    }

    glfwTerminate();

    return 0;
}