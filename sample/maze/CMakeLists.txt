cmake_minimum_required(VERSION 3.15)

project(maze)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB MAZE__HEADERS
    *.h
)

file(GLOB MAZE__SOURSES
    *.cpp
)

add_executable(maze ${MAZE__HEADERS} ${MAZE__SOURSES})

target_include_directories(maze PRIVATE ${CMAKE_SOURCE_DIR}/lib)
target_link_libraries(maze rocky)
