cmake_minimum_required(VERSION 3.31)
project(UU)

set(CMAKE_CXX_STANDARD 23)

add_executable(UU
	execute/main.cpp
)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build-cmake)
set(CMAKE_CURRENT_BINARY_DIR ${CMAKE_SOURCE_DIR}/build-cmake)