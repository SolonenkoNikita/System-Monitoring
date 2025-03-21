cmake_minimum_required(VERSION 3.22)
project(Utils)

set(CMAKE_CXX_STANDARD 20)

add_library (Utils STATIC source/Utils.cpp)

target_include_directories(Utils PUBLIC include)