#pragma once

#include <cstdio>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace gcw {

const char* const kDefaultVertexShaderSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main() {\n"
    "   gl_Position = vec4(aPos.xyz, 1.0f);\n"
    "}";

const char* const kDefaultFragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}";

class ShaderSource {
public:
    struct Path {
        std::string str;
        explicit Path(const std::string& path): str(path) {}
        operator std::string() const { return str; }
    };

private:
    std::string m_source;
    bool m_good;

public:
    ShaderSource(const std::string& source);
    ShaderSource(const Path& path);

public:
    const std::string& get_source() const noexcept { return m_source; }
    bool good() const noexcept { return m_good; }
};


class Shader {
public:
    enum ShaderType {
        kVertexShader = GL_VERTEX_SHADER,
        kFragmentShader = GL_FRAGMENT_SHADER,
    };

private:
    unsigned int m_vertex_shader;
    unsigned int m_fragment_shader;
    unsigned int m_shader_program;
    bool m_shader_changed;

    char m_error_log[512];

public:
    Shader();
    ~Shader();

public:
    bool prepareShader(ShaderType shader_type, const ShaderSource& shader_source);
        
    constexpr const char* get_error_log() const noexcept { return m_error_log; }
};

}
