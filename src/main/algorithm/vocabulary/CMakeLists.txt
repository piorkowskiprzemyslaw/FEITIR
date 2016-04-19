set(VOCABULARY_SOURCE_FILES
        DatabaseTranslator.cpp
        DatabaseTranslator.h
        VocabularyConfig.h
        VocabularyBuilder.h
        kmeans/KMeansVocabularyBuilder.cpp
        kmeans/KMeansVocabularyBuilder.h
        kmeans/KMeansConfig.cpp
        kmeans/KMeansConfig.h
        hierarchical_kmeans/HKMeansConfig.cpp
        hierarchical_kmeans/HKMeansConfig.h
        hierarchical_kmeans/HKMeansVocabularyBuilder.cpp
        hierarchical_kmeans/HKMeansVocabularyBuilder.h)

add_library(vocabulary STATIC ${VOCABULARY_SOURCE_FILES})

target_link_libraries(vocabulary database bsift ${OpenCV_LIBRARIES} ${Boost_LIBRARIES})