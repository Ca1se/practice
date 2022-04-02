#include <cassert>
#include <iostream>
#include <vector>
#include <stack>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.hpp"
#include "glfw_utils.hpp"
#include "uniform.hpp"
#include "haoframelinedata.inc"


static const int kWindowWidth  = 512;
static const int kWindowHeight = 512;

inline int getIndex(int x, int y) {
    return y * kWindowWidth + x;
}

inline void storePoint(int x, int y, std::vector<int>& mp, std::vector<int>& result) {
    result.push_back(x);
    result.push_back(y);
    mp[getIndex(x, y)] = 1;
}

void drawLine(const std::pair<int, int>& start_point, const std::pair<int, int>& end_point,
        std::vector<int>& mp, std::vector<int>& result) {
    if(start_point.first == end_point.first) {
        int x = start_point.first;
        int min_y = std::min(start_point.second, end_point.second);
        int max_y = start_point.second + end_point.second - min_y;
        for(int y = min_y; y <= max_y; y++)
            storePoint(x, y, mp, result);
    }else if(start_point.second == end_point.second) {
        int y = start_point.second;
        int min_x = std::min(start_point.first, end_point.first);
        int max_x = start_point.first + end_point.first - min_x;
        for(int x = min_x; x <= max_x; x++)
            storePoint(x, y, mp, result);
    }

    auto sp = start_point;
    auto ep = end_point;

    if(std::abs(start_point.first - end_point.first) >= std::abs(start_point.second - end_point.second)) {
        if(sp.first > ep.first) sp.swap(ep);
        int sx = sp.first, sy = sp.second;
        int ex = ep.first, ey = ep.second;
        int y = sp.second;
        int d = 2 * ((ex - sx) * sy + (sy - ey) * sx + sx * ey - ex * sy);
        int mul = sy < ey ? 1 : -1;
        d += 2 * (sy - ey) + mul * (ex - sx);
        for(int x = sx; x <= ex; x++) {
            storePoint(x, y, mp, result);
            if(d * mul < 0) {
                y += mul;
                d += 2 * (sy - ey + mul * (ex - sx));
            }else {
                d += 2 * (sy - ey);
            }
        }
    }else {
        if(sp.second > ep.second) sp.swap(ep);
        int sx = sp.first, sy = sp.second;
        int ex = ep.first, ey = ep.second;
        int x = sp.first;
        int d = 2 * ((sx - ex) * sy + (ey - sy) * sx + ex * sy - sx * ey);
        int mul = sx < ex ? 1 : -1;
        d += 2 * (sx - ex) + mul * (ey - sy);
        for(int y = sy; y <= ey; y++) {
            storePoint(x, y, mp, result);
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

void drawCircle(const std::pair<int, int>& center, int radius, std::vector<int>& result) {
    int p = 1 - radius;
    int ax = 0;
    int ay = radius;
    drawCircleAux(center.first, center.second, ax, ay, result);
    while(ax++ < ay) {
        if(p < 0) {
            p += 2 * ax + 1;
        }else {
            ay--;
            p += 2 * (ax - ay) + 1;
        }
        drawCircleAux(center.first, center.second, ax, ay, result);
    }
}

void floodfill(const std::pair<int, int>& seed, std::vector<int>& mp, std::vector<int>& result) {
    const int step[][2] = { 1, 0, 0, 1, -1, 0, 0, -1 };
    
    int x, y;
    std::stack<std::pair<int, int>> s;
    s.push(seed);
    storePoint(seed.first, seed.second, mp, result);
    while(!s.empty()) {
        auto [px, py] = s.top();
        s.pop();
        for(int i = 0; i < 4; i++) {
            x = px + step[i][0];
            y = py + step[i][1];
            if(x >= 0 && x < kWindowWidth && y >= 0 && y < kWindowHeight && mp[getIndex(x, y)] == 0) {
                s.emplace(x, y);
                storePoint(x, y, mp, result);
            }
        }
    }
}

inline void drawHaoAux(const int* arr, int length, std::vector<int>& mp, std::vector<int>& result) {
    int ind;
    for(int i = 0; i < length; i += 2) {
        ind = (i + 2) % length;
        drawLine({ arr[i], arr[i + 1] }, { arr[ind], arr[ind + 1] }, mp, result);
    }
}

inline void drawHao(std::vector<int>& mp, std::vector<int>& result) {
    drawHaoAux(kHaoPart1, sizeof kHaoPart1 / sizeof(int), mp, result);
    drawHaoAux(kHaoPart2, sizeof kHaoPart2 / sizeof(int), mp, result);
    drawHaoAux(kHaoPart3White, sizeof kHaoPart3White / sizeof(int), mp, result);
    drawHaoAux(kHaoPart4, sizeof kHaoPart4 / sizeof(int), mp, result);
    drawHaoAux(kHaoPart5, sizeof kHaoPart5 / sizeof(int), mp, result);
    floodfill({kHaoPart1[0] + 1, kHaoPart1[1] + 1}, mp, result);
    floodfill({kHaoPart2[0] + 1, kHaoPart2[1] + 1}, mp, result);
    floodfill({kHaoPart4[0] + 1, kHaoPart4[1] + 1}, mp, result);
    floodfill({kHaoPart5[0] + 1, kHaoPart5[1] + 1}, mp, result);
}

int main() {
    auto* window = gchw::utils().createWindow("gchw1", kWindowWidth, kWindowHeight);

    std::vector<int> points;
    std::vector<int> mp(kWindowWidth * kWindowHeight, 0);
    drawHao(mp, points);

    uint32_t vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    uint32_t vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(int), points.data(), GL_STATIC_DRAW);

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
        glDrawArrays(GL_POINTS, 0, points.size() / 2);
        glfwSwapBuffers(window);
    }
    
    return 0;
}

