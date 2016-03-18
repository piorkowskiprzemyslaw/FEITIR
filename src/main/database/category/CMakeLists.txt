set(CATEGORY_SOURCE_FILES
        Category.cpp
        CategoryFactory.cpp)

add_library(category STATIC ${CATEGORY_SOURCE_FILES})
target_link_libraries(category image util ${Boost_LIBRARIES})