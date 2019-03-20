cmake_minimum_required(VERSION 3.1)
project(rtdata)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")
find_package(CppUnit REQUIRED)

find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)

include_directories(src)

file(GLOB SRC_FILES  src/*.cpp src/concurrent/*.cpp src/time/*.cpp)

add_library( rtdata STATIC ${SRC_FILES} )

target_link_libraries(rtdata Threads::Threads )

target_link_libraries(rtdata dl)

IF(NOT(MSVC OR MINGW))
    include_directories(${CPPUNIT_INCLUDE_DIR})
    include_directories(test)
    file(GLOB TEST_FILES test/*.cpp src/*.cpp src/concurrent/*.cpp src/time/*.cpp)
    list(REMOVE_ITEM TEST_FILES "${CMAKE_SOURCE_DIR}/src/main.cpp")
    add_executable(rtdata_test ${TEST_FILES})
    target_link_libraries(rtdata_test cppunit)
    target_link_libraries(rtdata_test Threads::Threads )
    target_link_libraries(rtdata_test dl)
ENDIF()
