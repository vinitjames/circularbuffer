#include "circular_buffer.h"
#include <iostream>
#include <string.h>
#include "gtest/gtest.h"

#define TEST_BUFFER_SIZE 100

class CircularBufferTest : public ::testing::Test{
	
protected:
	
	CircularBuffer<std::string> test{TEST_BUFFER_SIZE};
	
};

TEST_F(CircularBufferTest, CapacityTest){
	EXPECT_EQ(TEST_BUFFER_SIZE, test.capacity());
	EXPECT_FALSE(test.capacity() == 0);
}

TEST_F(CircularBufferTest, EmptyTest){
	EXPECT_TRUE(test.empty());
	test.push_back("string 1");
	test.push_back("string 2");
	EXPECT_FALSE(test.empty());
	test.pop_front();
	test.pop_front();
	EXPECT_TRUE(test.empty());
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		test.push_back("string" + std::to_string(i));
	EXPECT_FALSE(test.empty());
	
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		test.pop_front();
	EXPECT_TRUE(test.empty());
}

