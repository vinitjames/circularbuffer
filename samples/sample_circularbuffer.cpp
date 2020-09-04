#include "circular_buffer.h"
#include <iostream>
#include <string.h>
#include "gtest/gtest.h"

#include "circular_buffer.h"
#include <iostream>
#include <string.h>

struct test_struct{
	static int count ;
	char* bytes =nullptr; 
	test_struct(){
		bytes = (char*)malloc(100);
		std::cout<<"constructing test_struct: "<<count++<<"\n";
	}
	
	test_struct(const test_struct& other){
		bytes = (char*)malloc(100);
		memcpy(bytes, other.bytes,100);
		std::cout<<"copy constructor called for test_struct \n";
	}
	
	test_struct& operator=(const test_struct& other){
		bytes = (char*)malloc(100);
		memcpy(bytes, other.bytes,100);
		std::cout<<"assignment operator called for test_struct \n";
		return *this;
	}
	
	~test_struct(){
		free(bytes);
	}

	friend std::ostream& operator<<(std::ostream& os, const test_struct& ts){
		return os<<"\ntest";
	}
	

};


int test_struct::count =0;
int main(int argc, char *argv[])
{   
	
    CircularBuffer<int> test{5};
	//std::cout<<"size of data "<<sizeof(data[1].bytes)<<"\n";
	std::cout<<"length of buffer "<<test.size()<<"\n";
	std::cout<<"size of buffer in bytes "<<test.buffer_size()<<"\n";
	std::cout<<"Max capacity  of buffer "<<test.capacity()<<"\n";
	std::cout<<"Checking is buffer empty function "<<test.empty()<<"\n";
	std::cout<<"Pushing back  data in bufffer \n";
	test.push_back(5);
	test.push_back(2);
	//test.push_back(3);
	std::cout<<"Checking is buffer empty function "<<test.empty()<<"\n";
	std::cout<<"Checking length of buffer after modification "<<test.size()<<"\n";
	std::cout<<"Checking front function  "<<test.front()<<"\n";
	std::cout<<"Checking front function  "<<test.front()<<"\n";
	std::cout<<"Checking back function  "<<test.back()<<"\n";
	test.back() = 10;
	
	std::cout<<"Checking pop function\n";
	test.pop_front();
	std::cout<<"Checking front function  "<<test.front()<<"\n";
	std::cout<<"Checking back function  "<<test.back()<<"\n";
	//std::cout<<"Checking []operator  "<<test[10]<<"\n";

	CircularBuffer<std::string> test_stringbuf{10};
	std::cout<<"Checking is buffer empty function "<<test_stringbuf.empty()<<"\n";
	std::cout<<"Checking length of string buffer "<<test_stringbuf.size()<<"\n";
	std::cout<<"size of buffer in bytes "<<test_stringbuf.buffer_size()<<"\n";
	std::cout<<"Max capacity  of buffer "<<test_stringbuf.capacity()<<"\n";
	
	std::cout<<"Pushing back  data in bufffer \n";
	test_stringbuf.push_back("this is the first string");	
	test_stringbuf.push_back("this is the second string");
	test_stringbuf.push_back("this is the third string"); 

	std::cout<<"Checking is buffer empty function "<<test_stringbuf.empty()<<"\n";
	std::cout<<"Checking length of buffer after modification "<<test_stringbuf.size()<<"\n";
	std::cout<<"Checking front function  "<<test_stringbuf.front()<<"\n";
	std::cout<<"Checking back function  "<<test_stringbuf.back()<<"\n";
	test_stringbuf.pop_front();
	std::cout<<"Checking length of buffer after modification "<<test_stringbuf.size()<<"\n";
	std::cout<<"Checking front function  "<<test_stringbuf.front()<<"\n";
	std::cout<<"Checking back function  "<<test_stringbuf.back()<<"\n";
	
	std::cout<<"Checking iterator function\n";
	auto it = test_stringbuf.begin();
	
	std::cout<<"Checking deference * operator "<<*it<<"\n";
	std::cout<<"Checking deference ++ operator "<<*(++it)<<"\n";
	std::cout<<"Checking deference -- operator "<<*(--it)<<"\n";

	
	std::cout<<"Checking iterator for loop  \n";
	for(auto it:test_stringbuf)
		std::cout<<"Checking for loop function  "<<it<<"\n";

	std::cout<<"Checking for loop with iterator  \n";
	for(auto it = test_stringbuf.begin(); it != test_stringbuf.end(); it++)
		std::cout<<"Checking for loop function  "<<*it<<"\n";
	
	CircularBuffer<test_struct> test_structbuf{5};
	std::cout<<"Checking [] operator"<<test_structbuf[0]<<"\n";
	
	auto temp_struct = test_struct();
	
	test_structbuf.push_back(temp_struct);
	std::cout<<"Checking [] operator"<<test_structbuf[1]<<"\n";
	std::cout<<"Checking at operator"<<test_structbuf.at(0)<<"\n";
	
	test_structbuf.push_back(temp_struct);
	std::cout<<"Checking at operator"<<test_structbuf.at(1)<<"\n";
	test_structbuf.push_back(temp_struct);
	std::cout<<"Checking at operator"<<test_structbuf.at(2)<<"\n";
	test_structbuf.push_back(temp_struct);
	std::cout<<"Checking at operator"<<test_structbuf.at(3)<<"\n";
	test_structbuf.push_back(temp_struct);
	std::cout<<"Checking at operator"<<test_structbuf.at(4)<<"\n";
	test_structbuf.push_back(temp_struct);
	std::cout<<"Checking at operator"<<test_structbuf.at(0)<<"\n";
	test_structbuf.push_back(temp_struct);
	test_structbuf.push_back(temp_struct);
	test_structbuf.push_back(temp_struct);
	test_structbuf.push_back(temp_struct);
	
	
	test_structbuf.pop_front();
	
	CircularBuffer<std::string> test_stringbufcopy{test_stringbuf};
	std::cout<<"Checking  maxsize of copy buffer"<<test_stringbufcopy.capacity()<<"\n";
	std::cout<<"Checking  size of copy buffer"<<test_stringbufcopy.size()<<"\n";
	std::cout<<"Checking  [] in copybuffer"<<test_stringbufcopy[1]<<"\n";
	std::cout<<"Checking maxsize buffer"<<test_stringbuf.capacity()<<"\n";
	std::cout<<"Checking size buffer"<<test_stringbuf.size()<<"\n";
	return 0;
}



