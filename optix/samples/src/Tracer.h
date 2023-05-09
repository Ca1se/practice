#pragma once

#include <memory>

#include <optix_types.h>

#include "Scene.h"

struct TracerState
{
    OptixDeviceContext          context                  = nullptr;
    OptixModule                 module                   = nullptr;
    OptixPipeline               pipeline                 = nullptr;
    OptixPipelineCompileOptions pipeline_compile_options = {};
    OptixShaderBindingTable     shader_binding_table     = {};

    OptixProgramGroup raygen_pinhole_pg = nullptr;
    OptixProgramGroup hit_radiance_pg   = nullptr;
    OptixProgramGroup hit_occlusion_pg  = nullptr;
    OptixProgramGroup miss_radiance_pg  = nullptr;
    OptixProgramGroup miss_occlusion_pg = nullptr;

    OptixTraversableHandle ias_handle;

    std::vector<CudaDeviceBuffer> buffers;
};

class Tracer
{
public:
    Tracer();
    ~Tracer() noexcept;

    void loadScene(std::shared_ptr<Scene> scene);

private:
    void createOptixContext();
    void buildAccelerationStructures();
    void buildModule();
    void buildProgramGroups();
    void buildPipeline();
    void buildShaderBindingTable();

private:
    std::shared_ptr<Scene> m_scene = nullptr;

    TracerState m_state;
};