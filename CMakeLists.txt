cmake_minimum_required(VERSION 3.3)
project(FEITIR)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

enable_testing()

add_subdirectory(src)