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


static const int kWindowWidth  = 512;
static const int kWindowHeight = 512;

void drawLine(const gchw::Vector2i& start_point, const gchw::Vector2i& end_point, std::vector<int>& result) {
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

    auto sp = start_point;
    auto ep = end_point;

    if(std::abs(start_point.x() - end_point.x()) >= std::abs(start_point.y() - end_point.y())) {
        if(sp.x() > ep.x()) sp.swap(ep);
        int sx = sp.x();
        int sy = sp.y();
        int ex = ep.x();
        int ey = ep.y();
        int y = sp.y();
        int d = 2 * ((ex - sx) * sy + (sy - ey) * sx + sx * ey - ex * sy);
        int mul = sp.y() < ep.y() ? 1 : -1;
        d += 2 * (sy - ey) + mul * (ex - sx);
        for(int x = sp.x(); x <= ep.x(); x++) {
            result.push_back(x);
            result.push_back(y);
            if(d * mul < 0) {
                y += mul;
                d += 2 * (sy - ey + mul * (ex - sx));
            }else {
                d += 2 * (sy - ey);
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
        int mul = sp.x() < ep.x() ? 1 : -1;
        d += 2 * (sx - ex) + mul * (ey - sy);
        for(int y = sp.y(); y <= ep.y(); y++) {
            result.push_back(x);
            result.push_back(y);
            if(d * mul < 0) {
                x += mul;
                d += 2 * (sx - ex + mul * (ey - sy));
            }else {
                d += 2 * (sx - ex);
            }
        }
    }
}

inline void drawCircleAux(int x, int y, int ax, int ay, std::vector<int>& result) {
    result.push_back(x + ax), result.push_back(y + ay);
    result.push_back(x - ax), result.push_back(y + ay);
    result.push_back(x + ay), result.push_back(y + ax);
    result.push_back(x - ay), result.push_back(y + ax);
    result.push_back(x + ay), result.push_back(y - ax);
    result.push_back(x - ay), result.push_back(y - ax);
    result.push_back(x + ax), result.push_back(y - ay);
    result.push_back(x - ax), result.push_back(y - ay);
}

void drawCircle(const gchw::Vector2d& center, int radius, std::vector<int>& result) {
    int p = 1 - radius;
    int ax = 0;
    int ay = radius;
    drawCircleAux(center.x(), center.y(), ax, ay, result);
    while(ax++ < ay) {
        if(p < 0) {
            p += 2 * ax + 1;
        }else {
            ay--;
            p += 2 * (ax - ay) + 1;
        }
        drawCircleAux(center.x(), center.y(), ax, ay, result);
    }
}

const int kHaoPart1[] = {
    132, 124,
    249, 124,
    249, 110,
    274, 110,
    274, 124,
    392, 124,
    392, 148,
    132, 148
};

const int kHaoPart2[] = {
    161, 156,
    360, 156,
    360, 205,
    161, 205
};

const int kHaoPart3White[] = {
    184, 175,
    337, 175,
    337, 186,
    184, 186
};

const int kHaoPart4[] = {
    127, 214,
    382, 214,
    402, 225,
    399, 251,
    390, 276,
    369, 269,
    373, 254,
    375, 238,
    150, 238,
    150, 271,
    127, 271
};

const int kHaoPart5[] = {
    163, 247,
    359, 247,
    359, 266,
    273, 266,
    305, 308,
    350, 281,
    366, 300,
    324, 326,
    354, 348,
    392, 366,
    377, 388,
    334, 365,
    298, 336,
    295, 356,
    288, 375,
    274, 387,
    259, 390,
    225, 384,
    225, 362,
    254, 366,
    268, 356,
    272, 337,
    226, 359,
    167, 378,
    138, 383,
    130, 360,
    177, 352,
    224, 337,
    271, 313,
    269, 302,
    214, 329,
    173, 341,
    141, 347,
    133, 323,
    165, 319,
    216, 303,
    258, 284,
    248, 276,
    207, 295,
    164, 307,
    143, 309,
    136, 287,
    167, 283,
    221, 266,
    163, 266
};

inline void drawHaoAux(const int* arr, int length, std::vector<int>& result) {
    int ind;
    for(int i = 0; i < length; i += 2) {
        ind = (i + 2) % length;
        drawLine(gchw::Vector2i{ arr[i], arr[i + 1] }, gchw::Vector2i{ arr[ind], arr[ind + 1] }, result);
    }
}

void drawHao(std::vector<int>& result) {
    drawHaoAux(kHaoPart1, sizeof kHaoPart1 / sizeof(int), result);
    drawHaoAux(kHaoPart2, sizeof kHaoPart2 / sizeof(int), result);
    drawHaoAux(kHaoPart3White, sizeof kHaoPart3White / sizeof(int), result);
    drawHaoAux(kHaoPart4, sizeof kHaoPart4 / sizeof(int), result);
    drawHaoAux(kHaoPart5, sizeof kHaoPart5 / sizeof(int), result);
}

int main() {
    auto* window = gchw::utils().createWindow("gchw1", kWindowWidth, kWindowHeight);

    std::vector<int> lines;
    drawHao(lines);

    uint32_t vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    uint32_t vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, lines.size() * sizeof(int), lines.data(), GL_STATIC_DRAW);

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
        glDrawArrays(GL_POINTS, 0, lines.size() / 2);
        glfwSwapBuffers(window);
    }
    
    return 0;
}

