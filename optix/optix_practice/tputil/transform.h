#pragma once

#include "VectorMath.h"
#include "Matrix.h"

namespace tputil
{

TPUTIL_DECL float3 operator*(const Matrix<4, 4>& matrix, const float3& point)
{
    float4 res = matrix * make_float4(point.x, point.y, point.z, 1.0f);
    return make_float3(res.x / res.w, res.y / res.w, res.z / res.w);
}

TPUTIL_DECL Matrix<4, 4> rotateAroundXAxis(float radian)
{
    float cosr = std::cosf(radian);
    float sinr = std::sinf(radian);
    Matrix<4, 4> ret = {{
        1.0f,  0.0f, 0.0f, 0.0f,
        0.0f,  cosr, sinr, 0.0f,
        0.0f, -sinr, cosr, 0.0f,
        0.0f,  0.0f, 0.0f, 1.0f
    }};

    return ret;
}

TPUTIL_DECL Matrix<4, 4> rotateAroundYAxis(float radian)
{
    float cosr = std::cosf(radian);
    float sinr = std::sinf(radian);
    Matrix<4, 4> ret = {{
        cosr, 0.0f, -sinr, 0.0f,
        0.0f, 1.0f,  0.0f, 0.0f,
        sinr, 0.0f,  cosr, 0.0f,
        0.0f, 0.0f,  0.0f, 1.0f
    }};

    return ret;
}

TPUTIL_DECL Matrix<4, 4> rotateAroundZAxis(float radian)
{
    float cosr = std::cosf(radian);
    float sinr = std::sinf(radian);
    Matrix<4, 4> ret = {{
         cosr, sinr, 0.0f, 0.0f,
        -sinr, cosr, 0.0f, 0.0f,
         0.0f, 0.0f, 1.0f, 0.0f,
         0.0f, 0.0f, 0.0f, 1.0f
    }};

    return ret;
}

TPUTIL_DECL Matrix<4, 4> translate(const float3& offset)
{
    Matrix<4, 4> ret = {{
        1.0f, 0.0f, 0.0f, offset.x,
        0.0f, 1.0f, 0.0f, offset.y,
        0.0f, 0.0f, 1.0f, offset.z,
        0.0f, 0.0f, 0.0f,     1.0f
    }};

    return ret;
}

}