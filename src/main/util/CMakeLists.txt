set(UTIL_SOURCE_FILES
        Util.cpp
        Util.h
        eigenmvn.h)

add_library(util STATIC ${UTIL_SOURCE_FILES})

target_link_libraries(util ${Boost_LIBRARIES})