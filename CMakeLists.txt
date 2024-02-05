cmake_minimum_required(VERSION 3.0...3.27)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) # all builds will be here

project(compiller
        VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER g++)

add_subdirectory(src)