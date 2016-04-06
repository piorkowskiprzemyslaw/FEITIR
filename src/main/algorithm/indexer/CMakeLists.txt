set(INDEXER_SOURCE_FILES
        inverted_file/InvertedFileIndexer.cpp
        inverted_file/IFConfig.cpp)

add_library(indexer STATIC ${INDEXER_SOURCE_FILES})

target_link_libraries(indexer database ${OpenCV_LIBRARIES})