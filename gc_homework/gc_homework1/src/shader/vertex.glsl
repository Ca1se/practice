#version 330 core
layout (location = 0) in ivec2 pos;

uniform int kWindowWidth;
uniform int kWindowHeight;

void main() {
    float x = 2.0f * (float(pos.x) / float(kWindowWidth - 1) - 0.5f);
    float y = 2.0f * (float(kWindowHeight - 1 - pos.y) / float(kWindowHeight - 1) - 0.5f);

    gl_Position = vec4(x, y, 0.0f, 1.0f);
}
