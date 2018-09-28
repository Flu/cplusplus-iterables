#include "vector.hpp"

namespace cppit {

	template<typename T>
	std::ostream& operator<<(std::ostream &_os, const Vector<T> &_output) {
		_os << "[";
		for (size_t _index = 0ul; _index < _output._size; _index++)
			_os << _output._vector[_index] << ", ";
		_os << "]" << std::endl;
		return _os;
	}

	template<typename T>
	bool Vector<T>::operator==(const Vector<T> &_compareVector) const {
		if (this->_size != _compareVector._size)
			return false;
		for (size_t _index = 0ul; _index < _size; _index++) {
			if (_vector[_index] != _compareVector[_index])
				return false;
		}
		return true;
	}

	template<typename T>
	inline short int Vector<T>::operator+=(const T &_elem) {
		return this->push_back(_elem);
	}

	template<typename T>
	Vector<T> Vector<T>::operator=(const Vector<T> &_copyVector) {
		if (_copyVector._vector == nullptr)
			exit(1); // Won't copy uninitialized vector - preventing undefined behaviour
		if (_vector)
			delete[] _vector;
		_vector = nullptr;
		_size = _copyVector._size;
		_bufferSize = _copyVector._bufferSize;
		
		if (!(_vector = new T[_bufferSize]))
			exit(2);
		memcpy(_vector, _copyVector._vector, _size*sizeof(T));
		return *this;
	}

	template<typename T>
	inline void Vector<T>::swap(T& a, T& b) {
		T aux = a;
		a = b;
		b = aux;
	}

	template<typename T>
	Vector<T> Vector<T>::operator()(const size_t &_startSlice, const size_t &_stopSlice) const {
		if (_startSlice >= _stopSlice || _stopSlice >= _size) {
			throw "Invalid_Indices";
			exit(1);
		}
		size_t _slice = _stopSlice - _startSlice;

		Vector *_sliceVector = new Vector(_vector + _startSlice, _slice);
		return *_sliceVector;
	}

	template<typename T>
	size_t Vector<T>::partition(const long long &_start, const long long &_end, std::function<bool(const T&, const T&)> _comp) {
		size_t _pivot = _vector[_end], indexI = _start;
		for (size_t indexJ = _start; indexJ < _end; indexJ++) {
			if (_comp(_vector[indexJ], _pivot)) {
				swap(_vector[indexI], _vector[indexJ]);
				indexI++;
			}
		}
		swap(_vector[indexI], _vector[_end]);
		return indexI;
	}

	template<typename T>
	Vector<T> Vector<T>::sort(const long long &_start, const long long &_end, std::function<bool(const T&, const T&)> _comp) {
		if (_start >= _end)
			return *this;
		if (_end - _start <= 10l)
			return this->insertSort(_start, _end, _comp);

		size_t _pivot = this->partition(_start, _end, _comp);
		this->sort(_start, _pivot - 1, _comp);
		this->sort(_pivot + 1, _end, _comp);
		return *this;
	}

	template<typename T>
	Vector<T> Vector<T>::insertSort(const long long &_start, const long long &_end, std::function<bool(const T&, const T&)> _comp) {
		size_t _tempStart = _start;
		for (long long _index = _start + 1; _index <= _end; _index++) {
			for (long long _itr = _index - 1; _itr >= _start; _itr--) {
				if (!_comp(_vector[_itr],_vector[_itr+1])) {
					swap(_vector[_itr], _vector[_itr+1]);
					continue;
				}
				break;
			}
		}
		return *this;
	}

	template<typename T>
	short int Vector<T>::reserve(const size_t &_newBufferSize) {
		if (_newBufferSize <= _bufferSize)
			return 1; // Loss of data, forbidden
		_bufferSize = _newBufferSize;

		T *_temp;
		if (!(_temp = new T[_newBufferSize]))
			return 2; //Bad allocation

		memcpy(_temp, this->_vector, _size*sizeof(T));
		delete[] _vector;

		_vector = _temp;
		return 0;
	}

	template<typename T>
	size_t Vector<T>::bufferSize() const {
		return this->_bufferSize;
	}

	template<typename T>
	bool Vector<T>::shrink() {
		T *_temp;
		if (!(_temp = new T[_size]))
			return false; // Bad allocation
		memcpy(_temp, _vector, _size*sizeof(T));

		delete[] _vector;
		_vector = _temp;
		_bufferSize = _size;

		return true; // Return succesfully
	}

	template<typename T>
	short int Vector<T>::push_back(const T &_elem) {
		if (_size + 1 > _bufferSize)
			if(reserve(_bufferSize + 20ul))
				return 1;
		
		_vector[_size] = _elem;
		_size++;
		return 0;
	}

	template<typename T>
	short int Vector<T>::push_front(const T &_elem) {
		if (++_size > _bufferSize)
			if (reserve(_bufferSize + 20ul))
				return 1;
		for (size_t _index = _size - 1ul; _index > 0ul; _index--)
			_vector[_index] = _vector[_index - 1ul];
		_vector[0] = _elem;
		return 0;
	}

	template<typename T>
	short int Vector<T>::insert(const T &_elem, const size_t &_pos) {
		if (_pos > _size)
			return 1; // Space not accesible by user
		if (++_size > _bufferSize)
			this->reserve(_bufferSize + 15ul);

		for (size_t _index = _size - 1ul; _index > _pos; _index--) {
			_vector[_index] = _vector[_index - 1ul];
		}
		_vector[_pos] = _elem;
		return 0;
	}

	template<typename T>
	T Vector<T>::pop() {
		if (_size == 0ul)
			exit(1);
		_size--;
		return _vector[_size];
	}

	template<typename T>
	T& Vector<T>::operator[](const long long &_pos) {
		if (_pos > (long)(_size - 1) || _pos < (long)-_size) {
			exit(1); // Not accessible
		}
		if (_pos < 0) {
			return this->_vector[_size + _pos];
		}
		return this->_vector[_pos];
	}

	template<typename T>
	void Vector<T>::swap(Vector<T> &_swapVector) {
		T* _temp = this->_vector;
		this->_vector = _swapVector._vector;
		_swapVector._vector = _temp;
		size_t _tempSize = this->_bufferSize;
		this->_bufferSize = _swapVector._bufferSize;
		_swapVector._bufferSize = _tempSize;
		_tempSize = this->_size;
		this->_size = _swapVector._size;
		_swapVector._size = _tempSize;
		_temp = nullptr;
	}

	template<typename T>
	const size_t Vector<T>::length() const {
		return this->_size;
	}

} // namespace cppit