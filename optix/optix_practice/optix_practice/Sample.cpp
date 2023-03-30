#include "Sample.h"

#include <optix_function_table_definition.h>

extern "C" char embedded_ptx_code[];

struct alignas(OPTIX_SBT_RECORD_ALIGNMENT) RaygenRecord
{
    alignas(OPTIX_SBT_RECORD_ALIGNMENT) char header[OPTIX_SBT_RECORD_HEADER_SIZE];

    void* data;
};

struct alignas(OPTIX_SBT_RECORD_ALIGNMENT) MissRecord
{
    alignas(OPTIX_SBT_RECORD_ALIGNMENT) char header[OPTIX_SBT_RECORD_HEADER_SIZE];

    void* data;
};

struct alignas(OPTIX_SBT_RECORD_ALIGNMENT) HitgroupRecord
{
    alignas(OPTIX_SBT_RECORD_ALIGNMENT) char header[OPTIX_SBT_RECORD_HEADER_SIZE];

    int object_id;
};

namespace
{

void
destoryProgramGroups(std::vector<OptixProgramGroup>& program_groups) noexcept
{
    for (auto group : program_groups)
        OPTIX_CHECK(optixProgramGroupDestroy(group));

    program_groups.clear();
}

}  // namespace

template <typename T>
static void
allocAndCopy(void** dest, const std::vector<T>& src)
{
    const int32_t byte_size = sizeof(T) * src.size();
    CUDA_CHECK(cudaMalloc(dest, byte_size));
    CUDA_CHECK(cudaMemcpy(*dest, src.data(), byte_size, cudaMemcpyHostToDevice));
}

Sample::Sample(int32_t width, int32_t height)
    : m_launch_params{ .frame_id = 0, .color_buffer = nullptr, .size = { .width = width, .height = height } }
{
    initOptix();
    createContext();
    createModule();
    createRaygenPrograms();
    createMissPrograms();
    createHitgroupPrograms();
    createPipeline();
    buildSBT();
    CUDA_CHECK(cudaMalloc(&m_launch_params_buffer, sizeof(LaunchParams)));
}

Sample::~Sample()
{
    try {
        OPTIX_CHECK(optixPipelineDestroy(m_pipeline));

        destoryProgramGroups(m_raygen_program_groups);
        destoryProgramGroups(m_miss_program_groups);
        destoryProgramGroups(m_hitgroup_program_groups);

        OPTIX_CHECK(optixModuleDestroy(m_module));
        OPTIX_CHECK(optixDeviceContextDestroy(m_optix_context));
        CUDA_CHECK(cudaStreamDestroy(m_cuda_stream));

        CUDA_CHECK(cudaFree(m_launch_params_buffer));
        CUDA_CHECK(cudaFree(m_raygen_records_buffer));
        CUDA_CHECK(cudaFree(m_miss_records_buffer));
        CUDA_CHECK(cudaFree(m_hitgroup_records_buffer));
    } catch (std::exception& e) {
        LOG_ERROR(std::format("exception caught: {}", e.what()));
    }
}

void
Sample::initOptix()
{
    cudaFree(nullptr);

    int device_num;
    cudaGetDeviceCount(&device_num);
    if (device_num == 0)
        THROW_EXCEPTION("no CUDA capable device available");

    OPTIX_CHECK(optixInit());
}

static void
context_log_cb(uint32_t level, const char* tag, const char* message, void*)
{
    LOG_INFO(std::format("[{}][{}]: {}", level, tag, message));
}

void
Sample::createContext()
{
    // Always use the first device
    static constexpr int device_id = 0;

    CUDA_CHECK(cudaSetDevice(device_id));
    CUDA_CHECK(cudaStreamCreate(&m_cuda_stream));

    auto device_prop = cudaDeviceProp{};
    CUDA_CHECK(cudaGetDeviceProperties(&device_prop, device_id));
    LOG_INFO(std::format("running on device: {}", device_prop.name));

    CUresult cu_res = cuCtxGetCurrent(&m_cuda_context);
    if (cu_res != CUDA_SUCCESS)
        THROW_EXCEPTION(std::format("error querying current context (error code: {})", static_cast<int>(cu_res)));

    OPTIX_CHECK(optixDeviceContextCreate(m_cuda_context, 0, &m_optix_context));
    OPTIX_CHECK(optixDeviceContextSetLogCallback(m_optix_context, context_log_cb, nullptr, 4));
}

