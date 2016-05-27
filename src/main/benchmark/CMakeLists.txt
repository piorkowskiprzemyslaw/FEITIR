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

add_library(benchmark STATIC ${BENCHMARK_SOURCE_FILES})

target_link_libraries(benchmark ${Boost_LIBRARIES} ${OpenCV_LIBRARIES} util)