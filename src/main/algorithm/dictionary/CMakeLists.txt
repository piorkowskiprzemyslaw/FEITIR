set(DICTIONARY_SOURCE_FILES
        KMeansDictionary.cpp)

add_library(dictionary STATIC ${DICTIONARY_SOURCE_FILES})

target_link_libraries(dictionary ${OpenCV_LIBRARIES})