cmake_minimum_required(VERSION 3.16)

project(lab1)

enable_testing()

add_library(lab1_library 
    src/barrel/barrel.cpp
    src/matrix/matrix.cpp
    src/mystring/mystring.cpp
    src/rect/rect.cpp
    src/textwrapper/textwrapper.cpp
)

target_include_directories(lab1_library PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/barrel
    ${CMAKE_CURRENT_SOURCE_DIR}/src/matrix
    ${CMAKE_CURRENT_SOURCE_DIR}/src/mystring
    ${CMAKE_CURRENT_SOURCE_DIR}/src/rect
    ${CMAKE_CURRENT_SOURCE_DIR}/src/textwrapper
)

add_executable(main_app
    src/main.cpp
)

target_link_libraries(main_app PRIVATE lab1_library)

add_subdirectory(tests)