#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace gchw {

template <typename T, int Rows, int Cols>
struct Uniform {
    using ElementType = T;

    // for scalar or vec
    void operator() (int location, int count, const T* vals) const;

    // for matrix
    void operator() (int location, int count, bool transpose, const T* vals) const;
    
};

template <>
inline void Uniform<int, 1, 1>::operator() (int location, int count, const int* vals) const {
    glUniform1iv(location, count, vals);
}

template <>
inline void Uniform<int, 2, 1>::operator() (int location, int count, const int* vals) const {
    glUniform2iv(location, count, vals);
}

template <>
inline void Uniform<int, 3, 1>::operator() (int location, int count, const int* vals) const {
    glUniform3iv(location, count, vals);
}

template <>
inline void Uniform<int, 4, 1>::operator() (int location, int count, const int* vals) const {
    glUniform4iv(location, count, vals);
}

template <>
inline void Uniform<float, 1, 1>::operator() (int location, int count, const float* vals) const {
    glUniform1fv(location, count, vals);
}

template <>
inline void Uniform<float, 2, 1>::operator() (int location, int count, const float* vals) const {
    glUniform2fv(location, count, vals);
}

template <>
inline void Uniform<float, 3, 1>::operator() (int location, int count, const float* vals) const {
    glUniform3fv(location, count, vals);
}

template <>
inline void Uniform<float, 4, 1>::operator() (int location, int count, const float* vals) const {
    glUniform4fv(location, count, vals);
}

template <>
inline void Uniform<unsigned int, 1, 1>::operator() (int location, int count, const unsigned int* vals) const {
    glUniform1uiv(location, count, vals);
}

template <>
inline void Uniform<unsigned int, 2, 1>::operator() (int location, int count, const unsigned int* vals) const {
    glUniform2uiv(location, count, vals);
}

template <>
inline void Uniform<unsigned int, 3, 1>::operator() (int location, int count, const unsigned int* vals) const {
    glUniform3uiv(location, count, vals);
}

template <>
inline void Uniform<unsigned int, 4, 1>::operator() (int location, int count, const unsigned int* vals) const {
    glUniform4uiv(location, count, vals);
}

template <>
inline void Uniform<float, 2, 2>::operator() (int location, int count, bool transpose, const float* vals) const {
    glUniformMatrix2fv(location, count, transpose, vals);
}

template <>
inline void Uniform<float, 3, 2>::operator() (int location, int count, bool transpose, const float* vals) const {
    glUniformMatrix2x3fv(location, count, transpose, vals);
}

template <>
inline void Uniform<float, 4, 2>::operator() (int location, int count, bool transpose, const float* vals) const {
    glUniformMatrix2x4fv(location, count, transpose, vals);
}

template <>
inline void Uniform<float, 2, 3>::operator() (int location, int count, bool transpose, const float* vals) const {
    glUniformMatrix3x2fv(location, count, transpose, vals);
}

template <>
inline void Uniform<float, 3, 3>::operator() (int location, int count, bool transpose, const float* vals) const {
    glUniformMatrix3fv(location, count, transpose, vals);
}

template <>
inline void Uniform<float, 4, 3>::operator() (int location, int count, bool transpose, const float* vals) const {
    glUniformMatrix3x4fv(location, count, transpose, vals);
}

template <>
inline void Uniform<float, 2, 4>::operator() (int location, int count, bool transpose, const float* vals) const {
    glUniformMatrix4x2fv(location, count, transpose, vals);
}

template <>
inline void Uniform<float, 3, 4>::operator() (int location, int count, bool transpose, const float* vals) const {
    glUniformMatrix4x3fv(location, count, transpose, vals);
}

template <>
inline void Uniform<float, 4, 4>::operator() (int location, int count, bool transpose, const float* vals) const {
    glUniformMatrix4fv(location, count, transpose, vals);
}

template <>
inline void Uniform<double, 2, 2>::operator() (int location, int count, bool transpose, const double* vals) const {
    glUniformMatrix2dv(location, count, transpose, vals);
}

template <>
inline void Uniform<double, 3, 2>::operator() (int location, int count, bool transpose, const double* vals) const {
    glUniformMatrix2x3dv(location, count, transpose, vals);
}

template <>
inline void Uniform<double, 4, 2>::operator() (int location, int count, bool transpose, const double* vals) const {
    glUniformMatrix2x4dv(location, count, transpose, vals);
}

template <>
inline void Uniform<double, 2, 3>::operator() (int location, int count, bool transpose, const double* vals) const {
    glUniformMatrix3x2dv(location, count, transpose, vals);
}

template <>
inline void Uniform<double, 3, 3>::operator() (int location, int count, bool transpose, const double* vals) const {
    glUniformMatrix3dv(location, count, transpose, vals);
}

template <>
inline void Uniform<double, 4, 3>::operator() (int location, int count, bool transpose, const double* vals) const {
    glUniformMatrix3x4dv(location, count, transpose, vals);
}

template <>
inline void Uniform<double, 2, 4>::operator() (int location, int count, bool transpose, const double* vals) const {
    glUniformMatrix4x2dv(location, count, transpose, vals);
}

template <>
inline void Uniform<double, 3, 4>::operator() (int location, int count, bool transpose, const double* vals) const {
    glUniformMatrix4x3dv(location, count, transpose, vals);
}

template <>
inline void Uniform<double, 4, 4>::operator() (int location, int count, bool transpose, const double* vals) const {
    glUniformMatrix4dv(location, count, transpose, vals);
}

using Float = Uniform<float, 1, 1>;
using FVec2 = Uniform<float, 2, 1>;
using FVec3 = Uniform<float, 3, 1>;
using FVec4 = Uniform<float, 4, 1>;

using Int   = Uniform<int, 1, 1>;
using IVec2 = Uniform<int, 2, 1>;
using IVec3 = Uniform<int, 3, 1>;
using IVec4 = Uniform<int, 4, 1>;

using UInt  = Uniform<unsigned int, 1, 1>;
using UVec2 = Uniform<unsigned int, 2, 1>;
using UVec3 = Uniform<unsigned int, 3, 1>;
using UVec4 = Uniform<unsigned int, 4, 1>;

using FMat2   = Uniform<float, 2, 2>;
using FMat2x3 = Uniform<float, 3, 2>;
using FMat2x4 = Uniform<float, 4, 2>;
using FMat3x2 = Uniform<float, 2, 3>;
using FMat3   = Uniform<float, 3, 3>;
using FMat3x4 = Uniform<float, 4, 3>;
using FMat4x2 = Uniform<float, 2, 4>;
using FMat4x3 = Uniform<float, 3, 4>;
using FMat4   = Uniform<float, 4, 4>;

using DMat2   = Uniform<double, 2, 2>;
using DMat2x3 = Uniform<double, 3, 2>;
using DMat2x4 = Uniform<double, 4, 2>;
using DMat3x2 = Uniform<double, 2, 3>;
using DMat3   = Uniform<double, 3, 3>;
using DMat3x4 = Uniform<double, 4, 3>;
using DMat4x2 = Uniform<double, 2, 4>;
using DMat4x3 = Uniform<double, 3, 4>;
using DMat4   = Uniform<double, 4, 4>;

}
