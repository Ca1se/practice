#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace gchw {

inline void windowSizeChangeCallback(GLFWwindow* window, int width, int height);

class GlfwUtils {
private:
    GlfwUtils();
    ~GlfwUtils();

public:
    GlfwUtils(const GlfwUtils&) = delete;
    GlfwUtils& operator = (const GlfwUtils&) = delete;

public:
    static GlfwUtils& getUtils() noexcept {
        static GlfwUtils utils;
        return utils;
    }

    GLFWwindow* createWindow(const std::string& title, int width, int height) const;
    
};

inline GlfwUtils& utils() noexcept {
    return GlfwUtils::getUtils();
}

void windowSizeChangeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

}
