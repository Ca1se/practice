#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace gchw {

class GlfwUtils {
private:
    GlfwUtils();
    ~GlfwUtils();

public:
    static GlfwUtils& getUtils() noexcept {
        static GlfwUtils utils;
        return utils;
    }

    GlfwUtils(const GlfwUtils&) = delete;
    GlfwUtils& operator = (const GlfwUtils&) = delete;

public:
    GLFWwindow* createWindow(const std::string& title, int width, int height) const;
        
    void terminate() const { glfwTerminate(); }
};

inline GlfwUtils& utils() noexcept {
    return GlfwUtils::getUtils();
}

inline void windowSizeChangeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

}
