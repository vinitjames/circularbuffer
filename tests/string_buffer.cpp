#include "circular_buffer.h"
#include <iostream>
#include <string.h>
#include <utility>
#include "gtest/gtest.h"

#define TEST_BUFFER_SIZE 100

class CircularBufferTest : public ::testing::Test{
	
protected:
	
	CircularBuffer<std::string> test_buff{TEST_BUFFER_SIZE};
	
};

TEST_F(CircularBufferTest, CapacityTest){
	EXPECT_EQ(TEST_BUFFER_SIZE, test_buff.capacity());
	EXPECT_FALSE(test_buff.capacity() == 0);
}

TEST_F(CircularBufferTest, EmptyTest){
	EXPECT_TRUE(test_buff.empty());
	test_buff.push_back("string 1");
	test_buff.push_back("string 2");
	EXPECT_FALSE(test_buff.empty());
	test_buff.pop_front();
	test_buff.pop_front();
	EXPECT_TRUE(test_buff.empty());
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		test_buff.push_back("string" + std::to_string(i));
	EXPECT_FALSE(test_buff.empty());
	
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		test_buff.pop_front();
	EXPECT_TRUE(test_buff.empty());
}

TEST_F(CircularBufferTest, SizeTest){
	EXPECT_TRUE(test_buff.empty());
	test_buff.push_back("string 1");
	test_buff.push_back("string 2");
	EXPECT_EQ(test_buff.size(), 2);
	test_buff.pop_front();
	test_buff.pop_front();
	EXPECT_EQ(test_buff.size(), 0);
	// create full buffer
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		test_buff.push_back("string" + std::to_string(i));
	EXPECT_EQ(test_buff.size(), TEST_BUFFER_SIZE);
	//add more entries to overwrite front
	test_buff.push_back("string" + std::to_string(TEST_BUFFER_SIZE + 1));
	test_buff.push_back("string" + std::to_string(TEST_BUFFER_SIZE + 2));
	EXPECT_EQ(test_buff.size(), TEST_BUFFER_SIZE);
	//manually empty buffer
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		test_buff.pop_front();
	EXPECT_EQ(test_buff.size(), 0);
}

TEST_F(CircularBufferTest, ClearTest){
	EXPECT_TRUE(test_buff.empty());
	// create full buffer
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		test_buff.push_back("string" + std::to_string(i));	
	EXPECT_FALSE(test_buff.empty());
	//add more entries to overwrite front
	test_buff.push_back("string" + std::to_string(TEST_BUFFER_SIZE + 1));	
	EXPECT_FALSE(test_buff.empty());
	//clear buffer
	test_buff.clear();
	//check size and empty flags after clearing
	EXPECT_TRUE(test_buff.empty());
	EXPECT_EQ(test_buff.size(), 0);

}

TEST_F(CircularBufferTest, FullTest){
	EXPECT_FALSE(test_buff.full());
	// create full buffer
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		test_buff.push_back("string" + std::to_string(i));	
	EXPECT_TRUE(test_buff.full());
	//add more entries to overwrite front
	test_buff.push_back("string" + std::to_string(TEST_BUFFER_SIZE + 1));	
	EXPECT_TRUE(test_buff.full());
	//remove front element
	test_buff.pop_front();
	EXPECT_FALSE(test_buff.full());
	//add one elememt to make the buffer full
	test_buff.push_back("string" + std::to_string(TEST_BUFFER_SIZE + 2));		
	EXPECT_TRUE(test_buff.full());
}


TEST_F(CircularBufferTest, PushBackTest){
	// push back individual elements
	test_buff.push_back("string1");	
	EXPECT_EQ(test_buff.size(), 1);
	test_buff.push_back("string2");	
	EXPECT_EQ(test_buff.size(), 2);
	//create full buffer
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		test_buff.push_back("string" + std::to_string(i));
	
	//test move semantics in push_back
	std::string string_to_move{"This string is moved"};
	test_buff.push_back(std::move(string_to_move));	
	EXPECT_TRUE(string_to_move.empty());
	//create full buffer
	for(int i=0; i<TEST_BUFFER_SIZE; i++){
		std::string temp_string{"This string is moved"};
		test_buff.push_back(std::move(temp_string));
		EXPECT_TRUE(temp_string.empty());
	}	
	EXPECT_TRUE(test_buff.full());
	EXPECT_EQ(test_buff.size(), TEST_BUFFER_SIZE);
	
}


TEST_F(CircularBufferTest, PopFrontTest){
	// push back & pop individual elements
	test_buff.push_back("string1");
	EXPECT_EQ(test_buff.size(), 1);
	test_buff.pop_front();	
	EXPECT_EQ(test_buff.size(), 0);
	
	//create full buffer
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		test_buff.push_back("string" + std::to_string(i));
	//pop all elements
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		test_buff.pop_front();
	EXPECT_TRUE(test_buff.empty());
	EXPECT_EQ(test_buff.size(), 0);
	//try pop on empty buffer
	try {
		test_buff.pop_front();
		FAIL() << "Expected std::length_error";
	}
	catch(const std::length_error& err){
		EXPECT_EQ(err.what(), std::string("pop_front called on empty buffer"));
	}
}


TEST_F(CircularBufferTest, FrontTest){
	// push back & front for  individual elements
	test_buff.push_back("string1");
	test_buff.push_back("string2");
	EXPECT_EQ(test_buff.size(), 2);
	EXPECT_EQ(test_buff.front(), "string1");
	test_buff.front() = "string2";
	EXPECT_EQ(test_buff.front(), "string2");
	//create full buffer
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		test_buff.push_back("string" + std::to_string(i));
	EXPECT_EQ(test_buff.front(), "string0");
	//empty the buffer
	test_buff.clear();
	EXPECT_EQ(test_buff.size(), 0);
	//calling front on empty buffer raises exception
	try {
		test_buff.front() = "string0";
		FAIL() << "Expected std::length_error";
	}
	catch(const std::length_error& err){
		EXPECT_EQ(err.what(), std::string("front function called on empty buffer"));
	}
}

TEST_F(CircularBufferTest, BackTest){
	// push back & front for  individual elements
	test_buff.push_back("string1");
	test_buff.push_back("string2");
	EXPECT_EQ(test_buff.size(), 2);
	EXPECT_EQ(test_buff.back(), "string2");
	test_buff.back() = "string1";
	EXPECT_EQ(test_buff.back(), "string1");
	//create full buffer
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		test_buff.push_back("string" + std::to_string(i));
	EXPECT_EQ(test_buff.back(), "string99");
	//empty the buffer
	test_buff.clear();
	EXPECT_EQ(test_buff.size(), 0);
	//calling back on empty buffer raises exception
	try {
		test_buff.back() = "string0";
		FAIL() << "Expected std::length_error";
	}
	catch(const std::length_error& err){
		EXPECT_EQ(err.what(), std::string("back function called on empty buffer"));
	}
 
}










