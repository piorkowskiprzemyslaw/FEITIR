set(BENCHMARK_SOURCE_FILES
        BenchmarkScenarioRunner.cpp
        BenchmarkScenarioRunner.h
        BenchmarkScenario.cpp
        BenchmarkScenario.h
        benchmark_description/BSIFTMethodDescription.cpp
        benchmark_description/BSIFTMethodDescription.h
        benchmark_description/BSIFTBenchmarkDescription.cpp
        benchmark_description/BSIFTBenchmarkDescription.h
        benchmark_description/IndexerBenchmarkDescription.cpp
        benchmark_description/IndexerBenchmarkDescription.h)

set(COMPARISON_ARRAY_N_PARAM 384)
set(VORONOI_POSITION_N_PARAM 64)
set(LSH_N_PARAM 128)

configure_file(benchmark_config.h.in ${CMAKE_BINARY_DIR}/generated/benchmark_config.h)
include_directories(${CMAKE_BINARY_DIR}/generated/)

add_library(benchmark STATIC ${BENCHMARK_SOURCE_FILES})

target_link_libraries(benchmark ${Boost_LIBRARIES} util)