set(DATABASE_SOURCE_FILES
        Database.cpp
        DatabaseFactory.cpp)

add_library(database STATIC ${DATABASE_SOURCE_FILES})

add_subdirectory(category)
add_subdirectory(image)

target_link_libraries(database category image util)