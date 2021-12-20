cmake_minimum_required(VERSION 3.0)
project(WebServer)

set(CMAKE_CXX_STANDARD 11)
FILE(GLOB SRC
    ${PROJECT_SOURCE_DIR}/src/ui/*.cc 
    ${PROJECT_SOURCE_DIR}/src/ui/*.hh
    )

find_package(oatpp REQUIRED)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} oatpp::oatpp)
