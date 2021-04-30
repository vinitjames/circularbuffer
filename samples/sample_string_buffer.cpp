#include "circular_buffer.h"
#include <iostream>
#include <string.h>
#include "circular_buffer.h"
#include <iostream>
#include <string.h>
#include <utility>


int main(int argc, char *argv[])
{   
	   
	CircularBuffer<std::string> string_buff{10};
	//checking buffer empty function
    std::cout<<"Calling buffer empty function "<<string_buff.empty()<<"\n";
	
	//Pushing data back into buffer
	std::cout<<"Pushing back string data in bufffer \n";
	for(int i = 0; i<10;i++){
		string_buff.push_back(" sample string " + std::to_string(i));
		std::cout<<"Pushing back string "<<i<<std::endl;
	}
	
	//Length of buffer
	std::cout<<"Checking length of buffer "<<string_buff.size()<<"\n";
	//Using Front Function, gives the first element
	std::cout<<"Checking front function  "<<string_buff.front()<<"\n";
	//Using Back Function, gives last element 
	std::cout<<"Checking back function  "<<string_buff.back()<<"\n";
	//Front and Back can be used for assignment
	string_buff.front() = "modified front string";
	string_buff.back() = "modified back string";

	//Pop Function removes  element as per FIFO
	std::cout<<"Checking pop_front function\n";
	string_buff.pop_front();
	std::cout<<"pop front executed new size: "<<string_buff.size()
			 <<" new front:" <<string_buff.front()<<"\n";
	
	std::cout<<"Checking iterator function\n";
	auto it = string_buff.begin();
	
	std::cout<<"Checking deference * operator "<<*it<<"\n";
	std::cout<<"Checking deference ++ operator "<<*(++it)<<"\n";
	std::cout<<"Checking deference -- operator "<<*(--it)<<"\n";

	// Range based  for loop can be used like other STL containers
	std::cout<<"Checking iterator for loop  \n";
	for(auto& it: string_buff)
		std::cout<<"Checking range based for loop function  "<<it<<"\n";

	// for loop with iterators can be used like other STL stile containers
	std::cout<<"Checking for loop with iterator  \n";
	for(auto it = string_buff.begin(); it != string_buff.end(); it++)
		std::cout<<"Checking for loop function  "<<*it<<"\n";
   
	// push_back using move semantics
	std::string string_to_move{"This string is moved"};
	string_buff.push_back(std::move(string_to_move));
	std::cout<<"string moved to buffer  new size: "<<string_buff.size()
			 <<" new back:" <<string_buff.back()<<"\n";

	//creating buffer from another buffer
	CircularBuffer<std::string> string_buff_copy1{string_buff};
	std::cout<<"Buffer Copy Created, copied buffer size "<<string_buff_copy1.size()<<"\n";

	//copying buffer 
	CircularBuffer<std::string> string_buff_copy2{10};
	string_buff_copy2 = string_buff;
	std::cout<<"Buffer Copy assigned , copied buffer size "<<string_buff_copy2.size()<<"\n";
	
	//move constructing
	CircularBuffer<std::string> string_buff_move1{std::move(string_buff)};
	std::cout<<"Buffer created with move constructor, moved buffer size "<<string_buff_move1.size()<<"\n";

	//move assignment 
	CircularBuffer<std::string> string_buff_move2{10};
	string_buff_move2 = std::move(string_buff_move1);
	std::cout<<"Buffer  moved with  assignment operator, moved buffer size "<<string_buff_move2.size()<<"\n";
	
}
