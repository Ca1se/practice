#include <cassert>
#include <cstdio>
#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.hpp"
#include "glfw_utils.hpp"
#include "uniform.hpp"
#include "matrix.hpp"

const float vertices[] = {
    -0.9f, -0.9f,
     0.9f, -0.9f,
     0.0f,  0.0f
};

static const int kWindowWidth  = 512;
static const int kWindowHeight = 512;

void drawLine(const gchw::Vector2d& start_point, const gchw::Vector2d& end_point, std::vector<int>& result) {
    assert(std::min(start_point.x(), end_point.x()) >= 0 && std::max(start_point.x(), end_point.x()) < kWindowWidth);
    assert(std::min(start_point.y(), end_point.y()) >= 0 && std::max(start_point.y(), end_point.y()) < kWindowHeight);

    if(start_point.x() == end_point.x()) {
        int x = start_point.x();
        int min_y = std::min(start_point.y(), end_point.y());
        int max_y = start_point.y() + end_point.y() - min_y;
        for(int y = min_y; y <= max_y; y++) {
            result.push_back(x);
            result.push_back(y);
        }
    }else if(start_point.y() == end_point.y()) {
        int y = start_point.y();
        int min_x = std::min(start_point.x(), end_point.x());
        int max_x = start_point.x() + end_point.x() - min_x;
        for(int x = min_x; x <= max_x; x++) {
            result.push_back(x);
            result.push_back(y);
        }
    }

    gchw::Vector2d sp = start_point;
    gchw::Vector2d ep = end_point;

    if(std::abs(start_point.x() - end_point.x()) >= std::abs(start_point.y() - end_point.y())) {
        if(sp.x() > ep.x()) sp.swap(ep);
        int sx = sp.x();
        int sy = sp.y();
        int ex = ep.x();
        int ey = ep.y();
        int y = sp.y();
        int d = 2 * ((ex - sx) * sy + (sy - ey) * sx + sx * ey - ex * sy);
        if(sp.y() < ep.y()) {
            d += 2 * (sy - ey) + ex - sx;
            for(int x = sp.x(); x <= ep.x(); x++) {
                result.push_back(x);
                result.push_back(y);
                if(d < 0) {
                    y++;
                    d += 2 * (sy - ey + ex - sx);
                }else {
                    d += 2 * (sy - ey);
                }
            }
        }else {
            d += 2 * (sy - ey) - ex + sx;
            for(int x = sp.x(); x <= ep.x(); x++) {
                result.push_back(x);
                result.push_back(y);
                if(d > 0) {
                    y--;
                    d += 2 * (sy - ey - ex + sx);
                }else {
                    d += 2 * (sy - ey);
                }
            }
        }
    }else {
        if(sp.y() > ep.y()) sp.swap(ep);
        int sx = sp.x();
        int sy = sp.y();
        int ex = ep.x();
        int ey = ep.y();
        int x = sp.x();
        int d = 2 * ((sx - ex) * sy + (ey - sy) * sx + ex * sy - sx * ey);
        if(sp.x() < ep.x()) {
            d += 2 * (sx - ex) + ey - sy;
            for(int y = sp.y(); y <= ep.y(); y++) {
                result.push_back(x);
                result.push_back(y);
                if(d < 0) {
                    x++;
                    d += 2 * (sx - ex + ey - sy);
                }else {
                    d += 2 * (sx - ex);
                }
            }
        }else {
            d += 2 * (sx - ex) - ey + sy;
            for(int y = sp.y(); y <= ep.y(); y++) {
                result.push_back(x);
                result.push_back(y);
                if(d > 0) {
                    x--;
                    d += 2 * (sx - ex - ey + sy);
                }else {
                    d += 2 * (sx - ex);
                }
            }
        }
    }
}

int main() {
    auto* window = gchw::utils().createWindow("gchw1", kWindowWidth, kWindowHeight);

    std::vector<int> line;
    drawLine(gchw::Vector2d{10, 10}, gchw::Vector2d{170, 500}, line);

    uint32_t vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    uint32_t vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, line.size() * sizeof(int), line.data(), GL_STATIC_DRAW);

    gchw::Shader shader;
    if(!shader.prepareShader(gchw::Shader::kVertexShader, gchw::Path("vertex.glsl"))) {
        std::cout << shader.get_error_log() << "\n";
        return 0;
    }
    if(!shader.prepareShader(gchw::Shader::kFragmentShader, gchw::Path("fragment.glsl"))) {
        std::cout << shader.get_error_log() << "\n";
        return 0;
    }

    glVertexAttribIPointer(0, 2, GL_INT, 2 * sizeof(int), (void*) 0);
    glEnableVertexAttribArray(0);

    shader.use();
    shader.setUniform<gchw::Int>("kWindowWidth", 1, &kWindowWidth);
    shader.setUniform<gchw::Int>("kWindowHeight", 1, &kWindowHeight);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_POINTS, 0, line.size() / 2);
        glfwSwapBuffers(window);
    }
    
    return 0;
}

