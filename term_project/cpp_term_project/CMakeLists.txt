cmake_minimum_required(VERSION 3.17)
project(CourseDesign)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(GUI/headers)
include_directories(MAIN/headers)

FILE(GLOB SOURCES
        "${PROJECT_SOURCE_DIR}/main.cpp"
        "${PROJECT_SOURCE_DIR}/GUI/sources/*.cpp"
        "${PROJECT_SOURCE_DIR}/GUI/headers/*.h"
        "MAIN/headers/*.h"
        "MAIN/sources/*.cpp"
        )

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
add_executable(CourseDesign
        ${SOURCES}
        )
target_link_libraries(CourseDesign Qt5::Core)
target_link_libraries(CourseDesign Qt5::Widgets)