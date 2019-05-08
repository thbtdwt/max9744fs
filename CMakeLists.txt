cmake_minimum_required(VERSION 3.0)

project(MAX9744_sound_daemon)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules" ${CMAKE_MODULE_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(EXE max9744d)

add_compile_options("$<$<CONFIG:RELEASE>:-O2>")
add_compile_options("$<$<CONFIG:DEBUG>:-O0;-g;-DDEBUG_TRACE_ON>")

add_compile_options(-Wall -Werror -Wextra )
add_definitions(-D_FILE_OFFSET_BITS=64)

add_subdirectory(${CMAKE_SOURCE_DIR}/src)
