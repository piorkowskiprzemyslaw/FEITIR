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

set(VOCABULARY_LIBRARIES database bsift ${OpenCV_LIBRARIES} ${Boost_LIBRARIES})

if ("${CMAKE_SYSTEM}" MATCHES "Linux")
    find_package(Threads)
    set(VOCABULARY_LIBRARIES ${VOCABULARY_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
endif()

target_link_libraries(vocabulary ${VOCABULARY_LIBRARIES})