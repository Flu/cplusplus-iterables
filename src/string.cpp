#include "string.hpp"

namespace cppit {

  std::ostream& operator<<(std::ostream &os, const String &string) {
    for (size_t index = 0ul; index < string._size; index++)
      os << string._string[index];
    return os;
  }

  char& String::operator[](const size_t index) {
  	if (index < _size)
  	  return _string[index];
		exit(1); // Out-of-bounds index	
  }

  String String::operator=(const String &_dr) {
	if (!_dr._string)
	  exit(1);
	_size = _dr._size;
	
	if (_dr._size >= _bufferSize || _string == nullptr) {
	  _bufferSize = _dr._size + 15ul;
	  _string = new char[_bufferSize];
	}

	for (size_t index = 0ul; index < _size; index++)
	  _string[index] = _dr._string[index];
	return *this;
  }

  short int String::reserve(const size_t _newBufferSize) {
		if (_newBufferSize <= _bufferSize)
	  	return 1; // Forbidden, data loss
		_bufferSize = _newBufferSize;

		char *_temp;
		if (!(_temp = new char[_newBufferSize]))
			return 2;
		memcpy(_temp, _string, _size);
		delete[] _string;

		_string = _temp;
		return 0;
  }

	bool String::operator==(const String &_obj) const {
		if (_size != _obj._size)
			return false;
		return memcmp(_string, _obj._string, _size) == 0 ? true : false;
	}

  String String::operator+=(const String &_appendString) {
		if (!_appendString._string)
	  	exit(1); // Can't append null cppit::String
	
		if (_size + _appendString._size > _bufferSize)
	  	reserve(_size + _appendString._size + 15ul);

		memcpy(_string + _size - 1, _appendString._string, _appendString._size);

		_size += _appendString._size - 1;
		return *this;
	}

	String String::append(const String &_appendString) {
		return this->operator+=(_appendString);
	}

	String String::operator+(const String &_concat) const {
		if (!_concat._string)
			exit(1);

		String _temp = *this;
		if (_temp._size + _concat._size > _temp._bufferSize)
			_temp.reserve(_temp._size + _concat._size + 15ul);

		memcpy(_temp._string + _temp._size - 1ul, _concat._string, _concat._size);

		_temp._size += _concat._size;
		return _temp;
	}

	size_t String::bufferSize() const {
		return this->_bufferSize;
	}

	bool String::shrink() {
		char *_temp;
		if (!(_temp = new char[_size]))
			return false;
		memcpy(_temp, _string, _size);

		delete[] _string;
		_string = _temp;
		_bufferSize = _size;

		return true;
	}

	String String::toLower() const {
		String _temp = *this;
		for (char *_char = _temp._string; _char < _temp._string + _temp._size - 1; _char++) {
			if (*_char >= 65 && *_char <= 90)
				*_char += 32;
		}
		return _temp;
	}

	String String::toUpper() const {
		String _temp = *this;
		for (char *_char = _temp._string; _char < _temp._string + _temp._size - 1; _char++) {
			if (*_char >= 97 && *_char <= 122)
				*_char -= 32;
		}
		return _temp;
	}

	String String::reverse() const {
		String _temp = *this;
		for (size_t _index = 0ul; _index < _temp._size; _index++) {
			_temp._string[_index] = this->_string[_size - _index - 1];
		}
		return _temp;
	}

	size_t String::query(const String &_substr) const {
		if (this->_size == 0ul || _substr._size == 0ul || _size < _substr._size)
			return 800;
		std::cout << "===" << _size << " " << _substr._size << "===" << std::endl;
		bool _foundSubString;

		for (size_t _index = 0ul; _index < _size - 1; _index++) {
			_foundSubString = true;
			std::cout << _index << " " << _string[_index] << " " << _substr._string[_index] << std::endl;
			if (_string[_index] == _substr._string[_index] || (_index + _substr._size < _size)) {
				for (size_t _it1 = _index, _it2 = 0ul; _it2 < _substr._size - 1; _it1++, _it2++) {
					if (_string[_it1] != _substr._string[_it2])
						_foundSubString = false;
				}
			}
			if (_foundSubString == true)
				return _index;
		}
		return 900;
	}
} // namespace cppit
