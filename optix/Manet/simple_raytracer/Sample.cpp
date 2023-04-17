#include "Sample.h"

#include <optix_function_table_definition.h>

#include "cuda/RecordData.h"
#include "SimpleRaytracer.h"

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

void resizeAndUpload(tputil::CudaDeviceBuffer& dest, const void* src, size_t byte_size)
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

Sample::Sample(const tputil::Model& model)
    : m_model{ model }
{
    initOptix();
    createContext();

    m_launch_params = LaunchParams{
        .frame  = { .id = 0, .color_buffer = nullptr },
        .handle = buildAccel(),
    };

    createModule();
    createRaygenPrograms();
    createMissPrograms();
    createHitgroupPrograms();
    createPipeline();
    buildSBT();
}

Sample::Sample(tputil::Model&& model)
    : m_model{ std::forward<tputil::Model>(model) }
{
    initOptix();
    createContext();

    m_launch_params = LaunchParams{
        .frame  = { .id = 0, .color_buffer = nullptr },
        .handle = buildAccel(),
    };

    createModule();
    createRaygenPrograms();
    createMissPrograms();
    createHitgroupPrograms();
    createPipeline();
    buildSBT();
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
    m_module_compile_options = OptixModuleCompileOptions{};
#if !defined(NDEBUG)
    m_module_compile_options.optLevel   = OPTIX_COMPILE_OPTIMIZATION_LEVEL_0;
    m_module_compile_options.debugLevel = OPTIX_COMPILE_DEBUG_LEVEL_FULL;
#endif

    m_pipeline_compile_options = OptixPipelineCompileOptions{
        .usesMotionBlur                   = false,
        .traversableGraphFlags            = OPTIX_TRAVERSABLE_GRAPH_FLAG_ALLOW_SINGLE_GAS,
        .numPayloadValues                 = 2,
        .numAttributeValues               = 2,
        .exceptionFlags                   = OPTIX_EXCEPTION_FLAG_NONE,
        .pipelineLaunchParamsVariableName = "g_optix_launch_params",
        .usesPrimitiveTypeFlags = static_cast<uint32_t>(OPTIX_PRIMITIVE_TYPE_FLAGS_TRIANGLE)
    };


    size_t code_size = 0;
    const char* code = tputil::getCompiledCudaCode("simple_raytracer", "DeviceProgram.cu", code_size);

    OPTIX_CHECK(optixModuleCreate(m_optix_context,
                                  &m_module_compile_options,
                                  &m_pipeline_compile_options,
                                  code,
                                  code_size,
                                  nullptr,
                                  nullptr,
                                  &m_module));
}

void
Sample::createRaygenPrograms()
{
    m_raygen_program_groups.resize(1);

    OptixProgramGroupOptions options = {};
    OptixProgramGroupDesc desc = {
        .kind   = OPTIX_PROGRAM_GROUP_KIND_RAYGEN,
        .raygen = OptixProgramGroupSingleModule{
            .module            = m_module,
            .entryFunctionName = "__raygen__pinhole"
        }
    };

    char log[2048];
    size_t log_size = sizeof(log);
    OPTIX_CHECK(optixProgramGroupCreate(m_optix_context,
                                        &desc,
                                        1,
                                        &options,
                                        log,
                                        &log_size,
                                        &m_raygen_program_groups[0]));

    if (log_size > 1)
        LOG_INFO(log);
}

void
Sample::createMissPrograms()
{
    m_miss_program_groups.resize(1);

    OptixProgramGroupOptions options = {};
    OptixProgramGroupDesc desc = {
        .kind = OPTIX_PROGRAM_GROUP_KIND_MISS,
        .miss = OptixProgramGroupSingleModule{
            .module            = m_module,
            .entryFunctionName = "__miss__radiance"
        }
    };

    char log[2048];
    size_t log_size = sizeof(log);
    OPTIX_CHECK(optixProgramGroupCreate(m_optix_context,
                                        &desc,
                                        1,
                                        &options,
                                        log,
                                        &log_size,
                                        &m_miss_program_groups[0]));

    if (log_size > 1)
        LOG_INFO(log);
}

void
Sample::createHitgroupPrograms()
{
    m_hitgroup_program_groups.resize(1);

    OptixProgramGroupOptions options = {};
    OptixProgramGroupDesc desc = {
        .kind     = OPTIX_PROGRAM_GROUP_KIND_HITGROUP,
        .hitgroup = OptixProgramGroupHitgroup{
            .moduleCH            = m_module,
            .entryFunctionNameCH = "__closesthit__radiance",
            .moduleAH            = m_module,
            .entryFunctionNameAH = "__anyhit__back_culling"
        }
    };

    char log[2048];
    size_t log_size = sizeof(log);
    OPTIX_CHECK(optixProgramGroupCreate(m_optix_context,
                                        &desc,
                                        1,
                                        &options,
                                        log,
                                        &log_size,
                                        &m_hitgroup_program_groups[0]));

    if (log_size > 1)
        LOG_INFO(log);
}

