set(VOCABULARY_SOURCE_FILES
        KMeansVocabulary.cpp)

add_library(vocabulary STATIC ${VOCABULARY_SOURCE_FILES})

target_link_libraries(vocabulary ${OpenCV_LIBRARIES} ${Boost_LIBRARIES})