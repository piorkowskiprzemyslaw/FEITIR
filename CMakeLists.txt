cmake_minimum_required(VERSION 3.3)
project(FEITIR)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

find_package(Boost 1.5.90 REQUIRED unit_test_framework system filesystem)
find_package(OpenCV 3.1.0 REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${Boost_INCLUDE_DIR}
                    ${OpenCV_INCLUDE_DIR})

enable_testing()

add_subdirectory(src)