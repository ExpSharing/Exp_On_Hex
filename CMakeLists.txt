cmake_minimum_required(VERSION 3.20)
project(exp_on_hex C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

add_executable(exp_hex_table src/exp_hex_tables.c)

include_directories(include)
add_library(hex_table INTERFACE include/hex_tables.h)

target_link_libraries(exp_hex_table PRIVATE hex_table)