void Sample::createPipeline()
{
    std::vector<OptixProgramGroup> groups;

    groups.insert(groups.end(), m_raygen_program_groups.begin(), m_raygen_program_groups.end());
    groups.insert(groups.end(), m_miss_program_groups.begin(), m_miss_program_groups.end());
    groups.insert(groups.end(), m_hitgroup_program_groups.begin(), m_hitgroup_program_groups.end());

    m_pipeline_link_options = OptixPipelineLinkOptions{ .maxTraceDepth = 2 };

    OPTIX_CHECK(optixPipelineCreate(m_optix_context,
                                    &m_pipeline_compile_options,
                                    &m_pipeline_link_options,
                                    groups.data(),
                                    static_cast<uint32_t>(groups.size()),
                                    nullptr,
                                    nullptr,
                                    &m_pipeline));

    OptixStackSizes stack_sizes = {};
    for(size_t i = 0; i < groups.size(); i++) {
        OPTIX_CHECK(optixUtilAccumulateStackSizes(groups[i], &stack_sizes, m_pipeline));
    }

    uint32_t direct_callable_stack_size_from_traversal;
    uint32_t direct_callable_stack_size_from_state;
    uint32_t continuation_stack_size;
    OPTIX_CHECK(optixUtilComputeStackSizes(&stack_sizes,
                                           2,
                                           0,
                                           0,
                                           &direct_callable_stack_size_from_traversal,
                                           &direct_callable_stack_size_from_state,
                                           &continuation_stack_size));
                        
    OPTIX_CHECK(optixPipelineSetStackSize(m_pipeline,
                                          direct_callable_stack_size_from_traversal,
                                          direct_callable_stack_size_from_state,
                                          continuation_stack_size,
                                          1));
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
        rec.data.background_color = make_float3(0.5f, 0.7f, 1.0f);
        miss_records.push_back(rec);
    }
    resizeAndUpload(m_miss_records_buffer, miss_records.data(), miss_records.size() * sizeof(MissRecord));
    m_shader_binding_table.missRecordBase          = m_miss_records_buffer.data();
    m_shader_binding_table.missRecordStrideInBytes = sizeof(MissRecord);
    m_shader_binding_table.missRecordCount         = static_cast<int>(miss_records.size());

    std::vector<HitgroupRecord> hitgroup_records;
    const auto& meshes = m_model.meshes;
    size_t mesh_num = meshes.size();
    m_normal_buffers.resize(mesh_num);
    m_texcoord_buffers.resize(mesh_num);
    m_normal_index_buffers.resize(mesh_num);
    m_texcoord_index_buffers.resize(mesh_num);
    for (int i = 0; i <mesh_num; i++) {
        resizeAndUpload(m_normal_buffers[i], meshes[i]->normals.data(), sizeof(float3) * meshes[i]->normals.size());
        resizeAndUpload(m_texcoord_buffers[i], meshes[i]->texcoords.data(), sizeof(float2) * meshes[i]->texcoords.size());
        resizeAndUpload(m_normal_index_buffers[i], meshes[i]->normal_indices.data(), sizeof(int32_t) * meshes[i]->normal_indices.size());
        resizeAndUpload(m_texcoord_index_buffers[i], meshes[i]->texcoord_indices.data(), sizeof(int32_t) * meshes[i]->texcoord_indices.size());
        HitgroupRecord rec = {
            .header = {},
            .data = HitgroupData{
                .vertices = reinterpret_cast<float3*>(m_vertex_buffers[i].data()),
                .normals  = reinterpret_cast<float3*>(m_normal_buffers[i].data()),
                .texcoords = reinterpret_cast<float2*>(m_texcoord_buffers[i].data()),
                .vertex_indices = reinterpret_cast<int3*>(m_vertex_index_buffers[i].data()),
                .normal_indices = reinterpret_cast<int3*>(m_normal_index_buffers[i].data()),
                .texcoord_indices = reinterpret_cast<int3*>(m_texcoord_index_buffers[i].data()),
                .diffuse_color = m_model.meshes[i]->diffuse_color
            }
        };
        OPTIX_CHECK(optixSbtRecordPackHeader(m_hitgroup_program_groups[0], static_cast<void*>(&rec)));
        hitgroup_records.push_back(rec);
    }
    resizeAndUpload(m_hitgroup_records_buffer,
                    hitgroup_records.data(),
                    sizeof(HitgroupRecord) * hitgroup_records.size());
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

