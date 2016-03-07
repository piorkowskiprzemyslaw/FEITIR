add_subdirectory(image)

add_executable(main_TEST main_TEST.cpp)
target_link_libraries(main_TEST ${Boost_LIBRARIES})
add_test(src/test/main_TEST main_TEST)