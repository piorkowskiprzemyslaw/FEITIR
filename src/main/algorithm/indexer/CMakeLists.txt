set(INDEXER_SOURCE_FILES
        inverted_file/InvertedFileIndexer.cpp
        inverted_file/IFConfig.cpp
        binary_inverted_file/BIFConfig.cpp
        Indexer.h
        binary_inverted_file/BinaryInvertedFileIndexer.h
        supporting_words_inverted_file/SupportingWordsInvertedFileIndexer.h
        supporting_words_inverted_file/SWIFConfig.h
        supporting_words_inverted_file/SWIFConfig.cpp)

add_library(indexer STATIC ${INDEXER_SOURCE_FILES})

target_link_libraries(indexer database ${OpenCV_LIBRARIES})