void
Sample::createModule()
{
    m_module_compile_options = OptixModuleCompileOptions{ .maxRegisterCount = 50,
                                                          .optLevel         = OPTIX_COMPILE_OPTIMIZATION_DEFAULT,
                                                          .debugLevel       = OPTIX_COMPILE_DEBUG_LEVEL_NONE };

    m_pipeline_compile_options =
        OptixPipelineCompileOptions{ .usesMotionBlur                   = false,
                                     .traversableGraphFlags            = OPTIX_TRAVERSABLE_GRAPH_FLAG_ALLOW_SINGLE_GAS,
                                     .numPayloadValues                 = 2,
                                     .numAttributeValues               = 2,
                                     .exceptionFlags                   = OPTIX_EXCEPTION_FLAG_NONE,
                                     .pipelineLaunchParamsVariableName = "optix_launch_params" };

    m_pipeline_link_options    = OptixPipelineLinkOptions{ .maxTraceDepth = 2 };

    const std::string ptx_code = embedded_ptx_code;

    char log[2048];
    size_t log_size = sizeof(log);
    OPTIX_CHECK(optixModuleCreateFromPTX(m_optix_context,
                                         &m_module_compile_options,
                                         &m_pipeline_compile_options,
                                         ptx_code.c_str(),
                                         ptx_code.size(),
                                         log,
                                         &log_size,
                                         &m_module));
    if (log_size > 1)
        LOG_INFO(log);
}

void
Sample::createRaygenPrograms()
{
    m_raygen_program_groups.resize(1);

    OptixProgramGroupOptions options = {};
    OptixProgramGroupDesc desc       = { .kind   = OPTIX_PROGRAM_GROUP_KIND_RAYGEN,
                                         .raygen = { .module = m_module, .entryFunctionName = "__raygen__renderFrame" } };

    char log[2048];
    size_t log_size = sizeof(log);
    OPTIX_CHECK(
        optixProgramGroupCreate(m_optix_context, &desc, 1, &options, log, &log_size, &m_raygen_program_groups[0]));

    if (log_size > 1)
        LOG_INFO(log);
}

void
Sample::createMissPrograms()
{
    m_miss_program_groups.resize(1);

    auto options = OptixProgramGroupOptions{};
    auto desc    = OptixProgramGroupDesc{ .kind = OPTIX_PROGRAM_GROUP_KIND_MISS,
                                          .miss = { .module = m_module, .entryFunctionName = "__miss__radiance" } };

    char log[2048];
    size_t log_size = sizeof(log);
    OPTIX_CHECK(
        optixProgramGroupCreate(m_optix_context, &desc, 1, &options, log, &log_size, &m_miss_program_groups[0]));
    if (log_size > 1)
        LOG_INFO(log);
}

void
Sample::createHitgroupPrograms()
{
    m_hitgroup_program_groups.resize(1);

    auto options = OptixProgramGroupOptions{};
    auto desc    = OptixProgramGroupDesc{ .kind     = OPTIX_PROGRAM_GROUP_KIND_HITGROUP,
                                          .hitgroup = { .moduleCH            = m_module,
                                                        .entryFunctionNameCH = "__closesthit__radiance",
                                                        .moduleAH            = m_module,
                                                        .entryFunctionNameAH = "__anyhit__radiance" } };

    char log[2048];
    size_t log_size = sizeof(log);
    OPTIX_CHECK(
        optixProgramGroupCreate(m_optix_context, &desc, 1, &options, log, &log_size, &m_hitgroup_program_groups[0]));
    if (log_size > 1)
        LOG_INFO(log);
}

