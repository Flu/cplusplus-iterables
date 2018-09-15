#include "vector.hpp"

namespace cppit {

	template<typename T>
	std::ostream& operator<<(std::ostream &_os, const Vector<T> _output) {
		_os << "[";
		for (size_t _index = 0ul; _index < _output._size; _index++)
			_os << _output._vector[index] << ", ";
		_os << "]";
		return _os;
	}

	template<typename T>
	short int Vector<T>::reserve(const size_t _newBufferSize) {
		if (_newBufferSize < _bufferSize)
			return 1; // Loss of data, forbidden
		_bufferSize = _newBufferSize;
		T *_temp;
		if (!(_temp = new T[_bufferSize]))
			return 2; //Bad allocation

		memcpy(_temp, this->_vector, _size);
		delete[] _vector;

		_vector = _temp;
		return 0;
	}

	template<typename T>
	size_t Vector<T>::bufferSize() const {
		return this->_bufferSize;
	}

	template<typename T>
	bool Vector<T>::shrink() {
		T *_temp;
		if (!(_temp = new T[_size]))
			return false; // Bad allocation
		memcpy(_temp, _vector, _size);

		delete[] _vector;
		_vector = _temp;
		_bufferSize = _size;
		
		return true; // Return succesfully
	}

}