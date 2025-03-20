cmake_minimum_required(VERSION 3.22)
project(parser)

set(CMAKE_CXX_STANDARD 20)

add_library (parser STATIC source/parser.cpp)

target_link_libraries(parser Directories)

target_include_directories(parser PUBLIC include)