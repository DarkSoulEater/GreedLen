cmake_minimum_required(VERSION 3.3)
set(CMAKE_CXX_STANDARD 20)

project(source)

# include_directories(${CMAKE_CURRENT_BINARY_DIR})_

set(
    SOURCE 
        main.cpp
        driver.cpp)

add_executable(main ${SOURCE})

add_subdirectory(front-end)
add_subdirectory(visitor)

target_include_directories(
    main PRIVATE
        front-end ${CMAKE_CURRENT_BINARY_DIR}/front-end
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(main front-end visitor)
