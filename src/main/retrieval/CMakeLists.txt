set(RETRIEVAL_SOURCE_FILES
        BagOfWords.cpp
        BagOfWords.h)

add_library(retrieval STATIC ${RETRIEVAL_SOURCE_FILES})

target_link_libraries(retrieval bsift indexer vocabulary category image util benchmark_description)