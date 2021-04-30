#include "circular_buffer.h"
#include <iostream>
#include <string.h>
#include <vector>
#include <thread>
#include <chrono>

struct custom_struct{
	static int count ; 
	char* bytes =nullptr;
	int id = 0;
	custom_struct(){
		bytes = (char*)malloc(100);
		id = count;
		std::cout<<"constructing custom_struct: "<<count++<<"\n";
	}
	
	custom_struct(const custom_struct& other){
		bytes = (char*)malloc(100);
		memcpy(bytes, other.bytes,100);
		std::cout<<"copy constructor called for custom_struct \n";
	}

	custom_struct(custom_struct&& other){
		bytes = other.bytes;
		other.bytes = nullptr;
		std::cout<<"move constructor called for custom_struct \n";
	}
	
	custom_struct& operator=(const custom_struct& other){
		memcpy(bytes, other.bytes,100);
		std::cout<<"assignment operator called for custom_struct \n";
		return *this;
	}

	custom_struct& operator=(custom_struct&& other){
		delete(bytes);
		bytes = other.bytes;
		other.bytes = nullptr;
		std::cout<<"move assignment operator called for custom_struct \n";
		return *this;
	}
	
	~custom_struct(){
		std::cout<<"destructor called for test struct "<<id<<std::endl;
		count--;
		free(bytes);
		bytes = nullptr;
	}

	friend std::ostream& operator<<(std::ostream& os, const custom_struct& ts){
		return os<<"Printing struct no: "<< ts.id<<"\n";
	}
	

};

int custom_struct::count =0;


int main(int argc, char *argv[])
{   
	CircularBuffer<custom_struct> custom_buffer(5);
	custom_struct element;
	for (int i = 0; i < 10; ++i) {
		custom_buffer.push_back(element);		
	}

	CircularBuffer<custom_struct> buffermoved = std::move(custom_buffer);
	CircularBuffer<custom_struct> buffermoveassigned{10};
	buffermoveassigned = std::move(buffermoved);
	buffermoveassigned.push_back(std::move(element));
	return 0;
}

