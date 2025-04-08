cmake_minimum_required(VERSION 3.3)
set(CMAKE_CXX_STANDARD 20)

project(visitor)

set(
    SOURSE
        print.cpp
        graphviz.cpp
        interpreter.cpp
        llvmir.cpp
)

add_library(
    visitor STATIC
        ${SOURSE}   
)

target_include_directories(
    visitor PRIVATE
        ${CMAKE_SOURCE_DIR}/src)