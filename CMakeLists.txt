cmake_minimum_required(VERSION 3.13)


cmake_policy(SET CMP0079 NEW)
project("circularbuffer")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE ${${PROJECT_NAME}_SOURCE_DIR})

add_subdirectory(tests)

