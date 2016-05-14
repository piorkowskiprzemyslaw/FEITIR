set(BSIFT_SOURCE_FILES
        descriptor_median/DescriptorMedianBSIFTExtractor.cpp
        descriptor_median/DescriptorMedianBSIFTExtractor.h
        comparasion_array/ComparasionArrayBSIFTExtractor.h
        descriptor_position_median/DescriptorPositionMedianBSIFTExtractor.cpp
        descriptor_position_median/DescriptorPositionMedianBSIFTExtractor.h
        locality_sensitive_hashing/LocalitySensitiveHashingBSIFTExtractor.h
        vectors_compare/VectorsCompareBSIFTExtractor.cpp
        vectors_compare/VectorsCompareBSIFTExtractor.h
        BSIFTDatabaseTranslator.h
        BSIFTExtractor.h
        ImageBSIFT.h)

add_library(bsift STATIC ${BSIFT_SOURCE_FILES})

target_link_libraries(bsift database util vocabulary ${OpenCV_LIBRARIES} ${Boost_LIBRARIES})