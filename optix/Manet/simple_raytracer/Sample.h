#pragma once

struct State;

class Sample
{
public:
    Sample(const tputil::Model& model);
    Sample(tputil::Model&& model);
    ~Sample() noexcept;

    void render(State& state);

protected:
    void initOptix();

    void createContext();

    void createTextures();

    void createModule();

    void createRaygenPrograms();

    void createMissPrograms();

    void createHitgroupPrograms();

    void createPipeline();

    void buildSBT();

    void buildAccel();

protected:
    int32_t m_cuda_device_id = 0;       // use first device
    CUcontext m_cuda_context = nullptr; // use current cuda context
    CUstream m_cuda_stream   = nullptr;

    // the optix context that our pipeline will run in.
    OptixDeviceContext m_optix_context = nullptr;

    // the pipeline we're building
    OptixPipeline m_pipeline = nullptr;
    OptixPipelineCompileOptions m_pipeline_compile_options = {};
    OptixPipelineLinkOptions m_pipeline_link_options       = {};

    // the module that contains out device programs
    OptixModule m_radiance_module = nullptr;
    OptixModule m_shadow_module   = nullptr;
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
    OptixTraversableHandle m_gas_handle   = 0;

    tputil::Model m_model = {};
    std::vector<tputil::CudaDeviceBuffer> m_vertex_buffers         = {};
    std::vector<tputil::CudaDeviceBuffer> m_normal_buffers         = {};
    std::vector<tputil::CudaDeviceBuffer> m_texcoord_buffers       = {};
    std::vector<tputil::CudaDeviceBuffer> m_vertex_index_buffers   = {};
    std::vector<tputil::CudaDeviceBuffer> m_normal_index_buffers   = {};
    std::vector<tputil::CudaDeviceBuffer> m_texcoord_index_buffers = {};

    std::vector<cudaArray_t> m_texture_arrays          = {};
    std::vector<cudaTextureObject_t> m_texture_objects = {};
};