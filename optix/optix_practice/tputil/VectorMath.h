#pragma once

#include <cmath>

#include <vector_functions.h>
#include <vector_types.h>

#include "Preprocessor.h"

#define TP_PI     3.14159265358979323846f
#define TP_PIDIV2 1.57079632679489661923f

// float2

TPUTIL_INLINE TPUTIL_HOSTDEVICE float2
operator+(const float2& a, const float2& b) noexcept
{
    return make_float2(a.x + b.x, a.y + b.y);
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float2
operator+(const float2& a, float f) noexcept
{
    return make_float2(a.x + f, a.y + f);
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float2&
operator+=(float2& a, const float2& b) noexcept
{
    a.x += b.x;
    a.y += b.y;

    return a;
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float2
operator-(const float2& a) noexcept
{
    return make_float2(-a.x, -a.y);
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float2
operator-(const float2& a, const float2& b) noexcept
{
    return make_float2(a.x - b.x, a.y - b.y);
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float2
operator-(const float2& a, float f) noexcept
{
    return make_float2(a.x - f, a.y - f);
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float2&
operator-=(float2& a, const float2& b) noexcept
{
    a.x -= b.x;
    a.y -= b.y;

    return a;
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float2
operator*(const float2& a, const float2& b) noexcept
{
    return make_float2(a.x * b.x, a.y * b.y);
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float2&
operator*=(float2& a, const float2& b) noexcept
{
    a.x *= b.x;
    a.y *= b.y;

    return a;
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float2
operator*(const float2& a, float f) noexcept
{
    return make_float2(a.x * f, a.y * f);
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float2
operator*(float f, const float2& a) noexcept
{
    return a * f;
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float2&
operator*=(float2& a, float f) noexcept
{
    a.x *= f;
    a.y *= f;

    return a;
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float2
operator/(const float2& a, float f) noexcept
{
    return make_float2(a.x / f, a.y / f);
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float2&
operator/=(float2& a, float f) noexcept
{
    a.x /= f;
    a.y /= f;

    return a;
}

// float3

TPUTIL_INLINE TPUTIL_HOSTDEVICE float3
operator+(const float3& a, const float3& b) noexcept
{
    return make_float3(a.x + b.x, a.y + b.y, a.z + b.z);
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float3
operator+(const float3& a, float f) noexcept
{
    return make_float3(a.x + f, a.y + f, a.z + f);
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float3&
operator+=(float3& a, const float3& b) noexcept
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;

    return a;
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float3
operator-(const float3& a) noexcept
{
    return make_float3(-a.x, -a.y, -a.z);
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float3
operator-(const float3& a, const float3& b) noexcept
{
    return make_float3(a.x - b.x, a.y - b.y, a.z - b.z);
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float3
operator-(const float3& a, float f) noexcept
{
    return make_float3(a.x - f, a.y - f, a.z - f);
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float3&
operator-=(float3& a, const float3& b) noexcept
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;

    return a;
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float3
operator*(const float3& a, const float3& b) noexcept
{
    return make_float3(a.x * b.x, a.y * b.y, a.z * b.z);
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float3&
operator*=(float3& a, const float3& b) noexcept
{
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;

    return a;
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float3
operator*(const float3& a, float f) noexcept
{
    return make_float3(a.x * f, a.y * f, a.z * f);
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float3
operator*(float f, const float3& a) noexcept
{
    return a * f;
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float3&
operator*=(float3& a, float f) noexcept
{
    a.x *= f;
    a.y *= f;
    a.z *= f;

    return a;
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float3
operator/(const float3& a, float f) noexcept
{
    return make_float3(a.x / f, a.y / f, a.z / f);
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float3&
operator/=(float3& a, float f) noexcept
{
    a.x /= f;
    a.y /= f;
    a.z /= f;

    return a;
}

// float4

TPUTIL_INLINE TPUTIL_HOSTDEVICE float4
operator+(const float4& a, const float4& b) noexcept
{
    return make_float4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float4
operator+(const float4& a, float f) noexcept
{
    return make_float4(a.x + f, a.y + f, a.z + f, a.w + f);
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float4&
operator+=(float4& a, const float4& b) noexcept
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    a.w += b.w;

    return a;
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float4
operator-(const float4& a) noexcept
{
    return make_float4(-a.x, -a.y, -a.z, -a.w);
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float4
operator-(const float4& a, const float4& b) noexcept
{
    return make_float4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float4
operator-(const float4& a, float f) noexcept
{
    return make_float4(a.x - f, a.y - f, a.z - f, a.w - f);
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float4&
operator-=(float4& a, const float4& b) noexcept
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    a.w -= b.w;

    return a;
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float4
operator*(const float4& a, const float4& b) noexcept
{
    return make_float4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float4&
operator*=(float4& a, const float4& b) noexcept
{
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;
    a.w *= b.w;

    return a;
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float4
operator*(const float4& a, float f) noexcept
{
    return make_float4(a.x * f, a.y * f, a.z * f, a.w * f);
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float4
operator*(float f, const float4& a) noexcept
{
    return a * f;
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float4&
operator*=(float4& a, float f) noexcept
{
    a.x *= f;
    a.y *= f;
    a.z *= f;
    a.w *= f;

    return a;
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float4
operator/(const float4& a, float f) noexcept
{
    return make_float4(a.x / f, a.y / f, a.z / f, a.w / f);
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float4&
operator/=(float4& a, float f) noexcept
{
    a.x /= f;
    a.y /= f;
    a.z /= f;
    a.w /= f;

    return a;
}

namespace tputil
{

TPUTIL_INLINE TPUTIL_HOSTDEVICE float
dot(const float3& a, const float3& b) noexcept
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float
lengthSquared(const float3& a) noexcept
{
    return dot(a, a);
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float
length(const float3& a) noexcept
{
    return std::sqrtf(lengthSquared(a));
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float3
cross(const float3& a, const float3& b) noexcept
{
    return make_float3(a.y * b.z - b.y * a.z, b.x * a.z - a.x * b.z, a.x * b.y - b.x * a.y);
}

TPUTIL_INLINE TPUTIL_HOSTDEVICE float3
normalize(const float3& a) noexcept
{
    return a / length(a);
}

}  // namespace tputil