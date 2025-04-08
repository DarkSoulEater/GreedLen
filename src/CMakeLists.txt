cmake_minimum_required(VERSION 3.3)
set(CMAKE_CXX_STANDARD 20)

project(source)

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "LLVM include dir: ${LLVM_INCLUDE_DIRS}")

# Подключите LLVM
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Свяжите LLVM-библиотеки с вашей программой
llvm_map_components_to_libnames(llvm_libs core irreader support)  # Укажите нужные компоненты

set(
    SOURCE 
        main.cpp
        driver.cpp)
        
add_executable(main ${SOURCE})

add_subdirectory(front-end)
add_subdirectory(visitor)

target_include_directories(
    main PRIVATE
        front-end 
        ${CMAKE_CURRENT_BINARY_DIR}/front-end
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(main front-end visitor)
target_link_libraries(main ${llvm_libs})
