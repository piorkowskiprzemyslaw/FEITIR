set(BENCHMARK_SOURCE_FILES
        BenchmarkScenarioRunner.cpp
        BenchmarkScenarioRunner.h)

add_subdirectory(benchmark_description)

add_library(benchmark STATIC ${BENCHMARK_SOURCE_FILES})

target_link_libraries(benchmark ${Boost_LIBRARIES} ${OpenCV_LIBRARIES} benchmark_description)