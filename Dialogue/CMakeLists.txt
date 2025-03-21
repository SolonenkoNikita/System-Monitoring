cmake_minimum_required(VERSION 3.22)
project(Dialogue)

set(CMAKE_CXX_STANDARD 20)

find_package(Curses REQUIRED)

add_executable(Dialogue source/main.cpp)

target_link_libraries(Dialogue Display System parser ${CURSES_LIBRARIES})