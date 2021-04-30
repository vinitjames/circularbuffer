cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "cmake in tests, project name ${PROJECT_NAME}" )

configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
			    RESULT_VARIABLE result
    			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download
				)
if(result)
	message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
			    RESULT_VARIABLE result
		  		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download
				)
				
if(result)
	message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
				 EXCLUDE_FROM_ALL)
				 
add_executable(int_buffer int_buffer.cpp)
target_link_libraries(int_buffer
					  circularbuffer
					  gtest_main
					  )
add_test(NAME test_int_buffer COMMAND int_buffer)

add_executable(string_buffer string_buffer.cpp)
target_link_libraries(string_buffer
					  circularbuffer
					  gtest_main
					  )
add_test(NAME test_string_buffer COMMAND string_buffer)


