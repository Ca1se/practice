#pragma once

struct Mesh
{
    std::vector<float3> vertices;
    std::vector<uint3> indices;

    static void addCube(Mesh& mesh, const float3& front_lower_left, const float3& size);
    static void addUnitCube(Mesh& mesh, const float3& front_lower_left);
};