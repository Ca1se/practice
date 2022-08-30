cmake_minimum_required(VERSION 3.0)
project(process_schedule)

set(CMAKE_C_STANDARD 11)

add_definitions(
    -DOUTPUT_FILE_DIR="${PROJECT_SOURCE_DIR}"
)

file(GLOB SRC
    ${PROJECT_SOURCE_DIR}/src/*.c
    ${PROJECT_SOURCE_DIR}/src/*.h
)

add_executable(${PROJECT_NAME} ${SRC})

