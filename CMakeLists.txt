cmake_minimum_required(VERSION 3.2)
project(FEITIR)

set(FEITIR_MAJOR_VERSION 0)
set(FEITIR_MINOR_VERSION 1)
set(FEITIR_PATCH_VERSION 0)
set(FEITIR_VERSION ${FEITIR_MAJOR_VERSION}.${FEITIR_MINOR_VERSION}.${FEITIR_PATCH_VERSION})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

find_package(Boost 1.5.90 REQUIRED unit_test_framework system filesystem program_options log)
find_package(OpenCV 3.1.0 REQUIRED)

set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${Boost_INCLUDE_DIR}
                    ${OpenCV_INCLUDE_DIR})

if (${TRAVIS})
    include_directories(${TRAVIS_EIGEN_DIRECTORY})
endif(${TRAVIS})

enable_testing()

add_subdirectory(src)

configure_file(benchmarkScenario.json.in ${PROJECT_SOURCE_DIR}/benchmarkScenario.json)