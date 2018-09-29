#include "dict.hpp"

namespace cppit {

	template<typename Key, typename U>
	Dictionary<Key, U> Dictionary<Key, U>::operator=(const Dictionary<Key, U> &_copyDict) {
		if (!_copyDict._keys || !_copyDict._values)
			exit(1); // Won't copy null pointers
		_size = _copyDict._size;
		_bufferSize = _copyDict._bufferSize;

		if (!(_keys = new Key[_bufferSize]) || !(_values = new U[_bufferSize]))
			throw std::bad_alloc();
		
		memcpy(_keys, _copyDict._keys, _size*sizeof(Key));
		memcpy(_values, _copyDict._values, _size*sizeof(U));
		return *this;
	}

	template<typename Key, typename U>
	bool Dictionary<Key, U>::operator==(const Dictionary<Key, U> &_compare) const {
		if (_size != _compare._size)
			return false;
		for (size_t index = 0ul; index < _size; index++) {
			if (!_compare.hasKey(_keys[index]))
				return false;
			if (_values[index] != _compare[_keys[index]])
				return false;
		}
		return true;
	}

	template<typename Key, typename U>
	inline bool Dictionary<Key, U>::operator!=(const Dictionary<Key, U> &_compare) const {
		return !(this->operator==(_compare));
	}

	template<typename Key, typename U>
	bool Dictionary<Key, U>::hasKey(const Key &_key) const {
		for (size_t index = 0ul; index < _size; index++)
			if (_keys[index] == _key)
				return true;
		return false;
	}

	template<typename Key, typename U> // Accessor
	const U& Dictionary<Key, U>::operator[](const Key &_key) const {
		for (size_t index = 0ul; index < _size; index++) {
			if (_keys[index] == _key)
				return _values[index];
		}
		throw std::out_of_range("Key not found");
	}

	template<typename Key, typename U> // Mutator
	U& Dictionary<Key, U>::operator[](const Key &_key) {
		for (size_t index = 0ul; index < _size; index++) {
			if (_keys[index] == _key)
				return _values[index];
		}
		if (++_size > _bufferSize)
			this->reserve(_bufferSize + 15ul);
		_keys[_size - 1] = _key;
		return _values[_size - 1];
	}

	template<typename Key, typename U>
	U& Dictionary<Key, U>::get(const Key &_key, const U &_defaultValue) {
		for (size_t index = 0ul; index < _size; index++) {
			if (_keys[index] == _key)
				return _values[index];
		}
		return _defaultValue;
	}

	template<typename Key, typename U>
	const size_t Dictionary<Key, U>::length() const {
		return this->_size;
	}

	template<typename Key, typename U>
	short int Dictionary<Key, U>::reserve(const size_t &_newBufferSize) {
		if (_newBufferSize <= _bufferSize)
			return 1; // Loss of data, forbidden
		_bufferSize = _newBufferSize;

		Key *_tempKeys;
		U *_tempValues;
		if (!(_tempKeys = new Key[_bufferSize]) || !(_tempValues = new U[_bufferSize]))
			throw std::bad_alloc();
		
		memcpy(_tempKeys, this->_keys, _size*sizeof(Key));
		memcpy(_tempValues, this->_values, _size*sizeof(U));
		delete[] _keys, _values;

		_keys = _tempKeys;
		_values = _tempValues;
		return 0;
	}

	template<typename Key, typename U>
	bool Dictionary<Key, U>::shrink() {
		Key *_tempKeys;
		U *_tempValues;
		if (!(_tempKeys = new Key[_size]) || !(_tempValues = new U[_size]))
			throw std::bad_alloc();
		
		memcpy(_tempKeys, this->_keys, _size*sizeof(Key));
		memcpy(_tempValues, this->_values, _size*sizeof(U));
		delete[] _keys, _values;

		_keys = _tempKeys;
		_values = _tempValues;
		_bufferSize = _size;
		return true;
	}

	template<typename Key, typename U>
	const size_t Dictionary<Key, U>::bufferSize() const {
		return this->_bufferSize;
	}

} // namespace cppit