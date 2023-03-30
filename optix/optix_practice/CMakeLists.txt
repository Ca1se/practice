cmake_minimum_required(VERSION 3.17)
project(optix_practice)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CUDA_ARCHITECTURES 75)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

add_compile_options($<$<C_COMPILER_ID:MSVC>:/utf-8>)
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/utf-8>)

include(cmake/configure_optix.cmake)

include_directories(third_party)
include_directories(third_party/glfw/include)
include_directories(tputil)

link_directories("${CMAKE_BINARY_DIR}/lib")

add_subdirectory(third_party)
add_subdirectory(tputil)

add_subdirectory(optix_practice)
add_subdirectory(simple_raytracer)