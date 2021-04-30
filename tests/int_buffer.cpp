#include "circular_buffer.h"
#include <iostream>
#include <string.h>
#include "gtest/gtest.h"

#define TEST_BUFFER_SIZE 100

class CircularBufferTest : public ::testing::Test{
	
protected:
	
	CircularBuffer<int> test{TEST_BUFFER_SIZE};
	
};

TEST_F(CircularBufferTest, CapacityTest){
	EXPECT_EQ(TEST_BUFFER_SIZE, test.capacity());
	EXPECT_FALSE(test.capacity() == 0);
}

TEST_F(CircularBufferTest, EmptyTest){
	EXPECT_TRUE(test.empty());
	test.push_back(10);
	test.push_back(5);
	EXPECT_FALSE(test.empty());
	test.pop_front();
	test.pop_front();
	EXPECT_TRUE(test.empty());
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		test.push_back(10);
	EXPECT_FALSE(test.empty());
	
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		test.pop_front();
	EXPECT_TRUE(test.empty());
}

TEST_F(CircularBufferTest, PushBackTest){
	EXPECT_TRUE(test.empty());
	test.push_back(1);
	test.push_back(2);
	EXPECT_EQ(1, test.front());
	EXPECT_EQ(2, test.back());
	test.pop_front();
	EXPECT_EQ(2, test.front());
	EXPECT_EQ(2, test.front());
	
}

TEST_F(CircularBufferTest, PopFrontTest){
	EXPECT_TRUE(test.empty());
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		test.push_back(10);
	EXPECT_TRUE(test.full());
	while(true){
		try{
			test.pop_front();
		}
		catch(std::exception& e){
			EXPECT_TRUE(test.empty());
			break;
		}
	}
		
}

TEST_F(CircularBufferTest, SizeTest){
	EXPECT_EQ(0, test.size());
	test.push_back(1);
	test.push_back(2);
	EXPECT_EQ(2, test.size());
	while(!test.full())
		test.push_back(1);
	EXPECT_EQ(test.size(), test.capacity());	
}

TEST_F(CircularBufferTest, PushAndPopTest){
	EXPECT_EQ(0, test.size());
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		test.push_back(i);
	EXPECT_EQ(TEST_BUFFER_SIZE, test.size());
	EXPECT_EQ(test.size(), test.capacity());

	for(int i=0; i<TEST_BUFFER_SIZE - 1; i++)
		test.pop_front();	
	EXPECT_EQ(1, test.size());
	EXPECT_EQ(TEST_BUFFER_SIZE, test.capacity());
	EXPECT_EQ(test.back(), test.front());
	EXPECT_EQ(TEST_BUFFER_SIZE - 1, test.front());
	
}



