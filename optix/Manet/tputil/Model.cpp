#include "Model.h"

#include <unordered_map>
#include <set>
#include <iostream>
#include <format>
#include <vector_functions.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include "TpUtil.h"
#include "Exception.h"

namespace tputil
{

namespace
{

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

    const float3* vec3f_view = reinterpret_cast<const float3*>(attributes.vertices.data());
    mesh.vertices.push_back(vec3f_view[vertex_index_attr]);
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

    const float3* vec3f_view = reinterpret_cast<const float3*>(attributes.normals.data());
    mesh.normals.push_back(vec3f_view[normal_index_attr]);
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

    const float2* vec2f_view = reinterpret_cast<const float2*>(attributes.texcoords.data());
    mesh.texcoords.push_back(vec2f_view[texcoord_index_attr]);
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

int32_t loadTexture(Model& model,
                    std::map<std::string, uint32_t>& known_texture,
                    const std::string& texture_name,
                    const std::string& model_dir_path)
{
    if (texture_name.size() == 0)
        return -1;
    
    if (auto itr = known_texture.find(texture_name); itr != known_texture.end())
        return itr->second;
    
    std::string texture_path = model_dir_path + '/' + texture_name;

    int texture_index = -1;
    int width, height, comp;
    uint8_t* image = stbi_load(texture_path.c_str(), &width, &height, &comp, STBI_rgb_alpha);

    if (image != nullptr) {
        std::shared_ptr<Texture> texture{ new Texture{
            .width  = width,
            .height = height,
            .data   = std::vector<uint32_t>(width * height)
        } };

        const uint32_t* image_u32 = reinterpret_cast<const uint32_t*>(image);
        auto& data = texture->data;
        for (int y = 0; y < height; y++) {
            int y1 = height - y - 1;
            int image_line_begin = y * width;
            int data_line_begin = y1 * width;
            for (int x = 0; x < width; x++)
                data[data_line_begin + x] = image_u32[image_line_begin + x];
        }

        texture_index = static_cast<int>(model.textures.size());
        model.textures.push_back(texture);
        free(image);
    } else {
        std::cerr << EXCEPTION_MSG(std::format("failed to load texture {}", texture_name)) << std::endl;
    }

    known_texture[texture_name] = texture_index;
    return texture_index;
}

} // namespace


void loadObjModel(Model& model, const std::string& filename)
{
    std::string obj_file_path = getModelPath(filename);
    std::string model_dir_path  = obj_file_path.substr(0, obj_file_path.rfind('/') + 1);

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
                                model_dir_path.c_str());
    
    if (!res)
        throw std::runtime_error{ EXCEPTION_MSG(std::format("failed to load OBJ model {}", filename)) };
    
    if (materials.empty())
        throw std::runtime_error{ EXCEPTION_MSG(std::format("failed to parse materials when loading model {}", filename)) };
    
    if (!warn.empty())
        std::cerr << EXCEPTION_MSG(std::format("get a warning when loading model {}: {}", filename, warn)) << std::endl;
    
    std::map<std::string, uint32_t> known_textures;
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
            mesh->texture_index = loadTexture(model, known_textures, materials[material_id].diffuse_texname, model_dir_path);

            if(!mesh->vertices.empty())
                model.meshes.push_back(mesh);
        }
    }
}

} // namespace tputil

