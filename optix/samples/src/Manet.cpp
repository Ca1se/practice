#include <iostream>
#include <format>
#include <stdexcept>
#include "Scene.h"

int main()
{
    Scene scene;
    try {
        Scene::loadFromGltf(scene, "sponza/sponza.gltf");
        std::cerr << std::format("indices:   {}\n"
                                 "positions: {}\n"
                                 "normals:   {}\n"
                                 "texcoords: {}\n"
                                 "colors:    {}\n"
                                 "materials: {}\n",
                                 scene.meshes[0]->indices.size(),
                                 scene.meshes[0]->positions.size(),
                                 scene.meshes[0]->normals.size(),
                                 scene.meshes[0]->texcoords.size(),
                                 scene.meshes[0]->colors.size(),
                                 scene.meshes[0]->material_indices.size()) << std::endl;
        Scene::cleanup(scene);
    } catch (std::exception& e) {
        std::cerr << std::format("Caught a exception: {}", e.what()) << std::endl;
    }
    return 0;
}