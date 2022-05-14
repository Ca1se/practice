#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "matrix.hpp"
#include "glfw_utils.hpp"
#include "shader.hpp"
#include "uniform.hpp"


constexpr float kPi = 3.141593;
const int kWindowWidth  = 800;
const int kWindowHeight = 600;

struct Camera {
    Camera(Vector3f target, Vector3f view, Vector3f up): target(target), view(view), up(up) {}
    Vector3f target;
    Vector3f view;
    Vector3f up;
};

inline std::vector<float> generateTs(float step_size) noexcept {
    assert(step_size <= 1);

    std::vector<float> ret;

    for(float i = 0; i < 1; i += step_size) {
        ret.push_back(i);
    }
    ret.push_back(1);

    return ret;
}

inline Matrix4f calViewMatrix(const Camera& camera) {
    Vector3f w = Vector3f{camera.view - camera.target}.normalized();
    Vector3f u = camera.up.cross(w).normalized();
    Vector3f v = w.cross(u).normalized();
    const Vector3f& e = camera.view;

    return Matrix4f{
        u.x(), u.y(), u.z(), -u.x() * e.x() - u.y() * e.y() - u.z() * e.z(),
        v.x(), v.y(), v.z(), -v.x() * e.x() - v.y() * e.y() - v.z() * e.z(),
        w.x(), w.y(), w.z(), -w.x() * e.x() - w.y() * e.y() - w.z() * e.z(),
        0, 0, 0, 1
    };
}

inline Matrix4f calProjectionMatrix(float fov, float aspect, float near, float far) {
    float r = fov / 2 / 180 * kPi;
    float top = -tan(r) * near;
    float right = top * aspect;

    // perspective
    return Matrix4f{
        near / right, 0, 0, 0,
        0, near / top, 0, 0,
        0, 0, (near + far) / (near - far), -2 * near * far / (near - far),
        0, 0, 1, 0
    };
}

std::vector<Vector3f> g_control_points {
    Vector3f{ 0, 200, 0 },
    Vector3f{ 0, 0, 0 },
    Vector3f{ 200, 0, 0 }
};

int main() {
    auto* window = gchw::utils().createWindow("gc_homework3", kWindowWidth, kWindowHeight);

    gchw::Shader shader;

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

    Camera camera(Vector3f{0, 0, 0}, Vector3f{0, 0, 30}, Vector3f{0, 1, 0});
    Matrix4f view_matrix = calViewMatrix(camera);
    Matrix4f perspective_matrix = calProjectionMatrix(60, (float) kWindowWidth / kWindowHeight, -0.1, -10000);
    Matrix4f mvp = perspective_matrix * view_matrix;

    /*
    for(auto& point: g_control_points) {
        point.x() /= kWindowWidth / 2.0f;
        point.y() /= kWindowHeight / 2.0f;
    }

    shader.use();
    shader.setUniform<gchw::FVec3>("u_control_points", 
            g_control_points.size(), (const float*) g_control_points.data());

    const std::vector<float> ts = generateTs(0.0025);

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
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_POINTS, 0, ts.size());
        glfwSwapBuffers(window);
    }
    */

    gchw::utils().terminate();

    return 0;
}
