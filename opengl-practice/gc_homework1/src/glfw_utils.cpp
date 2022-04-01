#include "glfw_utils.hpp"

namespace gchw {

GlfwUtils::GlfwUtils() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GlfwUtils::~GlfwUtils() {
    glfwTerminate();
}

GLFWwindow* GlfwUtils::createWindow(const std::string& title, int width, int height) const {
    GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if(window == nullptr)
        return nullptr;

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        glfwDestroyWindow(window);
        return nullptr;
    }

    glfwSetFramebufferSizeCallback(window, windowSizeChangeCallback);

    return window;
}

}
