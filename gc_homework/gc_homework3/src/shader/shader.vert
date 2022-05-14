#version 330 core
layout (location = 0) in float t;

uniform vec3 u_control_points[3];

int factorial(int k) {
    int tmp = k, ret = 1;
    while(tmp > 1) {
        ret *= tmp--;
    }
    return ret;
}

int cnk(int n, int k) {
    return factorial(n) / factorial(k) / factorial(n - k);
}

float bernstein(int n, int i) {
    float tmp = 1 - t;
    return cnk(n, i) * pow(t, i) * pow(tmp, n - i);
}

vec3 bezier(int n) {
    vec3 ret = vec3(0);
    for(int i = 0; i < n + 1; i++) {
        ret += bernstein(n, i) * u_control_points[i];
    }
    return ret;
}

void main() {
    gl_Position = vec4(bezier(2), 1.0);
}
