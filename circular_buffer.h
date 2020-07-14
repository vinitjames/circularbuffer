#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <iostream>
#include <mutex>
#include <memory>
#include <iterator>
#include <type_traits>

template<typename T>
class CircularBuffer {
private:
	
	typedef T value_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	template <bool isConst>
	struct BufferIterator;
	typedef BufferIterator<false> iterator;
	typedef BufferIterator<true> const_iterator;

public:
	
	explicit CircularBuffer(size_t size)
		:_buff{std::unique_ptr<T[]>(new T[size])}, _max_size{size}{}

	void push_back(const value_type& data);
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
	const_reference operator[](size_type index) const;
	reference operator[](size_type index);

	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;
		
private:
	void _increment_bufferstate();
	void _decrement_bufferstate();
	mutable std::mutex _mtx;
	std::unique_ptr<T[]> _buff;
	size_type _head = 0;
	size_type _tail = 0;
	size_type _size = 0;
	size_type _max_size = 0;
	bool _full = false;
		
    template<bool isConst = false>
	class  BufferIterator{
	public:
		
		typedef std::random_access_iterator_tag iterator_type;
		typedef typename std::conditional<isConst, const T&, T&>::type reference;
		typedef typename std::conditional<isConst, const T*, T*>::type pointer;
		typedef CircularBuffer*  cbuf_pointer;
		
		cbuf_pointer _ptrToBuffer;
		size_type _offset;
		size_type _index;
		bool _reverse;

		bool _comparable(const BufferIterator& other){
			return (_ptrToBuffer == other._ptrToBuffer)&&(_reverse == other._reverse);
		}
		
		BufferIterator()
			:_ptrToBuffer{nullptr}, _offset{0}, _index{0}, _reverse{false}{}
		
		BufferIterator(const BufferIterator<false>& it)
			:_ptrToBuffer{it._ptrToBuffer},
			 _offset{it._offset},
			 _index{it._index},
			 _reverse{it._reverse}{}

		reference operator*(){
			if(_reverse)
				return (*_ptrToBuffer)[(_ptrToBuffer->size() - _index)];
			return (*_ptrToBuffer)[_index];
		}

		pointer  operator->() { return &(operator*()); }

		reference operator[](size_type index){
			this->_index += index;
			return this->operator*();
		}

		BufferIterator& operator++(){
			++_index;
			return *this;
		}

		BufferIterator operator++(int){
			BufferIterator iter = *this;
			++_index;
			return iter;
		}

		BufferIterator& operator--(){
			--_index;
			return *this;
		}

		BufferIterator operator--(int){
			BufferIterator iter = *this;
			--_index;
			return iter;
		}	

		friend BufferIterator operator+(BufferIterator lhsiter, difference_type n){
			lhsiter._index += n;
			return lhsiter;
		}

		friend BufferIterator operator+(difference_type n, BufferIterator rhsiter){
			rhsiter._index += n;
			return rhsiter;
		}

		BufferIterator& operator+=(difference_type n){
			_index += n;
			return *this;
		}

		friend BufferIterator operator-(BufferIterator lhsiter, difference_type n){
			lhsiter._index -= n;
			return lhsiter;
		}

		BufferIterator& operator-=(difference_type n){
			_index -= n;
			return *this;
		}

		bool operator==(const BufferIterator& other){
			if (!_comparable(other))
				return false;
			return ((_index == other._index)&&(_offset == other._offset));
		}
		
		bool operator!=(const BufferIterator& other){
			if (!_comparable(other))
				return true;
			return ((_index != other._index)||(_offset != other._offset));
		}

		bool operator<(const BufferIterator& other){
			if (!_comparable(other))
				return false;
			return ((_index + _offset)<(other._index+other._offset));
		}

		bool operator>(const BufferIterator& other){
			if (!_comparable(other))
				return false;
			return ((_index + _offset)>(other._index+other._offset));
		}

