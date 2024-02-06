cmake_minimum_required(VERSION 3.0...3.27)

# project(compiller)

file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "*.h")

include_directories(${DIR_SOURCES})

add_executable(${PROJECT_NAME}
    ${SOURCES}
    )
