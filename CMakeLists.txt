cmake_minimum_required(VERSION 3.5.1)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(greed VERSION 1.0)

add_subdirectory(src)

add_custom_target(run
  COMMAND ${CMAKE_SOURCE_DIR}/build/src/main
  DEPENDS src
)