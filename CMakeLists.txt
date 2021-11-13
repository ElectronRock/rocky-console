cmake_minimum_required(VERSION 3.15)
project(rocky-main)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib)
add_subdirectory(sample/maze)