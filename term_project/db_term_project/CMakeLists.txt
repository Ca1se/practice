cmake_minimum_required(VERSION 3.0)
project(WebServer)

set(CMAKE_CXX_STANDARD 11)
FILE(GLOB SRC
    ${PROJECT_SOURCE_DIR}/src/ui/*.cc 
    ${PROJECT_SOURCE_DIR}/src/ui/*.hh
    ${PROJECT_SOURCE_DIR}/src/*.cc
    ${PROJECT_SOURCE_DIR}/src/*.hh
    ${PROJECT_SOURCE_DIR}/src/db/*.cc
    ${PROJECT_SOURCE_DIR}/src/db/*.hh
    ${PROJECT_SOURCE_DIR}/src/dto/*.cc
    ${PROJECT_SOURCE_DIR}/src/dto/*.hh
    ${PROJECT_SOURCE_DIR}/src/service/*.cc
    ${PROJECT_SOURCE_DIR}/src/service/*.hh
    )

find_package(oatpp 1.3.0 REQUIRED)
find_package(oatpp-sqlite 1.3.0 REQUIRED)
find_package(Threads REQUIRED)

add_definitions(
        -DRESOURCE_DIR_PATH="${CMAKE_CURRENT_SOURCE_DIR}/res"
        -DSQL_INIT_FILE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/sql"
        -DDATABASE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/db.sqlite"
)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME}
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-sqlite
)
