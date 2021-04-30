set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(sample_int_buffer sample_int_buffer.cpp)
target_link_libraries(sample_int_buffer
					  PRIVATE
					  circularbuffer
					  )

add_executable(sample_string_buffer sample_string_buffer.cpp)
target_link_libraries(sample_string_buffer
					  PRIVATE
					  circularbuffer
					  )

add_executable(sample_custom_buffer sample_custom_buffer.cpp)
target_link_libraries(sample_custom_buffer
					  PRIVATE
					  circularbuffer
					  )
