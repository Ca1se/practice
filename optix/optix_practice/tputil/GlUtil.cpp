#include "GlUtil.h"

#include <format>
#include <iostream>

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <cuda_runtime_api.h>

#include "Exception.h"

namespace tputil
{

namespace
{

void
glfwErrorCallback(int32_t error, const char* msg)
{
    std::cerr << std::format("GLFW Error {}: {}", error, msg) << std::endl;
}

GLFWwindow*
initGlfw(const std::string& title, int32_t width, int32_t height)
{
    glfwSetErrorCallback(glfwErrorCallback);
    if (!glfwInit())
        throw std::runtime_error(exceptionMsg(TPFAL, "Failed to initialize GLFW"));

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (window == nullptr)
        throw std::runtime_error(exceptionMsg(TPFAL, "Failed to create GLFW window"));

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    return window;
}

void
loadGl()
{
    if (!gladLoadGL())
        throw std::runtime_error(exceptionMsg(TPFAL, "Failed to Load GL"));

    GL_CHECK(glClearColor(0.212f, 0.271f, 0.31f, 1.0f));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
}

}  // namespace

GLFWwindow*
initGl(const std::string& title, int32_t width, int32_t height)
{
    GLFWwindow* window = initGlfw(title, width, height);
    loadGl();

    return window;
}

}  // namespace tputil