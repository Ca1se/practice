#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader {
private:
    unsigned int m_vertex_shader;
    unsigned int m_fragment_shader;
    unsigned int m_geometry_shader;

public:
    Shader();
    ~Shader();

public:
    

};
