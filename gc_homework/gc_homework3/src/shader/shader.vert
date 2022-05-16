#version 330 core
layout (location = 0) in float t;

uniform vec3 u_control_points[12];

out VS_OUT {
    vec3 control_points[3];
} vs_out;

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

vec3 bezier(int n, int r) {
    vec3 ret = vec3(0.0);
    int idx = r * 4;
    for(int i = 0; i < n + 1; i++) {
        ret += bernstein(n, i) * u_control_points[idx++];
    }
    return ret;
}

void main() {
    for(int i = 0; i < 3; i++) {
        vs_out.control_points[i] = bezier(3, i);
    }
}

