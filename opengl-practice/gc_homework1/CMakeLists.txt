cmake_minimum_required(VERSION 3.0)
project(gc_homework1)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/*.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} glfw glad GL X11 pthread Xrandr Xi dl)