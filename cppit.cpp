#include "cppit.hpp"

namespace cppit {

  std::ostream& operator<<(std::ostream &os, const String &string) {
    for (size_t index = 0u; index < string._size; index++)
      os << string._string[index];
    return os;
  }
  std::istream& operator>>(std::istream &is, const String &string) {
	
  }
  char& String::operator[](const size_t index) {
    if (index < _size)
      return _string[index];
  }
  String String::operator=(const String &_dr) {
	if (!_dr._string)
	  exit(1);
	_size = _dr._size;
	
	if (_dr._size >= _bufferSize || _string == nullptr) {
	  _bufferSize = _dr._size + 15u;
	  _string = new char[_bufferSize];
	}

	for (size_t index = 0u; index < _size; index++)
	  _string[index] = _dr._string[index];
	return *this;
  }
  short int String::reserve(const size_t _newBufferSize) {
	if (_newBufferSize <= _bufferSize)
	  return 1; // Forbidden, data loss
	_bufferSize = _newBufferSize;
	
	char *temp = new char[_size];
	for (size_t index = 0u; index < _size; index++)
	  temp[index] = _string[index];
	
	delete[] _string;
	if (!(_string = new char[_bufferSize]))
	  return 2; // Bad alloc - not enough free memory or block too big
	
	for (size_t index = 0u; index < _size - 1u; index++)
	  _string[index] = temp[index];
	return 0;
  }
  String String::operator+=(const String &_dr) {
	if (!_dr._string)
	  exit(1); // Can't append null cppit::String
  }
} // namespace cppit
