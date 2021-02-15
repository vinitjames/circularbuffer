#include "circular_buffer.h"
#include <iostream>
#include <string.h>
#include "circular_buffer.h"
#include <iostream>
#include <string.h>

int main(int argc, char *argv[])
{   
	
    CircularBuffer<int> test{5};
	//std::cout<<"size of data "<<sizeof(data[1].bytes)<<"\n";
	std::cout<<"length of buffer "<<test.size()<<"\n";
	std::cout<<"size of buffer in bytes "<<test.buffer_size()<<"\n";
	std::cout<<"Max capacity  of buffer "<<test.capacity()<<"\n";
	std::cout<<"Checking is buffer empty function "<<test.empty()<<"\n";
	std::cout<<"Pushing back  data in bufffer \n";
	for(int i = 0; i<100;i++){
		test.push_back(i);
		std::cout<<"Pushing back i"<<std::endl;
	}
    
	CircularBuffer<std::string> test_stringbuf{10};
	std::cout<<"Checking is buffer empty function "<<test_stringbuf.empty()<<"\n";
	std::cout<<"Checking length of string buffer "<<test_stringbuf.size()<<"\n";
	std::cout<<"size of buffer in bytes "<<test_stringbuf.buffer_size()<<"\n";
	std::cout<<"Max capacity  of buffer "<<test_stringbuf.capacity()<<"\n";

	for(int i = 0; i<10;i++){
		test_stringbuf.push_back("this is a string" + std::to_string(i));
		std::cout<<"Pushing back string "<<i<<std::endl;
	}
	
	std::cout<<"Checking is buffer empty function "<<test_stringbuf.empty()<<"\n";
	std::cout<<"Checking length of buffer after modification "<<test_stringbuf.size()<<"\n";
	std::cout<<"Checking front function  "<<test_stringbuf.front()<<"\n";
	std::cout<<"Checking back function  "<<test_stringbuf.back()<<"\n";

	for(int i = 0; i<7;i++){
		test_stringbuf.pop_front();
		std::cout<<"Poping "<<i<<std::endl;
	}

	std::cout<<"Checking is buffer empty function "<<test_stringbuf.empty()<<"\n";
	std::cout<<"Checking length of buffer after modification "<<test_stringbuf.size()<<"\n";
	std::cout<<"Checking front function  "<<test_stringbuf.front()<<"\n";
	std::cout<<"Checking back function  "<<test_stringbuf.back()<<"\n";
	/*
	//test_stringbuf.pop_front();
	std::cout<<"Checking length of buffer after modification "<<test_stringbuf.size()<<"\n";
	std::cout<<"Checking front function  "<<test_stringbuf.front()<<"\n";
	std::cout<<"Checking back function  "<<test_stringbuf.back()<<"\n";

	/*
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
	*/
	std::cout<<"end is reached"<<std::endl;
	return 0;
}
