#include <cstring>
#include <iostream>
#include <vector>
#include <stack>
#include <tuple>
#include <cassert>
#include <cmath>
#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "matrix.hpp"
#include "shader.hpp"
#include "uniform.hpp"
#include "camera.hpp"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

inline Matrix4f matGlmToGchw(const glm::mat4& glm_mat) noexcept {
    Matrix4f ret;
    memcpy(ret.data(), &glm_mat[0][0], 16 * sizeof(float));
    return ret;
}

std::string generateAxiom(int n) noexcept {
    const char* const rule = "F[++F-F-F][-F+F+F][**F/F/F][/F*F*F]";
    std::string ret = "F";

    for(int i = 0; i < n; i++) {
        for(int k = 0; k < ret.size();) {
            if(ret[k] == 'F') {
                ret.insert(k + 1, rule);
                k += strlen(rule) + 1;
                continue;
            }
            k++;
        }
    }

    return ret;
}

std::vector<Vector3f> generatePoints(const Vector3f& origin) noexcept {
    const std::string axiom = generateAxiom(3);
    const float d = 0.1;
    const float pi = std::acos(-1);
    const float theta = 20 / 180.0 * pi;

    std::vector<Vector3f> ret;

    std::tuple<Vector3f, float, float> now = std::make_tuple(origin, 0, 0);
    std::stack<std::tuple<Vector3f, float, float>> st;
    for(char ch: axiom) {
        auto& [pos, radx, radz] = now;
        switch (ch) {
            case 'F':
                ret.push_back(pos);
                pos.y() += 0.5 * d * (cos(radx) + cos(radz));
                pos.x() += sin(radx) * d;
                pos.z() += sin(radz) * d;
                ret.push_back(pos);
                break;
            case '[':
                st.push(now);
                break;
            case ']':
                now = st.top();
                st.pop();
                break;
            case '+':
                radx += theta;
                break;
            case '-':
                radx -= theta;
                break;
            case '*':
                radz += theta;
                break;
            case '/':
                radz -= theta;
                break;
            default:;
        }
    }

    return ret;
}

// settings
const uint32_t kWindowWidth = 800;
const uint32_t kWindowHeight = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 9.0f));
float lastX = (float) kWindowWidth / 2.0;
float lastY = (float) kWindowHeight / 2.0;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;


int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(kWindowWidth, kWindowHeight, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
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

    gchw::Shader shader;

    if(!shader.prepareShader(gchw::Shader::kVertexShader, gchw::Path("shader.vert"))) {
        std::cout << shader.get_error_log() << std::endl;
        glfwTerminate();
        return 0;
    }

    if(!shader.prepareShader(gchw::Shader::kFragmentShader, gchw::Path("shader.frag"))) {
        std::cout << shader.get_error_log() << std::endl;
        glfwTerminate();
        return 0;
    }
    
    Matrix4f pers = matGlmToGchw(glm::perspective(glm::radians(45.0f), (float) kWindowWidth / kWindowHeight, 1.0f, 100.0f));

    if(!shader.use()) {
        std::cout << shader.get_error_log() << std::endl;
        glfwTerminate();
        return 0;
    }

    shader.setUniformMatrix<gchw::FMat4>("u_p", 1, false, pers.data());

    std::vector<Vector3f> lines = generatePoints(Vector3f{ 0, 0, 0 });

    uint32_t vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    uint32_t vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float) * lines.size(), lines.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    while(!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Matrix4f view = matGlmToGchw(camera.GetViewMatrix());
        shader.setUniformMatrix<gchw::FMat4>("u_v", 1, false, view.data());

        glDrawArrays(GL_LINES, 0, lines.size());

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
