#include "Model.h"

#include <unordered_map>
#include <set>
#include <iostream>
#include <format>
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include <vector_functions.h>

#include "TpUtil.h"
#include "Exception.h"

namespace tputil
{

namespace
{

struct Vec3f
{
    float x;
    float y;
    float z;
};

struct Vec2f
{
    float u;
    float v;
};

void addPosition(Mesh& mesh,
                 std::map<int32_t, uint32_t>& known_vertices,
                 const tinyobj::attrib_t& attributes,
                 int32_t vertex_index_attr)
{
    if (auto itr = known_vertices.find(vertex_index_attr); itr != known_vertices.end()) {
        mesh.vertex_indices.push_back(mesh.vertex_indices[itr->second]);
        return;
    }

    known_vertices[vertex_index_attr] = static_cast<uint32_t>(mesh.vertex_indices.size());
    mesh.vertex_indices.push_back(static_cast<int32_t>(mesh.vertices.size()));

    const Vec3f* vec3f_view = reinterpret_cast<const Vec3f*>(attributes.vertices.data());
    const Vec3f& vertex = vec3f_view[vertex_index_attr];

    mesh.vertices.push_back(make_float3(vertex.x, vertex.y, vertex.z));
}

void addNormal(Mesh& mesh,
               std::map<int32_t, uint32_t>& known_normals,
               const tinyobj::attrib_t& attributes,
               int32_t normal_index_attr)
{
    if (normal_index_attr == -1) {
        mesh.normal_indices.push_back(-1);
        return;
    }

    if (auto itr = known_normals.find(normal_index_attr); itr != known_normals.end()) {
        mesh.normal_indices.push_back(mesh.normal_indices[itr->second]);
        return;
    }

    known_normals[normal_index_attr] = static_cast<uint32_t>(mesh.normal_indices.size());
    mesh.normal_indices.push_back(static_cast<int32_t>(mesh.normals.size()));

    const Vec3f* vec3f_view = reinterpret_cast<const Vec3f*>(attributes.normals.data());
    const Vec3f& normal = vec3f_view[normal_index_attr];

    mesh.normals.push_back(make_float3(normal.x, normal.y, normal.z));
}

void addTexcoord(Mesh& mesh,
                 std::map<int32_t, uint32_t>& known_texcoords,
                 const tinyobj::attrib_t& attributes,
                 int32_t texcoord_index_attr)
{
    if (texcoord_index_attr == -1) {
        mesh.texcoord_indices.push_back(-1);
        return;
    }

    if(auto itr = known_texcoords.find(texcoord_index_attr); itr != known_texcoords.end()) {
        mesh.texcoord_indices.push_back(mesh.texcoord_indices[itr->second]);
        return;
    }

    known_texcoords[texcoord_index_attr] = static_cast<uint32_t>(mesh.texcoord_indices.size());
    mesh.texcoord_indices.push_back(static_cast<int32_t>(mesh.texcoords.size()));

    const Vec2f* vec2f_view = reinterpret_cast<const Vec2f*>(attributes.texcoords.data());
    const Vec2f& texcoord = vec2f_view[texcoord_index_attr];

    mesh.texcoords.push_back(make_float2(texcoord.u, texcoord.v));
}

void addVertex(Mesh& mesh,
               std::map<int32_t, uint32_t>& known_vertices,
               std::map<int32_t, uint32_t>& known_normals,
               std::map<int32_t, uint32_t>& known_texcoords,
               const tinyobj::attrib_t& attributes,
               const tinyobj::index_t& index)
{
    addPosition(mesh, known_vertices, attributes, index.vertex_index);
    addNormal(mesh, known_normals, attributes, index.normal_index);
    addTexcoord(mesh, known_texcoords, attributes, index.texcoord_index);
}

} // namespace

void loadObjModel(Model& model, const std::string& filename)
{
    std::string obj_file_path = getModelPath(filename);
    std::string mtl_dir_path = obj_file_path.substr(0, obj_file_path.rfind('/') + 1);

    tinyobj::attrib_t attributes;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn;
    std::string err;
    
    bool res = tinyobj::LoadObj(&attributes,
                                &shapes,
                                &materials,
                                &warn,
                                &err,
                                obj_file_path.c_str(),
                                mtl_dir_path.c_str());
    
    if (!res)
        throw std::runtime_error{ EXCEPTION_MSG(std::format("failed to load OBJ model {}", filename)) };
    
    if (materials.empty())
        throw std::runtime_error{ EXCEPTION_MSG(std::format("failed to parse materials when loading model {}", filename)) };
    
    if (!warn.empty())
        std::cerr << std::format("Get a warning when loading model {}: {}\n", filename, warn);
    
    for (size_t i = 0; i < shapes.size(); i++) {
        const tinyobj::shape_t& shape = shapes[i];
        const std::vector<tinyobj::index_t>& indices = shape.mesh.indices;
        const std::vector<int32_t>& material_ids     = shape.mesh.material_ids;

        std::unordered_map<int32_t, std::vector<uint32_t>> face_sorted_by_material_id;
        for (uint32_t face_id = 0; face_id < material_ids.size(); face_id++) {
            int32_t material_id = material_ids[face_id];
            face_sorted_by_material_id[material_id].push_back(face_id);
        }
        
        for (const auto& itr: face_sorted_by_material_id) {
            int32_t material_id = itr.first;
            const auto& face_ids = itr.second;
            std::shared_ptr<Mesh> mesh{ new Mesh{} };

            std::map<int32_t, uint32_t> known_vertices;
            std::map<int32_t, uint32_t> known_normals;
            std::map<int32_t, uint32_t> known_texcoords;

            for (uint32_t face_id: face_ids) {
                const auto& idx0 = indices[3 * face_id + 0];
                const auto& idx1 = indices[3 * face_id + 1];
                const auto& idx2 = indices[3 * face_id + 2];

                addVertex(*mesh, known_vertices, known_normals, known_texcoords, attributes, idx0);
                addVertex(*mesh, known_vertices, known_normals, known_texcoords, attributes, idx1);
                addVertex(*mesh, known_vertices, known_normals, known_texcoords, attributes, idx2);

                
                
            }
            mesh->diffuse_color = make_float3(materials[material_id].diffuse[0],
                                              materials[material_id].diffuse[1],
                                              materials[material_id].diffuse[2]);

            if(!mesh->vertices.empty())
                model.meshes.push_back(mesh);
        }
    }
}

} // namespace tputil

