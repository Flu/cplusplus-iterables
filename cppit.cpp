#include "cppit.hpp"

namespace cppit {

  std::ostream& operator<<(std::ostream &os, const String &string) {
    for (size_t index = 0u; index < string._size; index++)
      os << string._string[index];
    return os;
  }
  char& String::operator[](size_t index) {
    if (index < _size)
      return _string[index];
  }
  
} //namespace cppit
