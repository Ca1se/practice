#include "Tracer.h"

#include <iostream>
#include <format>
#include <cstdint>

#include <optix.h>
#include <optix_stack_size.h>
#include <optix_stubs.h>
#include <optix_function_table.h>
#include <optix_function_table_definition.h>
#include <cuda.h>
#include <cuda_runtime_api.h>

#include "Exception.h"
#include "Util.h"

namespace
{

void optixContextLogCallback(uint32_t level, const char* tag, const char* message, void*)
{
    std::cerr << std::format("[{}][{}]: {}", level, tag, message) << std::endl;
}

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
    const char* code = getCompiledCudaCode("pathtracer", "todo.cu", code_size);

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

}

void Tracer::buildPipeline()
{
    OptixProgramGroup program_groups[2] = { /* todo */ };
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