cmake_minimum_required(VERSION 3.0...3.27)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) # all builds will be here

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)