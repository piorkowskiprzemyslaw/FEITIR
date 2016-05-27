configure_file(feitir_config.h.in ${CMAKE_BINARY_DIR}/generated/feitir_config.h)
set(UTIL_SOURCE_FILES
        Util.cpp
        Util.h
        eigenmvn.h
        JSON/JSONObject.cpp
        JSON/JSONObject.h)

add_library(util STATIC ${UTIL_SOURCE_FILES})

target_link_libraries(util ${Boost_LIBRARIES} ${OpenCV_LIBRARIES})