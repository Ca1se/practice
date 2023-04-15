#include "Geometry.h"

void Mesh::addCube(Mesh& mesh, const float3& front_lower_left, const float3& size)
{
    auto &[vertices, indices] = mesh;
    uint32_t offset = static_cast<uint32_t>(vertices.size());
    
    vertices.push_back(front_lower_left + make_float3(   0.0f,    0.0f,   0.0f));
    vertices.push_back(front_lower_left + make_float3(   0.0f, -size.y,   0.0f));
    vertices.push_back(front_lower_left + make_float3(-size.x, -size.y,   0.0f));
    vertices.push_back(front_lower_left + make_float3(-size.x,    0.0f,   0.0f));
    vertices.push_back(front_lower_left + make_float3(   0.0f,    0.0f, size.z));
    vertices.push_back(front_lower_left + make_float3(   0.0f, -size.y, size.z));
    vertices.push_back(front_lower_left + make_float3(-size.x, -size.y, size.z));
    vertices.push_back(front_lower_left + make_float3(-size.x,    0.0f, size.z));

    static constexpr uint3 original_indices[12] = {
        { 0, 2, 1 },    { 2, 0, 3 },
        { 7, 5, 6 },    { 5, 7, 4 },
        { 0, 5, 4 },    { 5, 0, 1 },
        { 7, 2, 3 },    { 2, 7, 6 },
        { 7, 0, 4 },    { 0, 7, 3 },
        { 5, 2, 6 },    { 2, 5, 1 }
    };

    for(const auto& index: original_indices)
        indices.push_back(index + make_uint3(offset, offset, offset));
}

void Mesh::addUnitCube(Mesh& mesh, const float3& front_lower_left)
{
    Mesh::addCube(mesh, front_lower_left, make_float3(1.0f, 1.0f, 1.0f));
}