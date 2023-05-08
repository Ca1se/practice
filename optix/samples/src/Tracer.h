#pragma once

#include <optix_types.h>

struct TracerState
{

};

class Tracer
{
public:
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
};