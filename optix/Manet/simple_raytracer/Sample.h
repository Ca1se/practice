#pragma once

#include "cuda/LaunchParams.h"

struct State;
class Camera;
struct Mesh;

class Sample
{
public:
    Sample(const tputil::Model& model);
    Sample(tputil::Model&& model);
    ~Sample() noexcept;

    void render(State& launch_params);

    void updateCamera(const Camera& camera) noexcept;

protected:
    void initOptix();

    void createContext();

    void createModule();

    void createRaygenPrograms();

    void createMissPrograms();

    void createHitgroupPrograms();

    void createPipeline();

    void buildSBT();

    OptixTraversableHandle buildAccel();

protected:
    // CUDA device context and stream that optix pipeline will run
    // on, as well as device properties for this device
    CUcontext m_cuda_context = nullptr;
    CUstream m_cuda_stream   = nullptr;

    // the optix context that our pipeline will run in.
    OptixDeviceContext m_optix_context = nullptr;

    // the pipeline we're building
    OptixPipeline m_pipeline = nullptr;
    OptixPipelineCompileOptions m_pipeline_compile_options = {};
    OptixPipelineLinkOptions m_pipeline_link_options       = {};

    // the module that contains out device programs
    OptixModule m_module = nullptr;
    OptixModuleCompileOptions m_module_compile_options = {};

    // vector of all our program(group)s, and the SBT built around them
    std::vector<OptixProgramGroup> m_raygen_program_groups   = {};
    tputil::CudaDeviceBuffer m_raygen_records_buffer         = {};
    std::vector<OptixProgramGroup> m_miss_program_groups     = {};
    tputil::CudaDeviceBuffer m_miss_records_buffer           = {};
    std::vector<OptixProgramGroup> m_hitgroup_program_groups = {};
    tputil::CudaDeviceBuffer m_hitgroup_records_buffer       = {};

    OptixShaderBindingTable m_shader_binding_table = {};

    tputil::CudaDeviceBuffer m_gas_buffer = {};

    LaunchParams m_launch_params;
    tputil::CudaDeviceBuffer m_launch_params_buffer{ sizeof(LaunchParams) };

    tputil::Model m_model = {};
    std::vector<tputil::CudaDeviceBuffer> m_vertex_buffers         = {};
    std::vector<tputil::CudaDeviceBuffer> m_normal_buffers         = {};
    std::vector<tputil::CudaDeviceBuffer> m_texcoord_buffers       = {};
    std::vector<tputil::CudaDeviceBuffer> m_vertex_index_buffers   = {};
    std::vector<tputil::CudaDeviceBuffer> m_normal_index_buffers   = {};
    std::vector<tputil::CudaDeviceBuffer> m_texcoord_index_buffers = {};
};