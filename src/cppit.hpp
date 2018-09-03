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
	class Dictionary;
	class MultiDict;
	class Vector;
	class Tuple;
} // namespace cppit