#include "vector.hpp"

namespace cppit {
	template<typename T>
	std::ostream& operator<<(std::ostream &_os, const Vector<T> _output) {
		_os << "[";
		for (size_t _index = 0ul; _index < _output._size; _index++)
			_os << _output._vector[index] << ", ";
		_os << "]";
		return _os;
	}
}