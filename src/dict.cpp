#include "dict.hpp"

namespace cppit {

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
	const size_t Dictionary<T, U>::bufferSize() const {
		return this->_bufferSize;
	}

} // namespace cppit