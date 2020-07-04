#include "circular_buffer.h"
#include <iostream>
#include <string.h>
struct test_struct{
	int i;
	static int count ;
	char* bytes =nullptr; 
	test_struct(){
		i=0;
		bytes = (char*)malloc(10000000);
		std::cout<<"constructing test_struct: "<<count++<<"\n";
		}
	~test_struct(){
		std::cout<<"destructing test_struct\n";
		free(bytes);
	}
	};

int test_struct::count =0;
int main(int argc, char *argv[])
{   
	
	
    CircularBuffer<test_struct> test{100};
	//std::cout<<"size of data "<<sizeof(data[1].bytes)<<"\n";
	std::cout<<"size of buffer "<<test.size()<<"\n";
	std::cout<<"Max capacity  of buffer "<<test.capacity()<<"\n";
	std::cout<<"Checking is buffer empty function "<<test.empty()<<"\n";
	
	std::cout<<"size of  test buffer "<<test.buffer_size()<<"\n";
	//while(true){}
    return 0;
}
