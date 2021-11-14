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

#find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_library(rocky SHARED ${ROCKY_HEADERS} ${ROCKY_SOURSES} ${CURSES_LIBRARIES})
target_link_libraries(rocky ${CURSES_LIBRARIES})
target_include_directories(rocky PRIVATE ${CMAKE_SOURCE_DIR}/lib ${CURSES_INCLUDE_DIR})
