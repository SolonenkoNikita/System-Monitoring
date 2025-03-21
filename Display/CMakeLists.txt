cmake_minimum_required(VERSION 3.22)
project(Display)

set(CMAKE_CXX_STANDARD 20)

find_package(Curses REQUIRED)
find_package(fmt CONFIG REQUIRED)

add_library (Display STATIC source/Display.cpp)

target_link_libraries(Display Utils System ${CURSES_LIBRARIES} fmt::fmt)

target_include_directories(Display PUBLIC include)