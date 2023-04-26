#pragma once

#include <vector_types.h>
#include <vector_functions.h>

namespace tputil
{

class Aabb
{
public:
    Aabb();
    ~Aabb() noexcept = default;

    Aabb(const Aabb& other) = default;
    Aabb& operator=(const Aabb& other) = default;

    Aabb(const float3& min, const float3& max);

    bool isValid() const noexcept;
    operator bool() const noexcept { return isValid(); }

    void set(const float3& min, const float3& max) noexcept;
    float3 getMin() const noexcept;
    float3 getMax() const noexcept;

    void include(const float3& point) const noexcept;
    void include(const Aabb& aabb) const noexcept;

    float3 center() const noexcept;

    float3 extent() const noexcept;

private:
    float3 m_min;
    float3 m_max;
};

inline Aabb::Aabb()
    : m_min{ make_float3(1e37f, 1e37f, 1e37f) }
    , m_max{ make_float3(-1e37f, -1e37f, -1e37f) }
{
}

inline Aabb::Aabb(const float3& min, const float3& max)
    : m_min{ min }, m_max{ max }
{
}

inline bool Aabb::isValid() const noexcept
{
    return m_min.x <= m_max.x && m_min.y <= m_max.y && m_min.z <= m_max.z;
}

} // namespace tputil