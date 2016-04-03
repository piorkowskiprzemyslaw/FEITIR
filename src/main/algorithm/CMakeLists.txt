set(ALGORITHM_SOURCE_FILES
        BagOfWords.cpp)

add_subdirectory(vocabulary)
add_subdirectory(BSIFT)

add_library(algorithm STATIC ${ALGORITHM_SOURCE_FILES})

target_link_libraries(algorithm ${OpenCV_LIBRARIES})