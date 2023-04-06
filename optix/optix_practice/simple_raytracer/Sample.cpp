#include "Sample.h"

#include "RecordData.h"
#include "SimpleRaytracer.h"

#include <optix_function_table_definition.h>

extern "C" char embedded_ptx_code[];

template <typename T>
struct Record
{
    alignas(OPTIX_SBT_RECORD_ALIGNMENT) char header[OPTIX_SBT_RECORD_HEADER_SIZE];
    T data;
};

using RaygenRecord   = Record<RaygenData>;
using MissRecord     = Record<MissData>;
using HitgroupRecord = Record<HitgroupData>;

namespace
{

__device__ void
resizeAndUpload(tputil::CudaDeviceBuffer& dest, const void* src, size_t byte_size)
{
    dest.resize(byte_size);
    dest.upload(src, byte_size);
}

void
destoryProgramGroups(std::vector<OptixProgramGroup>& program_groups) noexcept
{
    for (auto group : program_groups)
        OPTIX_CHECK(optixProgramGroupDestroy(group));

    program_groups.clear();
}

void
context_log_cb(uint32_t level, const char* tag, const char* message, void*)
{
    LOG_INFO(std::format("[{}][{}]: {}", level, tag, message));
}

}  // namespace

Sample::Sample()
{
    initOptix();
    createContext();
    createModule();
    createRaygenPrograms();
    createMissPrograms();
    createHitgroupPrograms();
    createPipeline();
    buildSBT();
    m_launch_params = LaunchParams{
        .frame  = { .id = 0, .color_buffer = nullptr },
        .handle = buildAccel(),
    };
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
    } catch (std::exception& e) {
        LOG_ERROR(std::format("Sample destructor caught exception: {}", e.what()));
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
                                     .numPayloadValues                 = 3,
                                     .numAttributeValues               = 3,
                                     .exceptionFlags                   = OPTIX_EXCEPTION_FLAG_NONE,
                                     .pipelineLaunchParamsVariableName = "g_optix_launch_params",
                                     /*.usesPrimitiveTypeFlags = OPTIX_PRIMITIVE_TYPE_FLAGS_TRIANGLE */ };
    m_pipeline_compile_options.usesPrimitiveTypeFlags = OPTIX_PRIMITIVE_TYPE_FLAGS_TRIANGLE;

    m_pipeline_link_options = OptixPipelineLinkOptions{ .maxTraceDepth = 1 };

    const std::string ptx_code = embedded_ptx_code;

    OPTIX_CHECK(optixModuleCreateFromPTX(m_optix_context,
                                         &m_module_compile_options,
                                         &m_pipeline_compile_options,
                                         ptx_code.data(),
                                         ptx_code.size(),
                                         nullptr,
                                         nullptr,
                                         &m_module));
}

void
Sample::createRaygenPrograms()
{
    m_raygen_program_groups.resize(1);

    auto options = OptixProgramGroupOptions{};
    auto desc =
        OptixProgramGroupDesc{ .kind   = OPTIX_PROGRAM_GROUP_KIND_RAYGEN,
                               .raygen = OptixProgramGroupSingleModule{ .module            = m_module,
                                                                        .entryFunctionName = "__raygen__pinhole" } };

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
    auto desc =
        OptixProgramGroupDesc{ .kind = OPTIX_PROGRAM_GROUP_KIND_MISS,
                               .miss = OptixProgramGroupSingleModule{ .module            = m_module,
                                                                      .entryFunctionName = "__miss__radiance" } };

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
    auto desc =
        OptixProgramGroupDesc{ .kind     = OPTIX_PROGRAM_GROUP_KIND_HITGROUP,
                               .hitgroup = OptixProgramGroupHitgroup{ .moduleCH            = m_module,
                                                                      .entryFunctionNameCH = "__closesthit__radiance",
                                                                      /*
                                                                      .moduleAH            = m_module,
                                                                      .entryFunctionNameAH = "__anyhit__radiance"*/ } };

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
                                    static_cast<uint32_t>(groups.size()),
                                    nullptr,
                                    nullptr,
                                    &m_pipeline));

    OPTIX_CHECK(optixPipelineSetStackSize(m_pipeline, 2 * 1024, 2 * 1024, 2 * 1024, 1));
}

