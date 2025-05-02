cmake_minimum_required(VERSION 3.3)
set(CMAKE_CXX_STANDARD 20)

project(front-end)

set(
    SOURCE
        frontend.cpp
)

add_subdirectory(flex-bison)

add_library(
    front-end STATIC
        ${SOURCE}
)

target_link_libraries(
    front-end PRIVATE
        flex-bison
)

target_include_directories(
    front-end PRIVATE
        flex-bison
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_SOURCE_DIR}/src
)