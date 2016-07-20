add_subdirectory(JSON)

add_executable(Util_TEST Util_TEST.cpp)

target_link_libraries(Util_TEST util ${Boost_LIBRARIES})

add_test(src/test/util/Util_TEST Util_TEST)