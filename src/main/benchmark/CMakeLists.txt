set(BENCHMARK_SOURCE_FILES
        BenchmarkScenarioRunner.cpp
        BenchmarkScenarioRunner.h
        BenchmarkScenario.cpp
        BenchmarkScenario.h
        BenchmarkDescription.cpp
        BenchmarkDescription.h
        BenchmarkScenarioFactory.cpp
        BenchmarkScenarioFactory.h
        benchmark_description/BenchmarkDescriptionFactory.h
        benchmark_description/BenchmarkDescriptionFactory.cpp
        benchmark_description/BSIFTBenchmarkDescription.cpp
        benchmark_description/BSIFTBenchmarkDescription.h
        benchmark_description/IndexerBenchmarkDescription.cpp
        benchmark_description/IndexerBenchmarkDescription.h)

add_library(benchmark STATIC ${BENCHMARK_SOURCE_FILES})

target_link_libraries(benchmark ${Boost_LIBRARIES})