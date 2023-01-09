cmake_minimum_required(VERSION 3.1)
project(d3d_project_1)

set(CMAKE_CXX_STANDARD 17)
set(dxsdk-d3dx_DIR D:\\develop\\vcpkg\\installed\\x64-windows\\share\\dxsdk-d3dx)

file(GLOB SOURCES
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/*.hpp
)

include(cmake/file_basename.cmake)

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})
define_file_basename_for_sources(${PROJECT_NAME})

# find_package(dxsdk-d3dx CONFIG REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE Microsoft::D3DX9 Microsoft::D3DX10 Microsoft::D3DX11)
target_link_libraries(${PROJECT_NAME} PRIVATE
    d3d11.lib dxgi.lib dxguid.lib uuid.lib
    kernel32.lib user32.lib 
    comdlg32.lib advapi32.lib shell32.lib
    ole32.lib oleaut32.lib
)
