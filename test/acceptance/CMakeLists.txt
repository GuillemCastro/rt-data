cmake_minimum_required(VERSION 3.1)
project(rtdata_acceptance)

SET(CMAKE_CXX_FLAGS "-g -O0")
SET(CMAKE_C_FLAGS "-g -O0")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)
set(CMAKE_CXX_STANDARD 17)

file(GLOB SRC_FILES Application.cpp)

add_executable(rtdata_acceptance_test ${SRC_FILES})

find_package(Threads REQUIRED)

#find_package(g3logger)

find_package(nlohmann_json)

target_link_libraries(
    rtdata_acceptance_test
    rtdata
    Threads::Threads
    nlohmann_json::nlohmann_json
    SQLiteCpp
    sqlite3
    dl
    g3logger
)

add_definitions(-DWITH_G3LOG)
