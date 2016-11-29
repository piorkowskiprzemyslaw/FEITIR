configure_file(test_global.h.in ${CMAKE_BINARY_DIR}/generated/test_global.h)
configure_file(resources/util/JSON/sample1.json.in ${PROJECT_SOURCE_DIR}/src/test/resources/util/JSON/sample1.json)
configure_file(resources/util/JSON/sample2.json.in ${PROJECT_SOURCE_DIR}/src/test/resources/util/JSON/sample2.json)
include_directories(${CMAKE_BINARY_DIR}/generated/)

add_subdirectory(database)
add_subdirectory(algorithm)
add_subdirectory(util)