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

}

TPUTIL_DECL Matrix<4, 4> rotateAroundXAxis(float radian)
{

}

TPUTIL_DECL Matrix<4, 4> rotateAroundXAxis(float radian)
{

}

}