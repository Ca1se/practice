#pragma once

#include "CudaOutputBuffer.h"
#include "LaunchParams.h"

class Sample
{
public:
    Sample(int32_t width, int32_t height);
    ~Sample() noexcept;

    void render(tputil::CudaOutputBuffer<uchar4>& pixel_buffer);
    void resize(int32_t width, int32_t height) noexcept;

protected:
    void initOptix();

    void createContext();

    void createModule();

    void createRaygenPrograms();

    void createMissPrograms();

    void createHitgroupPrograms();

    void createPipeline();

    void buildSBT();

protected:
    // CUDA device context and stream that optix pipeline will run
    // on, as well as device properties for this device
    CUcontext m_cuda_context = nullptr;
    CUstream m_cuda_stream   = nullptr;

    // the optix context that our pipeline will run in.
    OptixDeviceContext m_optix_context = nullptr;

    // the pipeline we're building
    OptixPipeline m_pipeline                               = nullptr;
    OptixPipelineCompileOptions m_pipeline_compile_options = {};
    OptixPipelineLinkOptions m_pipeline_link_options       = {};

    // the module that contains out device programs
    OptixModule m_module                               = nullptr;
    OptixModuleCompileOptions m_module_compile_options = {};

    // vector of all our program(group)s, and the SBT built around them
    std::vector<OptixProgramGroup> m_raygen_program_groups   = {};
    void* m_raygen_records_buffer                            = nullptr;
    std::vector<OptixProgramGroup> m_miss_program_groups     = {};
    void* m_miss_records_buffer                              = nullptr;
    std::vector<OptixProgramGroup> m_hitgroup_program_groups = {};
    void* m_hitgroup_records_buffer                          = nullptr;
    OptixShaderBindingTable m_shader_binding_table           = {};

    // our launch parameters, on the host, and the buffer to store
    // them on the device
    LaunchParams m_launch_params;
    void* m_launch_params_buffer = nullptr;
};