cmake_minimum_required(VERSION 3.22)
project(System)

set(CMAKE_CXX_STANDARD 20)

add_library (System STATIC source/System.cpp)

target_link_libraries(System process)

target_include_directories(System PUBLIC include)