#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "shader.hpp"
#include "glfw_utils.hpp"

const float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
};

int main() {
    auto* window = gchw::utils().createWindow("gchw1", 800, 600);

    uint32_t vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    uint32_t vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);

    gchw::Shader shader;
    shader.prepareShader(gchw::Shader::kVertexShader, gchw::Path("vertex.glsl"));
    shader.prepareShader(gchw::Shader::kFragmentShader, gchw::Path("fragment.glsl"));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    shader.use();


    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float time_value = glfwGetTime();
        float green_value = (std::sin(time_value) / 2.0f) + 0.5f;
        glUniform4

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

