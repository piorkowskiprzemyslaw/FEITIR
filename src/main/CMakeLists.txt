set(MAIN_SOURCE_FILES main.cpp)
include_directories(${CMAKE_BINARY_DIR}/generated/)

add_subdirectory(algorithm)
add_subdirectory(benchmark)
add_subdirectory(database)
add_subdirectory(util)
add_subdirectory(retrieval)

add_executable(FEITIR ${MAIN_SOURCE_FILES})
target_link_libraries(FEITIR database bsift indexer vocabulary benchmark retrieval benchmark_description)