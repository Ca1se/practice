#version 330 core
out vec4 fragment_color;

uniform float green;

void main() {
    fragment_color = vec4(green, green, green, green);
}
