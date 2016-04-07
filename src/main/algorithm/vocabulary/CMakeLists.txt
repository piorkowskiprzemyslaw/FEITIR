set(VOCABULARY_SOURCE_FILES
        DatabaseTranslator.cpp
        kmeans/KMeansVocabularyBuilder.cpp
        kmeans/KMeansConfig.cpp
        VocabularyConfig.h)

add_library(vocabulary STATIC ${VOCABULARY_SOURCE_FILES})

target_link_libraries(vocabulary database bsift ${OpenCV_LIBRARIES} ${Boost_LIBRARIES})