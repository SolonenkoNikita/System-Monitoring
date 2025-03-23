cmake_minimum_required(VERSION 3.22)

project(System_Monitoring)

find_package(Doxygen REQUIRED)

set(DOXYGEN_INPUT 
    "${CMAKE_SOURCE_DIR}/process"
    "${CMAKE_SOURCE_DIR}/parser"
    "${CMAKE_SOURCE_DIR}/System"
    "${CMAKE_SOURCE_DIR}/Display"
    "${CMAKE_SOURCE_DIR}/Utils"
)
set(DOXYGEN_OUTPUT_DIR "${CMAKE_BINARY_DIR}/docs")

set(DOXYGEN_PROJECT_NAME "System Monitoring")
set(DOXYGEN_PROJECT_NUMBER "1.0")
set(DOXYGEN_RECURSIVE YES) 
set(DOXYGEN_GENERATE_HTML YES)  
set(DOXYGEN_GENERATE_LATEX NO)  

if (DOXYGEN_FOUND)
    if (NOT EXISTS "${CMAKE_BINARY_DIR}/Doxyfile")
        execute_process(
            COMMAND ${DOXYGEN_EXECUTABLE} -g Doxyfile
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )
    endif()

    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generating documentation with Doxygen"
    )
endif()

add_subdirectory(Dialogue)

add_subdirectory(process)

add_subdirectory(Directories)

add_subdirectory(parser)

add_subdirectory(System)

add_subdirectory(Display)

add_subdirectory(Utils)