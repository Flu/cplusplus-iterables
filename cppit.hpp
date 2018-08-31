#include <iostream>
#include <functional>

namespace cppit {
  
  class Iterable {
  public:
	virtual void append(const int obj) = 0;
	virtual int pop() = 0;
	virtual size_t length() const = 0;
	virtual ~Iterable() {}
  };
  
  class String {
	char* _string;
	size_t _size;
	bool _isNull;
  public:
	String() {
	  _string = NULL;
	  _isNull = true;
	  _size = 0;
	}
	String(const char *_init) {
	  if (!_init)
		exit(1); //Failure to copy NULL string
      
	  const char *_initPointer;
	  // Use pointer arithmetic to compute string size
	  for (_initPointer = _init; *_initPointer != '\0'; _initPointer++) {}
	  _size = _initPointer - _init;
	  if (!(_string = new char[_size+1])) // Allocate for string size + '\0'
		exit(2); //Bad alloc
	  for (size_t index = 0u; index < _size; index++)
		_string[index] = _init[index];
	  _isNull = false;
	}
	String(const String &_dr) {
	  if (_dr._isNull == true)
		exit(1);
	  _size = _dr._size;
	  if (_isNull == false)
		delete[] _string;
	  
	  _string = new char[_size+1];
	  for (size_t index = 0u; index < _dr._size; index++)
		_string[index] = _dr._string[index];
    }
	size_t length() const;
	char& operator[](size_t index);
	~String() {
	  if (_string)
		delete[] _string;
	}
  	friend std::ostream& operator<<(std::ostream &os, const String &string);
  };
} //namespace cppit
