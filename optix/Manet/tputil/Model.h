#pragma once

#include <vector>
#include <memory>
#include <string>

#include <vector_types.h>

namespace tputil
{

// Triangle mesh
struct Mesh
{
    std::vector<float3> vertices;
    std::vector<float3> normals;
    std::vector<float2> texcoords;

    std::vector<int32_t> vertex_indices;
    std::vector<int32_t> normal_indices;
    std::vector<int32_t> texcoord_indices;

    float3 diffuse_color;
    int32_t texture_index;
};

struct Texture
{
    int32_t width;
    int32_t height;
    std::vector<uint32_t> data;
};

struct Model
{
    std::vector<std::shared_ptr<Mesh>> meshes;
    std::vector<std::shared_ptr<Texture>> textures;
};

void loadObjModel(Model& model, const std::string& filename);

} // namespace tputil