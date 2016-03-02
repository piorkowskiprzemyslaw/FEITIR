find_package(OpenCV 3.1.0 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIR})

set(MAIN_SOURCE_FILES main.cpp)

add_subdirectory(image)

add_executable(FEITIR ${MAIN_SOURCE_FILES})
target_link_libraries(FEITIR image)