add_executable(DescriptorMedianBSIFT_TEST DescriptorMedianBSIFT_TEST.cpp)

target_link_libraries(DescriptorMedianBSIFT_TEST bsift
        image
        ${Boost_LIBRARIES}
        ${OpenCV_LIBRARIES})

add_test(src/test/algorithm/vocabularyMatrix/DescriptorMedianBSIFT_TEST DescriptorMedianBSIFT_TEST)