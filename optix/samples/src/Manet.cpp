#include <iostream>
#include <format>
#include <stdexcept>
#include "Scene.h"

int main()
{
    Scene scene;
    try {
        loadGltfScene(scene, "sponza/sponza.gltf");
        std::cerr << "hello\n";
    } catch (std::exception& e) {
        std::cerr << std::format("Caught a exception: {}", e.what()) << std::endl;
    }
    return 0;
}