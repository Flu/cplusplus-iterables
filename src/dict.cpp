#include "dict.hpp"

namespace cppit {

	template<typename T, typename U>
	Dictionary<T, U> Dictionary<T, U>::operator=(const Dictionary<T, U> &_copyDict) {
		if (!_copyDict._keys || !_copyDict._values)
			exit(1); // Won't copy null pointers
		_size = _copyDict._size;
		_bufferSize = _copyDict._bufferSize;

		if (!(_keys = new T[_bufferSize]) || !(_values = new U[_bufferSize]))
			throw std::bad_alloc();
		
		memcpy(_keys, _copyDict._keys, _size*sizeof(T));
		memcpy(_values, _copyDict._values, _size*sizeof(U));
		return *this;
	}

	template<typename T, typename U>
	const size_t Dictionary<T, U>::length() const {
		return this->_size;
	}

	template<typename T, typename U>
	short int Dictionary<T, U>::reserve(const size_t &_newBufferSize) {
		if (_newBufferSize <= _bufferSize)
			return 1; // Loss of data, forbidden
		_bufferSize = _newBufferSize;

		T *_tempKeys;
		U *_tempValues;
		if (!(_tempKeys = new T[_bufferSize]) || !(_tempValues = new U[_bufferSize]))
			throw std::bad_alloc();
		
		memcpy(_tempKeys, this->_keys, _size*sizeof(T));
		memcpy(_tempValues, this->_values, _size*sizeof(U));
		delete[] _keys, _values;

		_keys = _tempKeys;
		_values = _tempValues;
		return 0;
	}

	template<typename T, typename U>
	bool Dictionary<T, U>::shrink() {
		T *_tempKeys;
		U *_tempValues;
		if (!(_tempKeys = new T[_size]) || !(_tempValues = new U[_size]))
			throw std::bad_alloc();
		
		memcpy(_tempKeys, this->_keys, _size*sizeof(T));
		memcpy(_tempValues, this->_values, _size*sizeof(U));
		delete[] _keys, _values;

		_keys = _tempKeys;
		_values = _tempValues;
		_bufferSize = _size;
		return true;
	}

	template<typename T, typename U>
	const size_t Dictionary<T, U>::bufferSize() const {
		return this->_bufferSize;
	}

} // namespace cppit