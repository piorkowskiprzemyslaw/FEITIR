set(BSIFT_SOURCE_FILES BSIFTExtractor.cpp
        ImageBSIFT.cpp
        DescriptorMedianBSIFTExtractor.cpp)

add_library(bsift STATIC ${BSIFT_SOURCE_FILES})

target_link_libraries(bsift database util ${OpenCV_LIBRARIES} ${Boost_LIBRARIES})