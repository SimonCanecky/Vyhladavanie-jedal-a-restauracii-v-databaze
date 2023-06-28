cmake_minimum_required(VERSION 3.24)
project(Z4 C)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -std=c11")

add_executable(Z4 src/z4.c src/data.c)
target_include_directories(Z4 PRIVATE include)
target_link_libraries(Z4 m)
