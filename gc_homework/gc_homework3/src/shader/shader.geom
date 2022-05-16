#version 330 core
layout (points) in;
layout (line_strip, max_vertices = 101) out;

uniform mat4 u_v;
uniform mat4 u_p;

in VS_OUT {
    vec3 control_points[3];
} gs_in[];

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

float bernstein(int n, int i, float t) {
    float tmp = 1 - t;
    return cnk(n, i) * pow(t, i) * pow(tmp, n - i);
}

vec3 bezier(int n, float t) {
    vec3 ret = vec3(0.0);
    for(int i = 0; i < n + 1; i++) {
        ret += bernstein(n, i, t) * gs_in[0].control_points[i];
    }
    return ret;
}

void main() {    
    mat4 mvp = u_p * u_v;
    float t = 0;
    for(int i = 0; i <= 100; i++, t += 0.01) {
        gl_Position = mvp * vec4(bezier(2, t), 1.0);
        EmitVertex();
    }
    EndPrimitive();
}

