#pragma once

#include <source_location>
#include <string>

#define TP_LOG_ARGS __FILE__, __LINE__

#define OPTIX_CHECK(call) optixCheck(call, #call, TP_LOG_ARGS)

#define CUDA_CHECK(call) cudaCheck(call, #call, TP_LOG_ARGS)

#define CUDA_SYNC_CHECK() cudaSyncCheck(TP_LOG_ARGS)

#define GL_CHECK(call)                      \
    {                                       \
        call;                               \
        glCheck(#call, TP_LOG_ARGS); \
    }

enum OptixResult;
enum cudaError;

typedef cudaError cudaError_t;

std::string exceptionMsg(const std::string& file, int line, const std::string& msg);

void optixCheck(const OptixResult& res, const std::string& call, const std::string& file, int line);

void cudaCheck(const cudaError_t& res, const std::string& call, const std::string& file, int line);

void cudaSyncCheck(const std::string& file, int line);

void glCheck(const std::string& call, const std::string& file, int line);