cmake_minimum_required(VERSION 3.22)
project(process)

set(CMAKE_CXX_STANDARD 20)

add_library (process STATIC source/process.cpp)

target_link_libraries(process parser)

target_include_directories(process PUBLIC include)