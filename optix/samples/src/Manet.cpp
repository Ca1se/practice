#include <iostream>
#include <format>
#include <stdexcept>
#include "Scene.h"

int main()
{
    Scene scene;
    try {
        Scene::loadFromGltf(scene, "sponza/sponza.gltf");
        Scene::cleanup(scene);
    } catch (std::exception& e) {
        std::cerr << std::format("Caught a exception: {}", e.what()) << std::endl;
    }
    return 0;
}