cmake_minimum_required(VERSION 3.13)

message(STATUS "cmake in tests, project name ${PROJECT_NAME}" )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(test_circularbuffer_int test_circularbuffer_int.cpp)
target_link_libraries(test_circularbuffer_int
					  PRIVATE
					  circularbuffer
					  /usr/local/lib/libgtest.a
					  pthread
					  )
