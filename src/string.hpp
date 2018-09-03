#include "cppit.hpp"

namespace cppit {
	class String {
	private:
		char* _string;
		size_t _size, _bufferSize; // _size includes '\0'

		bool isLower(const char _char) const;

  	public:
		String() {
		_string = nullptr;
	  	_size = 0u;
	  	_bufferSize = 20u;
  	}

		String(const char *_init) {
		  _bufferSize = 20u;
		  if (!_init)
				exit(1); // Failure to copy nullptr string
	    const char *_initPointer;
		  // Use pointer arithmetic to compute string size
		  for (_initPointer = _init; *_initPointer != '\0'; _initPointer++) {}
		  _size = _initPointer - _init + 1u;
		  if (_size >= _bufferSize) // Allocate for string size + '\0'
			_bufferSize = _size + 15u;
		  if (!(_string = new char[_bufferSize]))
			exit(2); // Bad alloc
			for (size_t index = 0u; index < _size; index++)
			_string[index] = _init[index];
		}

		String(const String &_dr) {
	  	_string = nullptr;
	  	_size = 0u;
	  	_bufferSize = 20u;
	  
	  	if (!_dr._string)
				exit(1);
	  	_size = _dr._size;
	  
	  	if (_dr._size >= _bufferSize)
				_bufferSize = _dr._size + 15u;
	  
	  	_string = new char[_bufferSize];
	  	for (size_t index = 0u; index < _size; index++)
			_string[index] = _dr._string[index];
		}

		size_t length() const;
		char& operator[](const size_t _index);
		String operator=(const String &_dr);
		bool operator==(const String &_obj) const;
		String operator+=(const String &_appendString);
		String append(const String &_appendString);
		String operator+(const String &_concat) const;
		String toLower() const;
		String toUpper() const;

		short int reserve(const size_t _newBufferSize);
		size_t bufferSize() const;
		bool shrink();

		~String() {
	  	if (_string)
				delete[] _string;
		}

  	friend std::ostream& operator<<(std::ostream &os, const String &string);
		friend std::istream& operator>>(std::istream &is, const String &string);
  };
}