find_package(OpenCV 3.1.0 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIR})

add_executable(ImageFactory_TEST ImageFactory_TEST.cpp)

target_link_libraries(ImageFactory_TEST ${Boost_LIBRARIES} image ${OpenCV_LIBRARIES})

add_test(src/test/image/ImageFactory_TEST ImageFactory_TEST)