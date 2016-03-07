add_executable(ImageFactory_TEST ImageFactory_TEST.cpp)

target_link_libraries(ImageFactory_TEST ${Boost_LIBRARIES} ${OpenCV_LIBRARIES} image)

add_test(src/test/image/ImageFactory_TEST ImageFactory_TEST)