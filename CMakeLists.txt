cmake_minimum_required(VERSION 3.1)
project(rtdata)

SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(libs/nlohmann_json)
add_subdirectory(libs/SQLiteCpp)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")
find_package(CppUnit REQUIRED)

find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)

include_directories(src)

include_directories(libs/SQLiteCpp/include)

file(GLOB SRC_FILES  src/*.cpp src/concurrent/*.cpp src/time/*.cpp src/serialization/*.cpp src/utils/*.cpp)

add_library( rtdata STATIC ${SRC_FILES} )

target_link_libraries(rtdata Threads::Threads )

target_link_libraries(rtdata dl)

target_link_libraries(rtdata nlohmann_json::nlohmann_json)

target_link_libraries(rtdata sqlite3)

target_link_libraries(rtdata SQLiteCpp)

IF(NOT(MSVC OR MINGW))
    include_directories(${CPPUNIT_INCLUDE_DIR})
    include_directories(test)
    include_directories(libs/SQLiteCpp/include)
    file(GLOB TEST_FILES test/*.cpp src/*.cpp src/concurrent/*.cpp src/time/*.cpp src/serialization/*.cpp src/utils/*.cpp)
    list(REMOVE_ITEM TEST_FILES "${CMAKE_SOURCE_DIR}/src/main.cpp")
    add_executable(rtdata_test ${TEST_FILES})
    target_link_libraries(rtdata_test cppunit)
    target_link_libraries(rtdata_test Threads::Threads )
    target_link_libraries(rtdata_test dl)
    target_link_libraries(rtdata_test nlohmann_json::nlohmann_json)
    target_link_libraries(rtdata_test sqlite3)
    target_link_libraries(rtdata_test SQLiteCpp)
ENDIF()
