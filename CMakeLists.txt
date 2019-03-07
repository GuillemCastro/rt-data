cmake_minimum_required(VERSION 3.1)
project(rtdata)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)

add_library( rtdata STATIC main.cpp)
