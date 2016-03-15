add_executable(CategoryFactory_TEST CategoryFactory_TEST.cpp)

target_link_libraries(CategoryFactory_TEST ${Boost_LIBRARIES} ${OpenCV_LIBRARIES} category)

add_test(src/test/database/category/CategoryFactory_TEST CategoryFactory_TEST)