set(BENCHMARK_SOURCE_FILES
        BenchmarkScenarioRunner.cpp
        BenchmarkScenarioRunner.h
        BenchmarkScenario.cpp
        BenchmarkScenario.h
        benchmark_description/bsift/BSIFTMethod.cpp
        benchmark_description/bsift/BSIFTMethod.h
        benchmark_description/bsift/BSIFTBenchmark.cpp
        benchmark_description/bsift/BSIFTBenchmark.h
        benchmark_description/indexer/IndexerBenchmark.cpp
        benchmark_description/indexer/IndexerBenchmark.h
        benchmark_description/indexer/IndexerMethod.cpp
        benchmark_description/indexer/IndexerBenchmark.h
        benchmark_description/bsift/BSIFTAlgorithm.h
        benchmark_description/bsift/BSIFTAlgorithm.cpp)

add_library(benchmark STATIC ${BENCHMARK_SOURCE_FILES})

target_link_libraries(benchmark ${Boost_LIBRARIES} ${OpenCV_LIBRARIES} util)