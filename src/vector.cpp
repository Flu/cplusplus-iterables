#include "vector.hpp"

namespace cppit {
	template<typename T>
	std::ostream& operator<<(std::ostream &_os, const Vector<T> _output) {
		os << "[";
		for (size_t _index = 0ul; index < _output._size; index++)
			os << _output._vector[index] << ", ";
		os << "]";
		return os;
	}
}