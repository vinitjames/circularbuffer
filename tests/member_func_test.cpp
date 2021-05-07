#include "circular_buffer.h"
#include <string.h>
#include <utility>
#include "gtest/gtest.h"

#define TEST_BUFFER_SIZE 100
#define REDUCE_SIZE 100

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
	//fill buffer after clear
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		test_buff.push_back("string" + std::to_string(i));

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

TEST_F(CircularBufferTest, AtFunctionTest){
	// push back & at access for  individual elements
	test_buff.push_back("string1");
	test_buff.push_back("string2");
	EXPECT_EQ(test_buff.size(), 2);
	EXPECT_EQ(test_buff.at(0), "string1");
	EXPECT_EQ(test_buff.at(1), "string2");
	test_buff.at(0) = "string2";
	test_buff.at(1) = "string1";
	EXPECT_EQ(test_buff.at(0), "string2");
	EXPECT_EQ(test_buff.at(1), "string1");
	//create full buffer
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		test_buff.push_back("string" + std::to_string(i));
	//test at function for each element
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		EXPECT_EQ(test_buff.at(i), "string" + std::to_string(i));
	//test assignment with at function for each element
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		test_buff.at(i) = "test_string" ;
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		EXPECT_EQ(test_buff.at(i),"test_string");
	//test out of bounds
	try {
		test_buff.at(TEST_BUFFER_SIZE) = "test_string";
		FAIL() << "Expected std::out_of_range error";
	}
	catch(const std::out_of_range& err){
		EXPECT_EQ(err.what(), std::string("Index is out of Range of buffer size"));
	}
	//test out of size
	test_buff.pop_front();
	try {
		test_buff.at(TEST_BUFFER_SIZE - 1) = "test_string";
		FAIL() << "Expected std::out_of_range error";
	}
	catch(const std::out_of_range& err){
		EXPECT_EQ(err.what(), std::string("Index is out of Range of buffer size"));
	}
}

TEST_F(CircularBufferTest, AccessOperatorTest){
	// push back & [] access for  individual elements
	test_buff.push_back("string1");
	test_buff.push_back("string2");
	EXPECT_EQ(test_buff.size(), 2);
	EXPECT_EQ(test_buff[0], "string1");
	EXPECT_EQ(test_buff[1], "string2");
	test_buff[0] = "string2";
	test_buff[1] = "string1";
	EXPECT_EQ(test_buff[0], "string2");
	EXPECT_EQ(test_buff[1], "string1");
	//create full buffer
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		test_buff.push_back("string" + std::to_string(i));
	//test [] operator for each element
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		EXPECT_EQ(test_buff[i], "string" + std::to_string(i));
	//test assignment with [] operator for each element
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		test_buff[i] = "test_string" ;
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		EXPECT_EQ(test_buff[i],"test_string");
	//test out of bounds
	try {
		test_buff[TEST_BUFFER_SIZE] = "test_string";
		FAIL() << "Expected std::out_of_range error";
	}
	catch(const std::out_of_range& err){
		EXPECT_EQ(err.what(), std::string("Index is out of Range of buffer size"));
	}
	//test out of size
	test_buff.pop_front();
	try {
		test_buff[TEST_BUFFER_SIZE - 1] = "test_string";
		FAIL() << "Expected std::out_of_range error";
	}
	catch(const std::out_of_range& err){
		EXPECT_EQ(err.what(), std::string("Index is out of Range of buffer size"));
	}
}


TEST_F(CircularBufferTest, BeginIteratorTest){	
	//create full buffer
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		test_buff.push_back("string" + std::to_string(i));
    //test first element with iterator
	CircularBuffer<std::string>::iterator it = test_buff.begin();
	EXPECT_EQ(*it, "string0" );
	//access with begin iterator	
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		EXPECT_EQ(*(it++), "string" + std::to_string(i));

	//access with const begin iterator
	CircularBuffer<std::string>::const_iterator const_it = test_buff.begin(); 
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		EXPECT_EQ(*(const_it++), "string" + std::to_string(i));
	//test out of bounds
	try {
		*it = "test_string";
		FAIL() << "Expected std::out_of_range error";
	}
	catch(const std::out_of_range& err){
		EXPECT_EQ(err.what(), std::string("Index is out of Range of buffer size"));
	}

	try {
		std::string out_of_bound = *(const_it);
		FAIL() << "Expected std::out_of_range error";
	}
	catch(const std::out_of_range& err){
		EXPECT_EQ(err.what(), std::string("Index is out of Range of buffer size"));
	}
}

