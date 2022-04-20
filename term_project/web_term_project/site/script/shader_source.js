const kLineVsSource =
`#version 300 es
layout (location = 0) in vec2 aVertexPos;
void main() {
    gl_Position = vec4(aVertexPos, 0, 1);
}`;

const kLineFsSource =
`#version 300 es
precision mediump float;
out vec4 oFragColor;
void main() {
    oFragColor = vec4(0.0, 0.0, 0.0, 1.0);
}`;

export {
    kLineVsSource,
    kLineFsSource
}