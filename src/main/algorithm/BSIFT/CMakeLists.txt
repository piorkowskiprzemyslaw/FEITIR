set(BSIFT_SOURCE_FILES
        descriptor_median/DescriptorMedianBSIFTExtractor.cpp
        BSIFTDatabaseTranslator.h
        BSIFTExtractor.h
        ImageBSIFT.h)

add_library(bsift STATIC ${BSIFT_SOURCE_FILES})

target_link_libraries(bsift database util vocabulary ${OpenCV_LIBRARIES} ${Boost_LIBRARIES})