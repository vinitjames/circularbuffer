set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(sample_circularbuffer sample_circularbuffer.cpp)
target_link_libraries(sample_circularbuffer
					  PRIVATE
					  circularbuffer
					  )