		bool operator<=(const BufferIterator& other){
			if (!_comparable(other))
				return false;
			return ((_index + _offset)<=(other._index+other._offset));
		}

		bool operator>=(const BufferIterator& other){
			if (!_comparable(other))
				return false;
			return ((_index + _offset)>=(other._index+other._offset));
		}
		
	};
};

template<typename T>
inline 
bool CircularBuffer<T>::full() const{
	//return _full;
	return _size == _max_size;
}

template<typename T>
inline 
bool CircularBuffer<T>::empty() const{
	//return ((!full()) &&(_head == _tail));
	return _size == 0;
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
	_head = _tail = _size = _max_size = 0;
}

template<typename T>
inline 
typename CircularBuffer<T>::size_type CircularBuffer<T>::size() const{
	std::lock_guard<std::mutex> _lck(_mtx);
	return _size;
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
	return _buff[_head-1];
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
	return _buff[_head - 1];
}

template<typename T> 
void CircularBuffer<T>::push_back(const T& data){
	std::lock_guard<std::mutex> _lck(_mtx);
	if(full())
		_buff[_head].~T();
	_buff[_head] = data;
	_increment_bufferstate();
}

template<typename T>
inline 
void CircularBuffer<T>::_increment_bufferstate(){
	if(full())
		_tail = (_tail + 1)%_max_size;
	else
		++_size;
	_head = (_head + 1)%_max_size;
	_full = (_head == _tail);
}

template<typename T>
inline 
void CircularBuffer<T>::pop_front(){
	std::lock_guard<std::mutex> _lck(_mtx);
	if(empty())
		throw std::length_error("pop_back called on empty buffer");
	_decrement_bufferstate();
}

template<typename T>
inline 
void CircularBuffer<T>::_decrement_bufferstate(){
	//_full = false;
	--_size;
	_tail = (_tail + 1)%_max_size;
}

template<typename T>
inline 
typename CircularBuffer<T>::reference CircularBuffer<T>::operator[](size_t index) {
	if((index<0)||(index>_max_size))
		throw std::out_of_range("Index is out of Range of buffer size");
	index += _tail;
	index %= _max_size;
	return _buff[index];
}

template<typename T>
inline 
typename CircularBuffer<T>::const_reference CircularBuffer<T>::operator[](size_t index) const {
	if((index<0)||(index>_max_size))
		throw std::out_of_range("Index is out of Range of buffer size");
	index += _tail;
	index %= _max_size;
	return _buff[index];
}

template<typename T>
inline 
typename CircularBuffer<T>::iterator CircularBuffer<T>::begin() {
	std::lock_guard<std::mutex> _lck(_mtx);
	iterator iter;
	iter._ptrToBuffer = this;
	iter._offset = _tail;
	iter._index = 0;
	iter._reverse = false;
	return iter;
}

template<typename T>
inline 
typename CircularBuffer<T>::const_iterator CircularBuffer<T>::begin() const{
	std::lock_guard<std::mutex> _lck(_mtx);
	iterator iter;
	iter._ptrToBuffer = this;
	iter._offset = _tail;
	iter._index = 0;
	iter._reverse = false;
	return iter;
}

template<typename T>
inline 
typename CircularBuffer<T>::iterator CircularBuffer<T>::end() {
	std::lock_guard<std::mutex> _lck(_mtx);
	iterator iter;
	iter._ptrToBuffer = this;
	iter._offset = _tail;
	iter._index = _size;
	iter._reverse = false;
	return iter;
}

template<typename T>
inline 
typename CircularBuffer<T>::const_iterator CircularBuffer<T>::end() const{
	std::lock_guard<std::mutex> _lck(_mtx);
	iterator iter;
	iter._ptrToBuffer = this;
	iter._offset = _tail;
	iter._index = _size;
	iter._reverse = false;
	return iter;
}

#endif /* CIRCULAR_BUFFER_H */
