#include <iostream>
#include <mutex>
#include <memory>

template<typename T>
class CircularBuffer {
public:
	
	typedef T value_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	
	explicit CircularBuffer(size_t size)
		:_buff{std::unique_ptr<T[]>(new T[size])}, _max_size{size}{}

	void push_back(const T& data);
	void pop_back();
	void pop_front();
	reference front();
	reference back(); 
	const_reference front() const; 
	const_reference back() const;
	void clear();
	bool empty() const ;
	bool full() const ;
	size_type capacity() const ;
	size_type size() const;
	size_type buffer_size() const {return sizeof(T)*_max_size;};
	const_reference operator[](size_t index) const;
	reference operator[](size_t index);
	
	
	
private:
	void _increment_bufferstate();
	void _decrement_bufferstate();
	mutable std::mutex _mtx;
	std::unique_ptr<T[]> _buff;
	size_type _head = 0;
	size_type _tail = 0;
	size_type _max_size = 0;
	bool _full = false;
};

template<typename T>
inline 
bool CircularBuffer<T>::full() const{
	return _full;
}

template<typename T>
inline 
bool CircularBuffer<T>::empty() const{
	return (!_full &&(_head == _tail));
}

template<typename T>
inline 
typename CircularBuffer<T>::size_type CircularBuffer<T>::capacity() const{
	return _max_size;
}

template<typename T>
inline 
void  CircularBuffer<T>::clear(){
	std::lock_guard<std::mutex> _lck(_mtx);
	_head = _tail = _max_size = 0;
	_full = false;
}

template<typename T>
inline 
typename CircularBuffer<T>::size_type CircularBuffer<T>::size() const{
	std::lock_guard<std::mutex> _lck(_mtx);
	if(_full)
		return _max_size;
	else{
		if(_head >= _tail)
			return _head -_tail;
		else
			return _max_size - _tail +_head;
	}
}

template<typename T>
inline
typename CircularBuffer<T>::reference CircularBuffer<T>::front() {
	std::lock_guard<std::mutex> _lck(_mtx);
	if(empty())
		throw std::length_error("front function called on empty buffer");
	return _buff[_tail];
}

template<typename T>
inline
typename CircularBuffer<T>::reference CircularBuffer<T>::back() {
	std::lock_guard<std::mutex> _lck(_mtx);
	if(empty())
		throw std::length_error("back function called on empty buffer");
	return _buff[_head];
}

template<typename T>
inline
typename CircularBuffer<T>::const_reference CircularBuffer<T>::front() const{
	std::lock_guard<std::mutex> _lck(_mtx);
	if(empty())
		throw std::length_error("front function called on empty buffer");
	return _buff[_tail];
}

template<typename T>
inline
typename CircularBuffer<T>::const_reference CircularBuffer<T>::back() const{
	std::lock_guard<std::mutex> _lck(_mtx);
	if(empty())
		throw std::length_error("back function called on empty buffer");
	return _buff[_tail];
}

template<typename T> 
void CircularBuffer<T>::push_back(const T& data){
	std::lock_guard<std::mutex> _lck(_mtx);
	_buff[_head] = data;
	_increment_bufferstate();
}

template<typename T>
inline 
void CircularBuffer<T>::_increment_bufferstate(){
	if(_full)
		_tail = (_tail + 1)%_max_size;
	_head = (_head + 1)%_max_size;
	_full = (_head == _tail);
}

template<typename T>
inline 
void CircularBuffer<T>::pop_back(){
	std::lock_guard<std::mutex> _lck(_mtx);
	if(empty())
		throw std::length_error("pop_back called on empty buffer");
	_decrement_bufferstate();
}

template<typename T>
inline 
void CircularBuffer<T>::_decrement_bufferstate(){
	
	_full = false;
	_tail = (_tail + 1)%_max_size;
}

template<typename T>
inline 
typename CircularBuffer<T>::reference CircularBuffer<T>::operator[](size_t index) {
	if((index<0)||(index>_max_size))
		throw std::out_of_range("Index is out of Range of buffer size");
	index += _tail+index;
	index %= _max_size;
	return _buff[index];
}

template<typename T>
inline 
typename CircularBuffer<T>::const_reference CircularBuffer<T>::operator[](size_t index) const {
	if((index<0)||(index>_max_size))
		throw std::out_of_range("Index is out of Range of buffer size");
	index += _tail+index;
	index %= _max_size;
	return _buff[index];
}


