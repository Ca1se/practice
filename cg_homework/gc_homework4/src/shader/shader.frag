#version 330 core
out vec4 fragment_color;

void main() {
    fragment_color = vec4(0.0, float(0x80) / 0xff, float(0x40) / 0xff, 1.0);
}
