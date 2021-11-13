cmake_minimum_required(VERSION 3.15)

project(rocky)

add_definitions(-DROCKY_EXPORT=1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB ROCKY_HEADERS
    rocky/*.h
)

file(GLOB ROCKY_SOURSES
    rocky/*.cpp
)

add_library(rocky SHARED ${ROCKY_HEADERS} ${ROCKY_SOURSES})
target_include_directories(rocky PRIVATE ${CMAKE_SOURCE_DIR}/lib)
