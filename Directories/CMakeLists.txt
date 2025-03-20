cmake_minimum_required(VERSION 3.22)
project(Directories)

set(CMAKE_CXX_STANDARD 20)

add_library(Directories INTERFACE)

target_include_directories(Directories INTERFACE include)