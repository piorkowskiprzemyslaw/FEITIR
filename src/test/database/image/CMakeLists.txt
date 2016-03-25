add_executable(ImageFactory_TEST ImageFactory_TEST.cpp)

target_link_libraries(ImageFactory_TEST ${Boost_LIBRARIES} ${OpenCV_LIBRARIES} image vocabulary)

add_test(src/test/database/image/ImageFactory_TEST ImageFactory_TEST)