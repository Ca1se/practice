#include "Tracer.h"

#include <iostream>
#include <format>
#include <stdexcept>
#include <cstdint>
#include <cassert>
#include <cstring>

#include <optix.h>
#include <optix_stack_size.h>
#include <optix_stubs.h>
#include <optix_function_table.h>
#include <optix_function_table_definition.h>
#include <cuda.h>
#include <cuda_runtime_api.h>

#include "Exception.h"
#include "Util.h"
#include "CudaBufferView.h"

namespace
{

void optixContextLogCallback(uint32_t level, const char* tag, const char* message, void*)
{
    std::cerr << std::format("[{}][{}]: {}", level, tag, message) << std::endl;
}

struct
{
    OptixIndicesFormat indexFormat(CudaTriangleIndexBufferView::TriangleIndexFormat index_format)
    {
        switch (index_format) {
        case CudaBufferView<TriangleIndexType>::TRIANGLE_INDEX_FORMAT_SHORT3:
        case CudaBufferView<TriangleIndexType>::TRIANGLE_INDEX_FORMAT_USHORT3:
            return OPTIX_INDICES_FORMAT_UNSIGNED_SHORT3;
        case CudaBufferView<TriangleIndexType>::TRIANGLE_INDEX_FORMAT_INT3:
        case CudaBufferView<TriangleIndexType>::TRIANGLE_INDEX_FORMAT_UINT3:
            return OPTIX_INDICES_FORMAT_UNSIGNED_INT3;
        default:
            throw std::runtime_error{ std::format("indexFormat(): Unrecognized index format {}", static_cast<uint32_t>(index_format)) };
        }
    }
} g_mapper;

}

Tracer::Tracer()
{
    createOptixContext();
    buildModule();
    buildProgramGroups();
    buildPipeline();
}

Tracer::~Tracer() noexcept
{
    try {
        if (m_pipeline)
            OPTIX_CHECK(optixPipelineDestroy(m_pipeline));
        if (m_raygen_pinhole_pg)
            OPTIX_CHECK(optixProgramGroupDestroy(m_raygen_pinhole_pg));
        if (m_hit_radiance_pg)
            OPTIX_CHECK(optixProgramGroupDestroy(m_hit_radiance_pg));
        if (m_hit_occlusion_pg)
            OPTIX_CHECK(optixProgramGroupDestroy(m_hit_occlusion_pg));
        if (m_miss_radiance_pg)
            OPTIX_CHECK(optixProgramGroupDestroy(m_miss_radiance_pg));
        if (m_miss_occlusion_pg)
            OPTIX_CHECK(optixProgramGroupDestroy(m_miss_occlusion_pg));
        if (m_module)
            OPTIX_CHECK(optixModuleDestroy(m_module));
        if (m_context)
            OPTIX_CHECK(optixDeviceContextDestroy(m_context));

        Scene::cleanup(*m_scene);
    } catch (std::exception& e) {
        std::cerr << std::format("Tracer::~Tracer(): {}", e.what()) << std::endl;
    }
}

void Tracer::loadScene(std::shared_ptr<Scene> scene)
{
    m_scene = scene;
    assert(scene);
    buildAccelerationStructures();
    buildShaderBindingTable();
}

void Tracer::createOptixContext()
{
    CUDA_CHECK(cudaFree(nullptr));

    CUcontext cuda_context = nullptr;
    OptixDeviceContextOptions options = {
        .logCallbackFunction = optixContextLogCallback,
        .logCallbackLevel    = 4
    };
    OPTIX_CHECK(optixInit());
    OPTIX_CHECK(optixDeviceContextCreate(cuda_context, &options, &m_context));
}

