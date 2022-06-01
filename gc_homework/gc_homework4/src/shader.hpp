#pragma once

#include <cstdio>
#include <stdexcept>
#include <string>
#include <map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "uniform.hpp"


namespace gchw {

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

const char* const kDefaultGeometryShaderSource =
    "#version 330 core\n"
    "layout (points) in;\n"
    "layout (points, max_vertices = 1) out;\n"
    "void main() {\n"
    "   gl_Position = gl_in[0].gl_Position;\n"
    "   EmitVertex();\n"
    "   EndPrimitive();\n"
    "}";


struct Path {
    std::string str;
    explicit Path(const std::string& path): str(std::string{ SHADER_DIR_PATH } + path) {}
};

class ShaderSource {
private:
    std::string m_source;
    bool m_good;

public:
    ShaderSource(const std::string& source);
    ShaderSource(const char* source);
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
        kGeometryShader = GL_GEOMETRY_SHADER
    };

private:
    unsigned int m_vertex_shader;
    unsigned int m_fragment_shader;
    unsigned int m_geometry_shader;
    unsigned int m_shader_program;

    bool m_have_geometry;
    bool m_shader_changed;

    char m_error_log[512];

public:
    Shader(bool geometry = false);
    ~Shader();

public:
    bool prepareShader(ShaderType shader_type, const ShaderSource& shader_source);
    bool use();

    // UniType must be one of GLSL Uniform scalar or vec types;
    template<typename UniType>
    void setUniform(const std::string& name, int count, const typename UniType::ElementType* vals) const {
        int location = glGetUniformLocation(m_shader_program, name.c_str());
        if(location == -1) {
            std::fprintf(stderr, "%s: gcw::Shader::%s(): Uniform set failed, make sure that the shader is used and that the uniform name is currect.\n", __FILE__, __func__);
            return;
        }

        UniType()(location, count, vals);
    }

    // UniType must be one of GLSL Uniform mat types;
    template<typename UniType>
    void setUniformMatrix(const std::string& name, int count, bool transpose, const typename UniType::ElementType* vals) const {
        int location = glGetUniformLocation(m_shader_program, name.c_str());
        if(location == -1) {
            std::fprintf(stderr, "%s: gcw::Shader::%s(): Uniform set failed, make sure that the shader is used and that the uniform name is currect.\n", __FILE__, __func__);
            return;
        }

        UniType()(location, count, transpose, vals);
    }
        
    constexpr const char* get_error_log() const noexcept { return m_error_log; }
    constexpr unsigned int get_shader_program() const noexcept { return m_shader_program; }
};

}
