#include <iostream>
#include <functional>
#include <stdio.h>
#include <string.h>

namespace cppit {
  
	template<typename T>
  class Iterator {
		T *_position;
	public:
		Iterator() : _position(nullptr) {}
		Iterator(T *_initPosition) : _position(_initPosition) {}
		Iterator(const Iterator &_lvalue) : _position(_lvalue._position) {}
		
		Iterator<T> operator++();
		Iterator<T> operator++(int);
		Iterator<T> operator--();
		Iterator<T> operator--(int);
		T& operator*() const;
		bool operator==(const Iterator& _compare) const;
		bool operator!=(const Iterator& _compare) const;
		Iterator& operator->();

		~Iterator() {}
	};

	template<typename T>
	Iterator<T> Iterator<T>::operator++() {
		_position++;
		return *this;
	}

	template<typename T>
	Iterator<T> Iterator<T>::operator++(int a) {
		Iterator<T> _temp = *this;
		_position++;
		return _temp;
	}

	template<typename T>
	Iterator<T> Iterator<T>::operator--() {
		_position--;
		return *this;
	}

	template<typename T>
	Iterator<T> Iterator<T>::operator--(int a) {
		Iterator<T> _temp = *this;
		_position--;
		return _temp;
	}

	template<typename T>
	T& Iterator<T>::operator*() const {
		return *_position;
	}

	template<typename T>
	bool Iterator<T>::operator==(const Iterator<T> &_compare) const {
		return (_position == _compare._position) ? true : false;
	}

	template<typename T>
	bool Iterator<T>::operator!=(const Iterator<T> &_compare) const {
		return (_position != _compare._position) ? true : false;
	}

	template<typename T>
	Iterator<T>& Iterator<T>::operator->() {
		return _position;
	}
  
  class String;
	template<class T> class Vector;
	template<class T, class U> class Dictionary;
} // namespace cppit

#ifndef _CPPIT_STRING
	#define _CPPIT_STRING
	#include "string.cpp"
#endif
#ifndef _CPPIT_VECTOR
	#define _CPPIT_VECTOR
	#include "vector.cpp"
#endif
#ifndef _CPPIT_DICT
	#define _CPPIT_DICT
	#include "dict.cpp"
#endif
#ifndef _CPPIT_TUPLE
	#define _CPPIT_TUPLE
	#include "tuple.cpp"
#endif