void Tracer::buildAccelerationStructures()
{
    // build geometry acceleration structures
    static constexpr uint32_t triangle_input_flags[2] = { OPTIX_GEOMETRY_FLAG_DISABLE_ANYHIT | OPTIX_GEOMETRY_FLAG_DISABLE_TRIANGLE_FACE_CULLING, OPTIX_GEOMETRY_FLAG_DISABLE_ANYHIT };

    std::vector<OptixBuildInput> build_inputs = {};
    for (const auto& mesh: m_scene->meshes) {
        size_t submesh_num = mesh->indices.size();
        assert(mesh->positions.size() == submesh_num
               && mesh->normals.size() == submesh_num
               && mesh->texcoords.size() == submesh_num
               && mesh->colors.size() == submesh_num
               && mesh->material_indices.size() == submesh_num);
        for (size_t i = 0; i < submesh_num; i++) {
            int32_t material_index = mesh->material_indices[i];
            uint32_t flag_index    = material_index >= 0
                                     ? static_cast<uint32_t>(m_scene->materials[material_index].back_culling)
                                     : 1;
            build_inputs.push_back(OptixBuildInput{
                .type = OPTIX_BUILD_INPUT_TYPE_TRIANGLES,
                .triangleArray = OptixBuildInputTriangleArray{
                    .vertexBuffers       = &mesh->positions[i].buffer_ptr,
                    .numVertices         = mesh->positions[i].element_count,
                    .vertexFormat        = OPTIX_VERTEX_FORMAT_FLOAT3,
                    .vertexStrideInBytes = mesh->positions[i].stride_byte_size,
                    .indexBuffer         = mesh->indices[i].buffer_ptr,
                    .numIndexTriplets    = mesh->indices[i].element_count,
                    .indexFormat         = g_mapper.indexFormat(mesh->indices[i].index_format),
                    .indexStrideInBytes  = mesh->indices[i].stride_byte_size,
                    .preTransform        = 0,
                    .flags               = &triangle_input_flags[flag_index],
                    .numSbtRecords       = 1
                }
            });
        }
    }

    OptixAccelBuildOptions accel_build_options = {
        .buildFlags = OPTIX_BUILD_FLAG_ALLOW_COMPACTION,
        .operation  = OPTIX_BUILD_OPERATION_BUILD
    };
    OptixAccelBufferSizes gas_buffer_size = {};
    OPTIX_CHECK(optixAccelComputeMemoryUsage(m_context, &accel_build_options, build_inputs.data(), build_inputs.size(), &gas_buffer_size));

    CudaDeviceBuffer temp_buffer(gas_buffer_size.tempSizeInBytes);
    CudaDeviceBuffer output_buffer(gas_buffer_size.outputSizeInBytes);
    CudaDeviceBuffer compacted_size_buffer(sizeof(size_t));
    OptixAccelEmitDesc emit_desc = {
        .result = compacted_size_buffer.data(),
        .type   = OPTIX_PROPERTY_TYPE_COMPACTED_SIZE
    };
    OptixTraversableHandle gas_handle = 0;
    CudaDeviceBuffer       gas_buffer;
    OPTIX_CHECK(optixAccelBuild(m_context,
                                0, // stream
                                &accel_build_options,
                                build_inputs.data(),
                                static_cast<uint32_t>(build_inputs.size()),
                                temp_buffer.data(),
                                temp_buffer.size(),
                                output_buffer.data(),
                                output_buffer.size(),
                                &gas_handle,
                                &emit_desc,
                                1));
    CUDA_SYNC_CHECK();

    size_t compacted_size = 0;
    compacted_size_buffer.download(static_cast<void*>(&compacted_size), sizeof(size_t));

    if (compacted_size < gas_buffer_size.outputSizeInBytes) {
        gas_buffer.resize(compacted_size);
        OPTIX_CHECK(optixAccelCompact(m_context,
                                      0, // stream
                                      gas_handle,
                                      gas_buffer.data(),
                                      gas_buffer.size(),
                                      &gas_handle));
        CUDA_SYNC_CHECK();
    } else {
        gas_buffer = std::move(output_buffer);
    }

    // build instance acceleration structures
    size_t instance_num = m_scene->instances.size();

    std::vector<OptixInstance> optix_instances = {};
    uint32_t sbt_offset = 0;
    for (size_t i = 0; i < instance_num; i++) {
        optix_instances.push_back(OptixInstance{
            .transform         = {},
            .instanceId        = static_cast<uint32_t>(i),
            .sbtOffset         = sbt_offset,
            .visibilityMask    = 1,
            .flags             = OPTIX_INSTANCE_FLAG_NONE,
            .traversableHandle = gas_handle
        });
        memcpy(optix_instances.back().transform, m_scene->instances[i]->transform.data(), 12 * sizeof(float));
    }
}

void Tracer::buildModule()
{
    OptixModuleCompileOptions options = {
#if !defined (NDEBUG)
        .optLevel   = OPTIX_COMPILE_OPTIMIZATION_LEVEL_0,
        .debugLevel = OPTIX_COMPILE_DEBUG_LEVEL_FULL
#endif
    };

    m_pipeline_compile_options.usesMotionBlur                   = false;
    m_pipeline_compile_options.traversableGraphFlags            = OPTIX_TRAVERSABLE_GRAPH_FLAG_ALLOW_SINGLE_LEVEL_INSTANCING;
    m_pipeline_compile_options.numPayloadValues                 = 2;
    m_pipeline_compile_options.numAttributeValues               = 2;
    m_pipeline_compile_options.exceptionFlags                   = OPTIX_EXCEPTION_FLAG_NONE;
    m_pipeline_compile_options.pipelineLaunchParamsVariableName = "g_launch_params";
    m_pipeline_compile_options.usesPrimitiveTypeFlags           = static_cast<uint32_t>(OPTIX_PRIMITIVE_TYPE_FLAGS_TRIANGLE);

    size_t code_size = 0;
    const char* code = getCompiledCudaCode("pathtracer", "PathTracing.cu", code_size);

    OPTIX_CHECK(optixModuleCreate(m_context,
                                  &options,
                                  &m_pipeline_compile_options,
                                  code,
                                  code_size,
                                  nullptr,
                                  nullptr,
                                  &m_module));
}

