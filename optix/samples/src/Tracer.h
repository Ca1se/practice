#pragma once

#include <memory>

#include <optix_types.h>

#include "Scene.h"

struct TracerState
{

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
    OptixDeviceContext          m_context                  = nullptr;
    OptixModule                 m_module                   = nullptr;
    OptixPipeline               m_pipeline                 = nullptr;
    OptixPipelineCompileOptions m_pipeline_compile_options = {};
    OptixShaderBindingTable     m_shader_binding_table     = {};

    OptixProgramGroup m_raygen_pinhole_pg = nullptr;
    OptixProgramGroup m_hit_radiance_pg   = nullptr;
    OptixProgramGroup m_hit_occlusion_pg  = nullptr;
    OptixProgramGroup m_miss_radiance_pg  = nullptr;
    OptixProgramGroup m_miss_occlusion_pg = nullptr;

    std::shared_ptr<Scene> m_scene = nullptr;

    TracerState m_state;
};