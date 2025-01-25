cmake_minimum_required(VERSION 3.10)
project(assignment C)

# Add the executable
add_executable(assignment main.c functions.c)

# Include directories for header files
target_include_directories(assignment PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