void Tracer::buildProgramGroups()
{
    OptixProgramGroupOptions options = {};
    char log[2048]  = {};
    size_t log_size = 0;

    {
        OptixProgramGroupDesc desc = {
            .kind = OPTIX_PROGRAM_GROUP_KIND_RAYGEN,
            .raygen = {
                .module = m_module,
                .entryFunctionName = "__raygen__pinhole"
            }
        };
        OPTIX_CHECK(optixProgramGroupCreate(m_context,
                                            &desc,
                                            1,
                                            &options,
                                            log,
                                            &log_size,
                                            &m_raygen_pinhole_pg));
    }

    if (log_size > 0)
        std::cerr << log << std::endl;

    {
        OptixProgramGroupDesc desc = {
            .kind = OPTIX_PROGRAM_GROUP_KIND_HITGROUP,
            .hitgroup = {
                .moduleCH = m_module,
                .entryFunctionNameCH = "__closesthit__radiance"
            }
        };
        OPTIX_CHECK(optixProgramGroupCreate(m_context,
                                            &desc,
                                            1,
                                            &options,
                                            log,
                                            &log_size,
                                            &m_hit_radiance_pg));
    }

    if (log_size > 0)
        std::cerr << log << std::endl;

    {
        OptixProgramGroupDesc desc = {
            .kind = OPTIX_PROGRAM_GROUP_KIND_HITGROUP,
            .hitgroup = {
                .moduleCH = m_module,
                .entryFunctionNameCH = "__closesthit__occlusion"
            }
        };
        OPTIX_CHECK(optixProgramGroupCreate(m_context,
                                            &desc,
                                            1,
                                            &options,
                                            log,
                                            &log_size,
                                            &m_hit_occlusion_pg));
    }

    if (log_size > 0)
        std::cerr << log << std::endl;

    {
        OptixProgramGroupDesc desc = {
            .kind = OPTIX_PROGRAM_GROUP_KIND_MISS,
            .miss = {
                .module = m_module,
                .entryFunctionName = "__miss__radiance"
            }
        };
        OPTIX_CHECK(optixProgramGroupCreate(m_context,
                                            &desc,
                                            1,
                                            &options,
                                            log,
                                            &log_size,
                                            &m_miss_radiance_pg));
    }

    if (log_size > 0)
        std::cerr << log << std::endl;
    
    {
        OptixProgramGroupDesc desc = {
            .kind = OPTIX_PROGRAM_GROUP_KIND_MISS,
            .miss = {
                .module = m_module,
                .entryFunctionName = "__miss__occlusion"
            }
        };
        OPTIX_CHECK(optixProgramGroupCreate(m_context,
                                            &desc,
                                            1,
                                            &options,
                                            log,
                                            &log_size,
                                            &m_miss_radiance_pg));
    }

    if (log_size > 0)
        std::cerr << log << std::endl;
}

void Tracer::buildPipeline()
{
    OptixProgramGroup program_groups[] = {
        m_raygen_pinhole_pg,
        m_hit_radiance_pg,
        m_hit_occlusion_pg,
        m_miss_radiance_pg,
        m_miss_occlusion_pg
    };
    OptixPipelineLinkOptions pipeline_link_options   = { .maxTraceDepth = 2 };
    OPTIX_CHECK(optixPipelineCreate(m_context,
                                    &m_pipeline_compile_options,
                                    &pipeline_link_options,
                                    program_groups,
                                    static_cast<uint32_t>(std::size(program_groups)),
                                    nullptr,
                                    nullptr,
                                    &m_pipeline));
    OptixStackSizes stack_sizes = {};
    for (auto program_group: program_groups)
        OPTIX_CHECK(optixUtilAccumulateStackSizes(program_group, &stack_sizes, m_pipeline));

    uint32_t max_trace_depth = 2;
    uint32_t max_cc_depth    = 0;
    uint32_t max_dc_depth    = 0;
    uint32_t direct_callable_stack_size_from_traversal;
    uint32_t direct_callable_stack_size_from_state;
    uint32_t continuation_stack_size;
    OPTIX_CHECK(optixUtilComputeStackSizes(&stack_sizes,
                                           max_trace_depth,
                                           max_cc_depth,
                                           max_dc_depth,
                                           &direct_callable_stack_size_from_traversal,
                                           &direct_callable_stack_size_from_state,
                                           &continuation_stack_size));
    uint32_t max_traversal_depth = 1;
    OPTIX_CHECK(optixPipelineSetStackSize(m_pipeline,
                                          direct_callable_stack_size_from_traversal,
                                          direct_callable_stack_size_from_state,
                                          continuation_stack_size,
                                          max_traversal_depth));
}

void Tracer::buildShaderBindingTable()
{

}