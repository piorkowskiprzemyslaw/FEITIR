add_executable(DatabaseFactory_TEST DatabaseFactory_TEST.cpp)

target_link_libraries(DatabaseFactory_TEST ${Boost_LIBRARIES} database)

add_test(src/test/database/DatabaseFactory_TEST DatabaseFactory_TEST)

add_subdirectory(category)
add_subdirectory(image)