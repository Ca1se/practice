#pragma once

#include <cstdio>
#include <stdexcept>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define ELEMENT_TYPE_POINTER(unitype) decltype(elementTypeAux(*((unitype*) 0)))

namespace gchw {

template <typename T, int Rows, int Cols>
struct Uniform;

template <typename T, int Rows, int Cols>
constexpr int uniformSize(const Uniform<T, Rows, Cols>&) {
    return Rows * Cols;
}

// only for type inference
template <typename T, int Rows, int Cols>
inline T* elementTypeAux(const Uniform<T, Rows, Cols>&) {
    return nullptr;
}

template <>
struct Uniform<float, 1, 1> {
    void operator() (int location, float val) const {
        glUniform1f(location, val);
    }
};

template <>
struct Uniform<float, 2, 1> {
    void operator() (int location, float val1, float val2) const {
        glUniform2f(location, val1, val2);
    }
};

template <>
struct Uniform<float, 3, 1> {
    void operator() (int location, float val1, float val2, float val3) const {
        glUniform3f(location, val1, val2, val3);
    }
};

template <>
struct Uniform<float, 4, 1> {
    void operator() (int location, float val1, float val2, float val3, float val4) const {
        glUniform4f(location, val1, val2, val3, val4);
    }
};

template <>
struct Uniform<int, 1, 1> {
    void operator() (int location, int val) const {
        glUniform1i(location, val);
    }
};

template <>
struct Uniform<int, 2, 1> {
    void operator() (int location, int val1, int val2) const {
        glUniform2i(location, val1, val2);
    }
};

template <>
struct Uniform<int, 3, 1> {
    void operator() (int location, int val1, int val2, int val3) const {
        glUniform3i(location, val1, val2, val3);
    }
};

template <>
struct Uniform<int, 4, 1> {
    void operator() (int location, int val1, int val2, int val3, int val4) const {
        glUniform4i(location, val1, val2, val3, val4);
    }
};

template <>
struct Uniform<unsigned int, 1, 1> {
    void operator() (int location, unsigned int val) const {
        glUniform1ui(location, val);
    }
};

template <>
struct Uniform<unsigned int, 2, 1> {
    void operator() (int location, unsigned int val1, unsigned int val2) const {
        glUniform2ui(location, val1, val2);
    }
};

template <>
struct Uniform<unsigned int, 3, 1> {
    void operator() (int location, unsigned int val1, unsigned int val2, unsigned int val3) const {
        glUniform3ui(location, val1, val2, val3);
    }
};

template <>
struct Uniform<unsigned int, 4, 1> {
    void operator() (int location, unsigned int val1, unsigned int val2, unsigned int val3, unsigned int val4) const {
        glUniform4ui(location, val1, val2, val3, val4);
    }
};

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

}
