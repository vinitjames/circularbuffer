CircularBuffer_CPP
===========

[![Actions Status](https://github.com/vinitjames/circularbuffer_CPP/workflows/Build%20and%20Test/badge.svg)](https://github.com/vinitjames/circularbuffer_CPP/actions)


## About
circularbuffer_CPP is a simple, general purpose STL style [circularbuffer](https://en.wikipedia.org/wiki/Circular_buffer) implementation in C++.


## Features
* STL style implementaion of Circular Buffer
* Lightweight (only single header file)
* Simple API conforming to STL container semantics.
* Random Access Iterator for easy forwad and reverse iteration and looping through elements.
* Test suites

## Installation
Run:
```
git clone https://github.com/vinitjames/circularbuffer_CPP.git
```
# Without CMAKE 
copy circular_buffer.h to your project

# With CMAKE to run tests
Run ```mkdir build
       cd build 
       cmake ..
       cmake --build .
       ctest ``` 
 to compile and run tests.
