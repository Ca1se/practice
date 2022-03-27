#include <cstdio>
#include <string>
#include <algorithm>
#include "shader.hpp"

namespace gcw {

ShaderSource::ShaderSource(const std::string& source):
        m_source(source), m_good(true) {}

ShaderSource::ShaderSource(const Path& path):
        m_source(), m_good(false) {
    using std::ios;

    FILE* file = std::fopen(path.str.c_str(), "rb");
    if(file == nullptr) {
        std::fclose(file);
        return;
    }

    std::fseek(file, 0, SEEK_END);
    long len = std::ftell(file);
    std::fseek(file, 0, SEEK_SET);

    std::string tmp;
    tmp.resize(len + 1);

    if(std::fread(tmp.data(), len, 1, file) == 0) {
        std::fclose(file);
        return;
    }
    tmp.back() = '\0';
    tmp.swap(m_source);

    m_good = true;
    std::fclose(file);
}

Shader::Shader():
    m_vertex_shader(), m_fragment_shader(), m_shader_program(),
    m_shader_changed(false), m_error_log{} {

}

Shader::~Shader() {
    glDeleteShader(m_vertex_shader);
    glDeleteShader(m_fragment_shader);
    glDeleteProgram(m_shader_program);
}

bool Shader::prepareShader(ShaderType shader_type, const ShaderSource& shader_source) {
    if(!shader_source.good()) {
        std::sprintf(m_error_log, "Source file error: Shader source file not found.");
        return false;
    }

    unsigned int shader_id = glCreateShader(shader_type);
    const char* const sources[] = { shader_source.get_source().c_str() };
    glShaderSource(shader_id, 1, sources, nullptr);
    glCompileShader(shader_id);

    int res;
    if(glGetShaderiv(shader_id, GL_COMPILE_STATUS, &res), !res) {
        char buf[(sizeof m_error_log) - 64];
        glGetShaderInfoLog(shader_id, sizeof buf, nullptr, buf);
        std::sprintf(m_error_log, "Shader compile error: %s", buf);
        glDeleteShader(shader_id);
        return false;
    }

    if(shader_type == kVertexShader)
        std::swap(m_vertex_shader, shader_id);
    else if(shader_type == kFragmentShader)
        std::swap(m_fragment_shader, shader_id);

    glDeleteShader(shader_id);

    m_shader_changed = true;

    return true;
}

}
