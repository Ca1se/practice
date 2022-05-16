#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "matrix.hpp"
#include "glfw_utils.hpp"
#include "shader.hpp"
#include "uniform.hpp"
#include "camera.hpp"


inline std::vector<float> generateTs(float step_size) noexcept {
    assert(step_size <= 1);

    std::vector<float> ret;

    for(float i = 0; i < 1; i += step_size) {
        ret.push_back(i);
    }
    ret.push_back(1);

    return ret;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 9.0f));
float lastX = (float)SCR_WIDTH / 2.0;
float lastY = (float)SCR_HEIGHT / 2.0;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;


std::vector<Vector3f> g_control_points[4] = {
    {
        Vector3f{ 0, 2, 0 }, Vector3f{ 2.5, 1, 0 }, Vector3f{ 2.5, -1, 0 }, Vector3f{ 0, -2, 0 },
        Vector3f{ 0, 2, 0 }, Vector3f{ 1.7678, 1, -1.7678 }, Vector3f{ 1.7678, -1, -1.7678 }, Vector3f{ 0, -2, 0 },
        Vector3f{ 0, 2, 0 }, Vector3f{ 0, 1, -2.5 }, Vector3f{ 0, -1, -2.5 }, Vector3f{ 0, -2, 0 },
    },
    {
        Vector3f{ 0, 2, 0 }, Vector3f{ 0, 1, -2.5 }, Vector3f{ 0, -1, -2.5 }, Vector3f{ 0, -2, 0 },
        Vector3f{ 0, 2, 0 }, Vector3f{ -1.7678, 1, -1.7678 }, Vector3f{ -1.7678, -1, -1.7678 }, Vector3f{ 0, -2, 0 },
        Vector3f{ 0, 2, 0 }, Vector3f{ -2.5, 1, 0 }, Vector3f{ -2.5, -1, 0 }, Vector3f{ 0, -2, 0 },
    },
    {
        Vector3f{ 0, 2, 0 }, Vector3f{ -2.5, 1, 0 }, Vector3f{ -2.5, -1, 0 }, Vector3f{ 0, -2, 0 },
        Vector3f{ 0, 2, 0 }, Vector3f{ -1.7678, 1, 1.7678 }, Vector3f{ -1.7678, -1, 1.7678 }, Vector3f{ 0, -2, 0 },
        Vector3f{ 0, 2, 0 }, Vector3f{ 0, 1, 2.5 }, Vector3f{ 0, -1, 2.5 }, Vector3f{ 0, -2, 0 },
    },
    {
        Vector3f{ 0, 2, 0 }, Vector3f{ 0, 1, 2.5 }, Vector3f{ 0, -1, 2.5 }, Vector3f{ 0, -2, 0 },
        Vector3f{ 0, 2, 0 }, Vector3f{ 1.7678, 1, 1.7678 }, Vector3f{ 1.7678, -1, 1.7678 }, Vector3f{ 0, -2, 0 },
        Vector3f{ 0, 2, 0 }, Vector3f{ 2.5, 1, 0 }, Vector3f{ 2.5, -1, 0 }, Vector3f{ 0, -2, 0 },
    }
};

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    gchw::Shader shader(true);

    if(!shader.prepareShader(gchw::Shader::kVertexShader, gchw::Path("shader.vert"))) {
        std::cout << shader.get_error_log() << std::endl;
        gchw::utils().terminate();
        return 0;
    }

    if(!shader.prepareShader(gchw::Shader::kFragmentShader, gchw::Path("shader.frag"))) {
        std::cout << shader.get_error_log() << std::endl;
        gchw::utils().terminate();
        return 0;
    }

    if(!shader.prepareShader(gchw::Shader::kGeometryShader, gchw::Path("shader.geom"))) {
        std::cout << shader.get_error_log() << std::endl;
        gchw::utils().terminate();
        return 0;
    }
    
    glm::mat4 pers = glm::perspective(glm::radians(45.0f), (float) SCR_WIDTH / SCR_HEIGHT, 1.0f, 100.0f);

    if(!shader.use()) {
        std::cout << shader.get_error_log() << std::endl;
        gchw::utils().terminate();
        return 0;
    }

    shader.setUniformMatrix<gchw::FMat4>("u_p", 1, false, &pers[0][0]);

    const std::vector<float> ts = generateTs(0.01);

    uint32_t vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    uint32_t vbo;
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * ts.size(), ts.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    while(!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = camera.GetViewMatrix();
        shader.setUniformMatrix<gchw::FMat4>("u_v", 1, false, &view[0][0]);

        for(int i = 0; i < 4; i++) {
            shader.setUniform<gchw::FVec3>("u_control_points", 12, (const float*) g_control_points[i].data());
            glDrawArrays(GL_POINTS, 0, ts.size());
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// reference from https://learnopengl.com/code_viewer_gh.php?code=src/4.advanced_opengl/9.3.geometry_shader_normals/normal_visualization.cpp

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
