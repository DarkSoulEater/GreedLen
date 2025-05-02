cmake_minimum_required(VERSION 3.3)
set(CMAKE_CXX_STANDARD 20)

project(flex-bison)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

bison_target(
    BisonParser
        parser.ypp ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.cpp
        DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.hpp)

flex_target(
    FlexScanner
        lexer.lpp ${CMAKE_CURRENT_BINARY_DIR}/lexer.yy.cpp)
    
add_flex_bison_dependency(FlexScanner BisonParser)

add_library(
    flex-bison STATIC
        ${BISON_BisonParser_OUTPUTS}
        ${FLEX_FlexScanner_OUTPUTS})

target_include_directories(
    flex-bison PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}/../
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/src)