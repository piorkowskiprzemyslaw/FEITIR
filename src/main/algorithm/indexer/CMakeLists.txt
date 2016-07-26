set(INDEXER_SOURCE_FILES
        Indexer.h
        IndexerConfig.h
        inverted_file/InvertedFileIndexer.cpp
        inverted_file/IFConfig.cpp
        binary_inverted_file/BIFConfig.cpp
        binary_inverted_file/BinaryInvertedFileIndexer.h
        supporting_words_inverted_file/SupportingWordsInvertedFileIndexer.h
        supporting_words_inverted_file/SWIFConfig.h
        supporting_words_inverted_file/SWIFConfig.cpp
        cross_indexer/CrossConfig.h
        cross_indexer/CrossConfig.cpp
        cross_indexer/CrossIndexer.cpp
        cross_indexer/CrossIndexer.h)

add_library(indexer STATIC ${INDEXER_SOURCE_FILES})

target_link_libraries(indexer database ${OpenCV_LIBRARIES})