set(BENCHMARK_DESCRIPTION_SOURCE_FILES
        BenchmarkScenario.cpp
        BenchmarkScenario.h
        bsift/BSIFTMethod.cpp
        bsift/BSIFTMethod.h
        bsift/BSIFTBenchmark.cpp
        bsift/BSIFTBenchmark.h
        indexer/IndexerBenchmark.cpp
        indexer/IndexerBenchmark.h
        indexer/IndexerMethod.cpp
        indexer/IndexerBenchmark.h
        bsift/BSIFTAlgorithm.h
        bsift/BSIFTAlgorithm.cpp
        retrieval/RetrievalBenchmark.cpp
        retrieval/RetrievalBenchmark.h)

add_library(benchmark_description STATIC ${BENCHMARK_DESCRIPTION_SOURCE_FILES})

target_link_libraries(benchmark_description bsift indexer vocabulary category image database util)