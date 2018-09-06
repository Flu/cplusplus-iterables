#include <iostream>
#include <functional>
#include <stdio.h>
#include <string.h>

namespace cppit {
  
  class Iterable {
  public:
	virtual void append(const int obj) = 0;
	virtual int pop() = 0;
	virtual size_t length() const = 0;
	virtual ~Iterable() {}
  };
  
  class String;
	template<typename T> class Vector;
	class Dictionary;
	class MultiDict;
	class Tuple;
} // namespace cppit

#ifndef _CPPIT_STRING
	#define _CPPIT_STRING
	#include "string.cpp"
#endif
#ifndef _CPPIT_VECTOR
	#define _CPPIT_VECTOR
	#include "vector.cpp"
#endif