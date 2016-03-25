configure_file(test_config_global.h.in ${CMAKE_BINARY_DIR}/generated/test_config_global.h)
include_directories(${CMAKE_BINARY_DIR}/generated/)

add_subdirectory(database)
add_subdirectory(algorithm)

add_executable(main_TEST main_TEST.cpp)
target_link_libraries(main_TEST ${Boost_LIBRARIES})
add_test(src/test/main_TEST main_TEST)