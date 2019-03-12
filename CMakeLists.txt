cmake_minimum_required(VERSION 3.1)
project(rtdata)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)

include_directories(src)

file(GLOB SRC_FILES  src/*.cpp)

add_library( rtdata STATIC ${SRC_FILES} )
