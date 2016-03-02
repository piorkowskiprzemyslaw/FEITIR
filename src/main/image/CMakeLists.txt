set(IMAGE_SOURCE_FILES
        Image.cpp
        ImageFactory.cpp)

add_library(image STATIC ${IMAGE_SOURCE_FILES})

target_link_libraries(image ${OpenCV_LIBRARIES})
