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
  short int String::reserve(const size_t _newBufferSize) {
	if (_newBufferSize <= _bufferSize)
	  return 1; // Forbidden, data loss
	_bufferSize = _newBufferSize;
	if (!_string) {
	  return 0;
	}
	
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
} // namespace cppit
