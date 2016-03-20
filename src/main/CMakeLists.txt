set(MAIN_SOURCE_FILES main.cpp)

add_subdirectory(algorithm)
add_subdirectory(database)
add_subdirectory(util)

add_executable(FEITIR ${MAIN_SOURCE_FILES})
target_link_libraries(FEITIR database algorithm)