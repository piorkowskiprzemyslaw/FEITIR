find_package(Boost 1.5.90 REQUIRED unit_test_framework)
include_directories(${Boost_INCLUDE_DIR})

add_subdirectory(main)
add_subdirectory(test)