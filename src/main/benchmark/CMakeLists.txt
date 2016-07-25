set(BENCHMARK_SOURCE_FILES
        BenchmarkScenarioRunner.cpp
        BenchmarkScenarioRunner.h
        BenchmarkScenario.cpp
        BenchmarkScenario.h
        benchmark_description/bsift/BSIFTMethodDescription.cpp
        benchmark_description/bsift/BSIFTMethodDescription.h
        benchmark_description/bsift/BSIFTBenchmarkDescription.cpp
        benchmark_description/bsift/BSIFTBenchmarkDescription.h
        benchmark_description/indexer/IndexerBenchmark.cpp
        benchmark_description/indexer/IndexerBenchmark.h
        benchmark_description/indexer/IndexerMethod.cpp
        benchmark_description/indexer/IndexerBenchmark.h
        benchmark_description/indexer/BSIFTAlgorithm.h
        benchmark_description/indexer/BSIFTAlgorithm.cpp)

add_library(benchmark STATIC ${BENCHMARK_SOURCE_FILES})

target_link_libraries(benchmark ${Boost_LIBRARIES} ${OpenCV_LIBRARIES} util)