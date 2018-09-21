#include "vector.hpp"

namespace cppit {

	template<typename T>
	std::ostream& operator<<(std::ostream &_os, const Vector<T> &_output) {
		_os << "[";
		for (size_t _index = 0ul; _index < _output._size; _index++)
			_os << _output._vector[_index] << ", ";
		_os << "]";
		return _os;
	}

	template<typename T>
	short int Vector<T>::reserve(const size_t &_newBufferSize) {
		if (_newBufferSize <= _bufferSize)
			return 1; // Loss of data, forbidden
		_bufferSize = _newBufferSize;

		T *_temp;
		if (!(_temp = new T[_newBufferSize]))
			return 2; //Bad allocation

		memcpy(_temp, this->_vector, _size*sizeof(T));
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
		memcpy(_temp, _vector, _size*sizeof(T));

		delete[] _vector;
		_vector = _temp;
		_bufferSize = _size;

		return true; // Return succesfully
	}

	template<typename T>
	short int Vector<T>::push_back(const T &_elem) {
		if (_size + 1 > _bufferSize)
			if(reserve(_bufferSize + 20ul))
				return 1;
		
		_vector[_size] = _elem;
		_size++;
		return 0;
	}

	template<typename T>
	short int Vector<T>::push_front(const T &_elem) {
		if (++_size > _bufferSize)
			if (reserve(_bufferSize + 20ul))
				return 1;
		for (size_t _index = _size - 1ul; _index > 0ul; _index--)
			_vector[_index] = _vector[_index - 1ul];
		_vector[0] = _elem;
		return 0;
	}

	template<typename T>
	short int Vector<T>::insert(const T &_elem, const size_t &_pos) {
		if (_pos > _size)
			return 1; // Space not accesible by user
		if (++_size > _bufferSize)
			this->reserve(_bufferSize + 15ul);

		for (size_t _index = _size - 1ul; _index > _pos; _index--) {
			_vector[_index] = _vector[_index - 1ul];
		}
		_vector[_pos] = _elem;
		return 0;
	}

	template<typename T>
	T Vector<T>::pop() {
		if (_size == 0ul)
			exit(1);
		_size--;
		return _vector[_size];
	}

	template<typename T>
	T& Vector<T>::operator[](const size_t& _pos) {
		if (_pos > _size - 1)
			exit(1); // Not accessible
		return this->_vector[_pos];
	}

	template<typename T>
	void Vector<T>::swap(Vector<T> &_swapVector) {
		T* _temp = this->_vector;
		this->_vector = _swapVector._vector;
		_swapVector._vector = _temp;
		size_t _tempSize = this->_bufferSize;
		this->_bufferSize = _swapVector._bufferSize;
		_swapVector._bufferSize = _tempSize;
		_tempSize = this->_size;
		this->_size = _swapVector._size;
		_swapVector._size = _tempSize;
		_temp = nullptr;
	}

	template<typename T>
	const size_t Vector<T>::length() const {
		return this->_size;
	}

} // namespace cppit