OptixTraversableHandle Sample::buildAccel()
{
    static constexpr uint32_t triangle_input_flags = OPTIX_GEOMETRY_FLAG_NONE;

    const std::vector<std::shared_ptr<tputil::Mesh>>& meshes = m_model.meshes;
    size_t input_size = meshes.size();
    std::vector<CUdeviceptr> vertex_buffer_cuptr(input_size);
    std::vector<CUdeviceptr> index_buffer_cuptr(input_size);
    std::vector<OptixBuildInput> build_inputs(input_size);
    m_vertex_buffers.resize(input_size);
    m_vertex_index_buffers.resize(input_size);

    for(size_t i = 0; i < input_size; i++) {
        const auto& vertices = meshes[i]->vertices;
        const auto& vertex_indices = meshes[i]->vertex_indices;
        tputil::CudaDeviceBuffer vb{ static_cast<const void*>(vertices.data()),
                                     sizeof(float3) * vertices.size() };
        tputil::CudaDeviceBuffer ib{ static_cast<const void*>(vertex_indices.data()),
                                     sizeof(int32_t) * vertex_indices.size() };

        vertex_buffer_cuptr[i] = vb.data();
        index_buffer_cuptr[i] = ib.data();

        m_vertex_buffers[i] = std::move(vb);
        m_vertex_index_buffers[i] = std::move(ib);

        OptixBuildInput triangle_input = {
            .type = OPTIX_BUILD_INPUT_TYPE_TRIANGLES,
            .triangleArray = OptixBuildInputTriangleArray{
                .vertexBuffers               = &vertex_buffer_cuptr[i],
                .numVertices                 = static_cast<uint32_t>(vertices.size()),
                .vertexFormat                = OPTIX_VERTEX_FORMAT_FLOAT3,
                .vertexStrideInBytes         = sizeof(float3),
                .indexBuffer                 = index_buffer_cuptr[i],
                .numIndexTriplets            = static_cast<uint32_t>(vertex_indices.size() / 3),
                .indexFormat                 = OPTIX_INDICES_FORMAT_UNSIGNED_INT3,
                .indexStrideInBytes          = sizeof(int3),
                .preTransform                = 0,
                .flags                       = &triangle_input_flags,
                .numSbtRecords               = 1,
                .sbtIndexOffsetBuffer        = 0,
                .sbtIndexOffsetSizeInBytes   = 0,
                .sbtIndexOffsetStrideInBytes = 0
            }
        };
        build_inputs[i] = triangle_input;
    }

    OptixAccelBuildOptions accel_options  = { .buildFlags = OPTIX_BUILD_FLAG_ALLOW_COMPACTION,
                                              .operation  = OPTIX_BUILD_OPERATION_BUILD };
    OptixAccelBufferSizes gas_buffer_size = {};

    OPTIX_CHECK(optixAccelComputeMemoryUsage(m_optix_context, &accel_options, build_inputs.data(), static_cast<uint32_t>(input_size), &gas_buffer_size));

    tputil::CudaDeviceBuffer temp_buffer{ gas_buffer_size.tempSizeInBytes };
    tputil::CudaDeviceBuffer output_buffer{ gas_buffer_size.outputSizeInBytes };
    tputil::CudaDeviceBuffer compacted_size_buffer{ sizeof(size_t) };

    OptixAccelEmitDesc emit_desc = { .result = compacted_size_buffer.data(),
                                     .type   = OPTIX_PROPERTY_TYPE_COMPACTED_SIZE };

    OptixTraversableHandle handle = 0;

    OPTIX_CHECK(optixAccelBuild(m_optix_context,
                                m_cuda_stream,
                                &accel_options,
                                build_inputs.data(),
                                static_cast<uint32_t>(input_size),
                                temp_buffer.data(),
                                temp_buffer.size(),
                                output_buffer.data(),
                                output_buffer.size(),
                                &handle,
                                &emit_desc,
                                1));
    CUDA_SYNC_CHECK();

    size_t compacted_size = 0;
    compacted_size_buffer.download(static_cast<void*>(&compacted_size), sizeof(size_t));

    if (compacted_size < gas_buffer_size.outputSizeInBytes) {
        m_gas_buffer.resize(compacted_size);
        OPTIX_CHECK(optixAccelCompact(m_optix_context,
                                      m_cuda_stream,
                                      handle,
                                      m_gas_buffer.data(),
                                      m_gas_buffer.size(),
                                      &handle));
        CUDA_SYNC_CHECK();
    } else {
        m_gas_buffer = std::move(output_buffer);
    }

    return handle;
}