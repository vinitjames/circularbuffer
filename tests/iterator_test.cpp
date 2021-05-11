#include "circular_buffer.h"
#include <algorithm>
#include <string>
#include <utility>
#include "gtest/gtest.h"

#define TEST_BUFFER_SIZE 100
#define REDUCE_SIZE 50

class CircularBufferTest : public ::testing::Test{
	
protected:
	
	CircularBuffer<std::string> test_str_buff{TEST_BUFFER_SIZE};
	CircularBuffer<int> test_int_buff{TEST_BUFFER_SIZE};
};

TEST_F(CircularBufferTest, IteratorBasedLoopTest){	
	//create full buffer
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		test_str_buff.push_back("string" + std::to_string(i));
    int i = 0;
	for(auto it = test_str_buff.begin(); it!=test_str_buff.end(); it++)
		EXPECT_EQ(*it, "string" + std::to_string(i++));
	//partially fill buffers
	test_str_buff.clear();
	for(int i=0; i<TEST_BUFFER_SIZE/2; i++)
		test_str_buff.push_back("string" + std::to_string(i));
	//test begin and end on partially full buffer
	i = 0;
	for(auto it = test_str_buff.begin(); it!=test_str_buff.end(); it++)
		EXPECT_EQ(*it, "string" + std::to_string(i++));
	//test size with increment variable
	EXPECT_EQ(i, TEST_BUFFER_SIZE/2);
}

TEST_F(CircularBufferTest, ReverseIteratorBasedLoopTest){	
	//create full buffer
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		test_str_buff.push_back("string" + std::to_string(i));
    int i = 99;
	for(auto it = test_str_buff.rbegin(); it!=test_str_buff.rend(); it++)
		EXPECT_EQ(*it, "string" + std::to_string(i--));
	//partially fill buffers
	test_str_buff.clear();
	for(int i=0; i<TEST_BUFFER_SIZE/2; i++)
		test_str_buff.push_back("string" + std::to_string(i));
	//test begin and end on partially full buffer
	i = TEST_BUFFER_SIZE/2 - 1;
	for(auto it = test_str_buff.rbegin(); it!=test_str_buff.rend(); it++)
		EXPECT_EQ(*it, "string" + std::to_string(i--));
}

TEST_F(CircularBufferTest, RangeBasedLoopTest){	
	//create full buffer
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		test_str_buff.push_back("string" + std::to_string(i));
	int i = 0;
	//copied elements 
    for(auto buff_elem : test_str_buff)
		EXPECT_EQ(buff_elem, "string" + std::to_string(i++));
	//auto reference
	i = 0;
    for(auto& buff_elem : test_str_buff)
		EXPECT_EQ(buff_elem, "string" + std::to_string(i++));	
	//auto const reference
	i = 0;
    for(const auto& buff_elem : test_str_buff)
		EXPECT_EQ(buff_elem, "string" + std::to_string(i++));
	//check iterators after modifications
	for(int i = 0; i<REDUCE_SIZE; i++)
		test_str_buff.pop_front();
	i = TEST_BUFFER_SIZE - REDUCE_SIZE;
    for(const auto& buff_elem : test_str_buff)
		EXPECT_EQ(buff_elem, "string" + std::to_string(i++));
}

TEST_F(CircularBufferTest, FindTest){	
	//create full buffer
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		test_str_buff.push_back("string" + std::to_string(i));
	auto result = std::find(test_str_buff.cbegin(), test_str_buff.cend(), "string50");
	EXPECT_EQ(*result, "string50");
	result  = std::find(test_str_buff.cbegin(), test_str_buff.cend(), "string100");
	EXPECT_EQ(result, test_str_buff.cend());
	//partial buffer search
	result  = std::find(test_str_buff.cbegin(), test_str_buff.cbegin() + 50, "string30");
	EXPECT_EQ(*result, "string30");
	result  = std::find(test_str_buff.cbegin(), test_str_buff.cbegin() + 50, "string51");
	EXPECT_EQ(result, test_str_buff.cbegin() + 50);
}

TEST_F(CircularBufferTest, ForEachTest){	
	//create full buffer
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		test_str_buff.push_back("string" + std::to_string(i));
	std::for_each(test_str_buff.begin(), test_str_buff.end(), [](std::string& elem){
		elem = elem + "modified";});
	int i=0;
	for(const auto& elem: test_str_buff)
		EXPECT_EQ(elem, "string" + std::to_string(i++) + "modified");	
}

TEST_F(CircularBufferTest, SortTest){	
	//create full buffer
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		test_int_buff.push_back(i);
	std::sort(test_int_buff.begin(), test_int_buff.end(), std::greater<int>());
	int i = 99;
	for(const auto& elem: test_int_buff)
		EXPECT_EQ(elem, i--);
}

TEST_F(CircularBufferTest, CopyUsingIterator){	
	//create full buffer
	for(int i=0; i<TEST_BUFFER_SIZE; i++)
		test_str_buff.push_back("string" + std::to_string(i));
	std::vector<std::string> buffer_copy;
	buffer_copy.reserve(test_str_buff.size());
	std::copy(test_str_buff.begin(), test_str_buff.end(), std::back_inserter(buffer_copy));
	int i = 0;
	for(const auto& elem: test_str_buff)
		EXPECT_EQ(elem, buffer_copy[i++]);
	buffer_copy.clear();
	//remove elements from  buffer
	for(int i=0; i<REDUCE_SIZE; i++)
		test_str_buff.pop_front();
	std::copy(test_str_buff.begin(), test_str_buff.end(), std::back_inserter(buffer_copy));
	i = 0;
	for(const auto& elem: test_str_buff)
		EXPECT_EQ(elem, buffer_copy[i++]);
	
}



