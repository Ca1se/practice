#include <iostream>
#include <format>
#include <memory>
#include <stdexcept>

#include "Scene.h"
#include "Tracer.h"

int main()
{
    try {
        auto scene = std::make_shared<Scene>();
        Scene::loadFromGltf(*scene, "sponza/sponza.gltf");
        Tracer tracer;
        tracer.loadScene(scene);
    } catch (std::exception& e) {
        std::cerr << std::format("Caught a exception: {}", e.what()) << std::endl;
    }
    return 0;
}