void
Sample::buildSBT()
{
    std::vector<RaygenRecord> raygen_records;
    for (const auto& rpg : m_raygen_program_groups) {
        RaygenRecord rec;
        OPTIX_CHECK(optixSbtRecordPackHeader(rpg, static_cast<void*>(&rec)));
        raygen_records.push_back(rec);
    }
    resizeAndUpload(m_raygen_records_buffer, raygen_records.data(), raygen_records.size() * sizeof(RaygenRecord));
    m_shader_binding_table.raygenRecord = m_raygen_records_buffer.data();

    std::vector<MissRecord> miss_records;
    for (const auto& mpg : m_miss_program_groups) {
        MissRecord rec;
        OPTIX_CHECK(optixSbtRecordPackHeader(mpg, static_cast<void*>(&rec)));
        rec.data.background_color = make_uchar3(0.5f * 0xff, 0.7f * 0xff, 1.0f * 0xff);
        miss_records.push_back(rec);
    }
    resizeAndUpload(m_miss_records_buffer, miss_records.data(), miss_records.size() * sizeof(MissRecord));
    m_shader_binding_table.missRecordBase          = m_miss_records_buffer.data();
    m_shader_binding_table.missRecordStrideInBytes = sizeof(MissRecord);
    m_shader_binding_table.missRecordCount         = static_cast<int>(miss_records.size());

    // put a dummy object here
    std::vector<HitgroupRecord> hitgroup_records;
    for (int i = 0; i < 1; i++) {
        int object_type = 0;
        HitgroupRecord rec;
        OPTIX_CHECK(optixSbtRecordPackHeader(m_hitgroup_program_groups[object_type], static_cast<void*>(&rec)));
        rec.data.color = make_uchar3(0xff, 0xff, 0x00);
        hitgroup_records.push_back(rec);
    }
    resizeAndUpload(m_hitgroup_records_buffer,
                    hitgroup_records.data(),
                    hitgroup_records.size() * sizeof(HitgroupRecord));
    m_shader_binding_table.hitgroupRecordBase          = m_hitgroup_records_buffer.data();
    m_shader_binding_table.hitgroupRecordStrideInBytes = sizeof(HitgroupRecord);
    m_shader_binding_table.hitgroupRecordCount         = static_cast<int>(hitgroup_records.size());
}

void
Sample::render(State& state)
{
    m_launch_params.frame.color_buffer = state.pixel_buffer.map();
    m_launch_params_buffer.upload(static_cast<void*>(&m_launch_params), sizeof(LaunchParams));

    OPTIX_CHECK(optixLaunch(m_pipeline,
                            m_cuda_stream,
                            m_launch_params_buffer.data(),
                            sizeof(LaunchParams),
                            &m_shader_binding_table,
                            state.output_size.width,
                            state.output_size.height,
                            1));

    state.pixel_buffer.unmap();

    CUDA_SYNC_CHECK();

    m_launch_params.frame.id++;
}

void
Sample::updateCamera(const Camera& camera) noexcept
{
    auto& [pos, u, v, w] = m_launch_params.camera;

    pos = camera.getPosition();
    camera.getUVW(u, v, w);
}

OptixTraversableHandle
Sample::buildAccel()
{
    static constexpr std::array<float3, 3> vertices = {
        {
            { -1.0f, -1.0f, 0.0f },
            { 1.0f, -1.0f, 0.0f },
            { 0.0f, 1.0f, 0.0f },
        },
    };
    static constexpr uint32_t triangle_input_flags = OPTIX_GEOMETRY_FLAG_NONE;

    tputil::CudaDeviceBuffer vertex_buffer = { static_cast<const void*>(vertices.data()), sizeof(vertices) };

    OptixAccelBuildOptions accel_options = {
        .buildFlags = OPTIX_BUILD_FLAG_ALLOW_COMPACTION,
        .operation  = OPTIX_BUILD_OPERATION_BUILD,
    };
    CUdeviceptr buffer_pointer     = vertex_buffer.data();
    OptixBuildInput triangle_input = {
        .type = OPTIX_BUILD_INPUT_TYPE_TRIANGLES,
        .triangleArray =
            OptixBuildInputTriangleArray{
                .vertexBuffers       = &buffer_pointer,
                .numVertices         = vertices.size(),
                .vertexFormat        = OPTIX_VERTEX_FORMAT_FLOAT3,
                .vertexStrideInBytes = sizeof(float3),
                .flags               = &triangle_input_flags,
                .numSbtRecords       = 1,
            },
    };

    OptixAccelBufferSizes gas_buffer_size;

    OPTIX_CHECK(optixAccelComputeMemoryUsage(m_optix_context, &accel_options, &triangle_input, 1, &gas_buffer_size));

    tputil::CudaDeviceBuffer temp_buffer           = { gas_buffer_size.tempSizeInBytes };
    tputil::CudaDeviceBuffer output_buffer         = { gas_buffer_size.outputSizeInBytes };
    tputil::CudaDeviceBuffer compacted_size_buffer = { sizeof(size_t) };

    OptixAccelEmitDesc emit_desc = { .result = compacted_size_buffer.data(),
                                     .type   = OPTIX_PROPERTY_TYPE_COMPACTED_SIZE };

    OptixTraversableHandle handle;

    OPTIX_CHECK(optixAccelBuild(m_optix_context,
                                m_cuda_stream,
                                &accel_options,
                                &triangle_input,
                                1,
                                temp_buffer.data(),
                                temp_buffer.size(),
                                output_buffer.data(),
                                output_buffer.size(),
                                &handle,
                                &emit_desc,
                                1));

    size_t compacted_size;
    compacted_size_buffer.download(static_cast<void*>(&compacted_size), sizeof(size_t));

    if (compacted_size < gas_buffer_size.outputSizeInBytes) {
        m_gas_buffer.resize(compacted_size);
        OPTIX_CHECK(optixAccelCompact(m_optix_context,
                                      m_cuda_stream,
                                      handle,
                                      m_gas_buffer.data(),
                                      m_gas_buffer.size(),
                                      &handle));
    } else {
        m_gas_buffer = std::move(output_buffer);
    }

    return handle;
}