void
Sample::createPipeline()
{
    std::vector<OptixProgramGroup> groups;

    groups.insert(groups.end(), m_raygen_program_groups.begin(), m_raygen_program_groups.end());
    groups.insert(groups.end(), m_miss_program_groups.begin(), m_miss_program_groups.end());
    groups.insert(groups.end(), m_hitgroup_program_groups.begin(), m_hitgroup_program_groups.end());

    char log[2048];
    size_t log_size = sizeof(log);
    OPTIX_CHECK(optixPipelineCreate(m_optix_context,
                                    &m_pipeline_compile_options,
                                    &m_pipeline_link_options,
                                    groups.data(),
                                    static_cast<unsigned int>(groups.size()),
                                    log,
                                    &log_size,
                                    &m_pipeline));
    if (log_size > 1)
        LOG_INFO(log);

    OPTIX_CHECK(optixPipelineSetStackSize(m_pipeline, 2 * 1024, 2 * 1024, 2 * 1024, 1));
}

void
Sample::buildSBT()
{
    std::vector<RaygenRecord> raygen_records;
    for (const auto& rpg : m_raygen_program_groups) {
        RaygenRecord rec;
        OPTIX_CHECK(optixSbtRecordPackHeader(rpg, static_cast<void*>(&rec)));
        rec.data = nullptr;  // for now
        raygen_records.push_back(rec);
    }
    allocAndCopy(&m_raygen_records_buffer, raygen_records);
    m_shader_binding_table.raygenRecord = reinterpret_cast<CUdeviceptr>(m_raygen_records_buffer);

    std::vector<MissRecord> miss_records;
    for (const auto& mpg : m_miss_program_groups) {
        MissRecord rec;
        OPTIX_CHECK(optixSbtRecordPackHeader(mpg, static_cast<void*>(&rec)));
        rec.data = nullptr;
        miss_records.push_back(rec);
    }
    allocAndCopy(&m_miss_records_buffer, miss_records);
    m_shader_binding_table.missRecordBase          = reinterpret_cast<CUdeviceptr>(m_miss_records_buffer);
    m_shader_binding_table.missRecordStrideInBytes = sizeof(MissRecord);
    m_shader_binding_table.missRecordCount         = static_cast<int>(miss_records.size());

    // put a dummy object here
    std::vector<HitgroupRecord> hitgroup_records;
    for (int i = 0; i < 1; i++) {
        int object_type = 0;
        HitgroupRecord rec;
        OPTIX_CHECK(optixSbtRecordPackHeader(m_hitgroup_program_groups[object_type], static_cast<void*>(&rec)));
        rec.object_id = i;
        hitgroup_records.push_back(rec);
    }
    allocAndCopy(&m_hitgroup_records_buffer, hitgroup_records);
    m_shader_binding_table.hitgroupRecordBase          = reinterpret_cast<CUdeviceptr>(m_hitgroup_records_buffer);
    m_shader_binding_table.hitgroupRecordStrideInBytes = sizeof(HitgroupRecord);
    m_shader_binding_table.hitgroupRecordCount         = static_cast<int>(hitgroup_records.size());
}

void
Sample::render(tputil::CudaOutputBuffer<uchar4>& pixel_buffer)
{
    m_launch_params.color_buffer = pixel_buffer.map();
    CUDA_CHECK(cudaMemcpy(reinterpret_cast<void*>(m_launch_params_buffer),
                          &m_launch_params,
                          sizeof(LaunchParams),
                          cudaMemcpyHostToDevice));
    m_launch_params.frame_id++;

    OPTIX_CHECK(optixLaunch(m_pipeline,
                            m_cuda_stream,
                            reinterpret_cast<CUdeviceptr>(m_launch_params_buffer),
                            sizeof(LaunchParams),
                            &m_shader_binding_table,
                            m_launch_params.size.width,
                            m_launch_params.size.height,
                            1));
    pixel_buffer.unmap();
    CUDA_SYNC_CHECK();
}

void
Sample::resize(int32_t width, int32_t height) noexcept
{
    m_launch_params.size = { .width = width, .height = height };
}
