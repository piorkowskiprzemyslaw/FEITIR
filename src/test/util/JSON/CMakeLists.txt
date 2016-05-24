add_executable(JSONObject_TEST JSONObject_TEST.cpp)

target_link_libraries(JSONObject_TEST util benchmark ${Boost_LIBRARIES})

add_test(src/test/util/JSON/JSONObject_TEST JSONObject_TEST)