TEST_F(CircularBufferTest, RbeginIteratorTest){	
	//create full buffer
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		test_buff.push_back("string" + std::to_string(i));
    //test first element with iterator
	CircularBuffer<std::string>::iterator it = test_buff.rbegin();
	//access with rbegin iterator	
	for(int i=TEST_BUFFER_SIZE-1; i>=0; i--)
		EXPECT_EQ(*(it++), "string" + std::to_string(i));

	//access with const begin iterator
	CircularBuffer<std::string>::const_iterator const_it = test_buff.rbegin(); 
	for(int i=TEST_BUFFER_SIZE - 1; i>=0;  i--)
		EXPECT_EQ(*(const_it++), "string" + std::to_string(i));
	//test out of bounds
	try {
		*it = "test_string";
		FAIL() << "Expected std::out_of_range error";
	}
	catch(const std::out_of_range& err){
		EXPECT_EQ(err.what(), std::string("Index is out of Range of buffer size"));
	}

	try {
		std::string out_of_bound = *(const_it);
		FAIL() << "Expected std::out_of_range error";
	}
	catch(const std::out_of_range& err){
		EXPECT_EQ(err.what(), std::string("Index is out of Range of buffer size"));
		}
}

TEST_F(CircularBufferTest, CbeginIteratorTest){	
	//create full buffer
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		test_buff.push_back("string" + std::to_string(i));
    //test first element with iterator
	CircularBuffer<std::string>::const_iterator const_it = test_buff.cbegin();
	EXPECT_EQ(*const_it, "string0" );
	//access with begin iterator	
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		EXPECT_EQ(*(const_it++), "string" + std::to_string(i));
	
	try {
		std::string out_of_bound = *(const_it);
		FAIL() << "Expected std::out_of_range error";
	}
	catch(const std::out_of_range& err){
		EXPECT_EQ(err.what(), std::string("Index is out of Range of buffer size"));
	}
}


TEST_F(CircularBufferTest, EndIteratorTest){	
	//create full buffer
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		test_buff.push_back("string" + std::to_string(i));

	CircularBuffer<std::string>::iterator it = test_buff.end(); 
	//access with end iterator	
	for(int i = TEST_BUFFER_SIZE-1; i>=0; i--)
		EXPECT_EQ(*(--it), "string" + std::to_string(i));

	//access with const end iterator
	CircularBuffer<std::string>::const_iterator const_it = test_buff.end(); 
	for(int i = TEST_BUFFER_SIZE-1; i>=0; i--)
		EXPECT_EQ(*(--const_it), "string" + std::to_string(i));

	//test out of bounds
	try {
		*(--it) = "test_string";
		FAIL() << "Expected std::out_of_range error";
	}
	catch(const std::out_of_range& err){
		EXPECT_EQ(err.what(), std::string("Index is out of Range of buffer size"));
	}

	try {
		std::string out_of_bound = *(--const_it);
		FAIL() << "Expected std::out_of_range error";
	}
	catch(const std::out_of_range& err){
		EXPECT_EQ(err.what(), std::string("Index is out of Range of buffer size"));
	}
}

TEST_F(CircularBufferTest, RendIteratorTest){	
	//create full buffer
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		test_buff.push_back("string" + std::to_string(i));
    //test first element with iterator
	CircularBuffer<std::string>::iterator it = test_buff.rend() - 1;
	//access with rbegin iterator	
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		EXPECT_EQ(*(it--), "string" + std::to_string(i));

	//access with const begin iterator
	CircularBuffer<std::string>::const_iterator const_it = test_buff.rend() - 1; 
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		EXPECT_EQ(*(const_it--), "string" + std::to_string(i));
	//test out of bounds
	try {
		*it = "test_string";
		FAIL() << "Expected std::out_of_range error";
	}
	catch(const std::out_of_range& err){
		EXPECT_EQ(err.what(), std::string("Index is out of Range of buffer size"));
	}

	try {
		std::string out_of_bound = *(const_it);
		FAIL() << "Expected std::out_of_range error";
	}
	catch(const std::out_of_range& err){
		EXPECT_EQ(err.what(), std::string("Index is out of Range of buffer size"));
		}
}


TEST_F(CircularBufferTest, CendIteratorTest){	
	//create full buffer
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		test_buff.push_back("string" + std::to_string(i));

	CircularBuffer<std::string>::const_iterator const_it = test_buff.cend(); 
	//access with end iterator	
	for(int i = TEST_BUFFER_SIZE-1; i>=0; i--)
		EXPECT_EQ(*(--const_it), "string" + std::to_string(i));

	try {
		std::string out_of_bound = *(--const_it);
		FAIL() << "Expected std::out_of_range error";
	}
	catch(const std::out_of_range& err){
		EXPECT_EQ(err.what(), std::string("Index is out of Range of buffer size"));
	}	
}





















