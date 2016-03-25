set(BSIFT_SOURCE_FILES )

add_library(bsift STATIC ${BSIFT_SOURCE_FILES})

target_link_libraries(bsfit ${OpenCV_LIBRARIES})