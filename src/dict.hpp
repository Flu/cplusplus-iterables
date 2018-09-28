namespace cppit {

	template<typename T, typename U>
	class Dictionary {
		public:
		T* _keys;
		U* _values;
		size_t _size, _bufferSize;

	public:
		Dictionary() {
			_keys = _values = nullptr;
			_size = 0ul;
			_bufferSize = 20ul;
		}

		explicit Dictionary(const T &_initKey, const U &_initValue) {
			_bufferSize = 20ul;
			if (!(_keys = new T[_bufferSize]) || !(_values = new U[_bufferSize]))
				throw std::bad_alloc();
			_keys[0] = _initKey;
			_values[0] = _initValue;
			_size = 1ul;
		}

		explicit Dictionary(const T *_initKeys, const U *_initValues, const size_t &_initSize) {
			if (!_initKeys || !_initValues)
				exit(1);
			_bufferSize = 20ul;
			_size = _initSize;
			if (_size >= _bufferSize)
				_bufferSize = _size + 15ul;
			if (!(_keys = new T[_bufferSize]) || !(_values = new U[_bufferSize]))
				throw std::bad_alloc();
			memcpy(_keys, _initKeys, _size*sizeof(T));
			memcpy(_values, _initValues, _size*sizeof(U));
		}

		Dictionary(const Dictionary &_copyDict) : _size(_copyDict._size), _bufferSize(_copyDict._bufferSize) {
			_keys = nullptr;
			_values = nullptr;
			if (!(_keys = new T[_bufferSize]) || !(_values = new U[_bufferSize]))
				throw std::bad_alloc();
			memcpy(_keys, _copyDict._keys, _size*sizeof(T));
			memcpy(_values, _copyDict._values, _size*sizeof(U));
		}

		~Dictionary() {
			if (_keys)
				delete[] _keys;
			if (_values)
				delete[] _values;
		}
	};

} // namespace cppit