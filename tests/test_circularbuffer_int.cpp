#include "circular_buffer.h"
#include <iostream>
#include <string.h>
#include "gtest/gtest.h"


class CircularBufferTest : public ::testing::Test{
	
protected:
	
	CircularBuffer<int> test{5};
	
};

TEST_F(CircularBufferTest, CapacityTest){
	EXPECT_EQ(5, test.capacity());
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
	test.push_back(348789);
	test.push_back(34824);
	test.push_back(234892);
	test.push_back(100929);
	test.push_back(4878872);
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


int main(int argc, char *argv[])
{   
		
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
