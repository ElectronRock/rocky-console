cmake_minimum_required(VERSION 3.15)

project(potentials)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB P_HEADERS
    *.h
)

file(GLOB P_SOURSES
    *.cpp
)

add_executable(potentials ${P_HEADERS} ${P_SOURSES})

target_include_directories(potentials PRIVATE ${CMAKE_SOURCE_DIR}/lib)
target_link_libraries(potentials rocky)
