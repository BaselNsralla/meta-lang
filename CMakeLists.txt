cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_COMPILER /usr/bin/g++-9)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-fconcepts")
project(meta-lang)

file(GLOB SOURCES
    src/*.cpp
)

add_executable(meta ${SOURCES})

