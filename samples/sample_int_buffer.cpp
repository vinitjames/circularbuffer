#include "circular_buffer.h"
#include <iostream>
#include <string.h>

int main(int argc, char *argv[])
{   
	//Initializing a buffer
    CircularBuffer<int> int_buff{5};

	//checking buffer empty function
    std::cout<<"Calling buffer empty function "<<int_buff.empty()<<"\n";
	
	//Pushing data back into buffer
	std::cout<<"Pushing back  data in bufffer \n";
	int_buff.push_back(5);
	int_buff.push_back(2);
	int_buff.push_back(1250);
	int_buff.push_back(500);
	int_buff.push_back(235);

	//Length of buffer
	std::cout<<"Checking length of buffer "<<int_buff.size()<<"\n";
	//Using Front Function, gives the first element
	std::cout<<"Checking front function  "<<int_buff.front()<<"\n";
	//Using Back Function, gives last element 
	std::cout<<"Checking back function  "<<int_buff.back()<<"\n";
	//Front and Back can be used for assignment
	int_buff.front() = 100;
	int_buff.back() = 10;

	//Pop Function removes  element as per FIFO
	std::cout<<"Checking pop_front function\n";
	int_buff.pop_front();
	std::cout<<"pop front executed new size: "<<int_buff.size()
			 <<" new front:" <<int_buff.front()<<"\n";
	
	std::cout<<"Checking iterator function\n";
	auto it = int_buff.begin();
	
	std::cout<<"Checking deference * operator "<<*it<<"\n";
	std::cout<<"Checking deference ++ operator "<<*(++it)<<"\n";
	std::cout<<"Checking deference -- operator "<<*(--it)<<"\n";

	// Range based  for loop can be used like other STL containers
	std::cout<<"Checking iterator for loop  \n";
	for(const auto& it: int_buff)
		std::cout<<"Checking range based for loop function  "<<it<<"\n";

	// for loop with iterators can be used like other STL stile containers
	std::cout<<"Checking for loop with iterator  \n";
	for(auto it = int_buff.begin(); it != int_buff.end(); it++)
		std::cout<<"Checking for loop function  "<<*it<<"\n";
   
	return 0;
}



