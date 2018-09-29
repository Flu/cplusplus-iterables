namespace cppit {

	template<typename Key, typename U>
	std::ostream& operator<<(std::ostream &_os, const Dictionary<Key, U> &_output);

	template<typename Key, typename U>
	class Dictionary {
		Key* _keys;
		U* _values;
		size_t _size, _bufferSize;

	public:
		Dictionary() {
			_keys = _values = nullptr;
			_size = 0ul;
			_bufferSize = 20ul;
		}

		explicit Dictionary(const Key &_initKey, const U &_initValue) {
			_bufferSize = 20ul;
			if (!(_keys = new Key[_bufferSize]) || !(_values = new U[_bufferSize]))
				throw std::bad_alloc();
			_keys[0] = _initKey;
			_values[0] = _initValue;
			_size = 1ul;
		}

		Dictionary(const Key *_initKeys, const U *_initValues, const size_t &_initSize) {
			if (!_initKeys || !_initValues)
				exit(1);
			Dictionary _temp(_initKeys[0], _initValues[0]);

			for (size_t index = 1ul; index < _initSize; index++) {
				if (_temp.hasKey(_initKeys[index]))
					throw std::bad_alloc();
				_temp[_initKeys[index]] = _initValues[index];
			}

			_bufferSize = 20ul;
			_size = _initSize;

			if (_size >= _bufferSize)
				_bufferSize = _size + 15ul;
			if (!(_keys = new Key[_bufferSize]) || !(_values = new U[_bufferSize]))
				throw std::bad_alloc();

			memcpy(_keys, _initKeys, _size*sizeof(Key));
			memcpy(_values, _initValues, _size*sizeof(U));
		}

		Dictionary(const Dictionary &_copyDict) : _size(_copyDict._size), _bufferSize(_copyDict._bufferSize) {
			_keys = nullptr;
			_values = nullptr;
			if (!(_keys = new Key[_bufferSize]) || !(_values = new U[_bufferSize]))
				throw std::bad_alloc();
			memcpy(_keys, _copyDict._keys, _size*sizeof(Key));
			memcpy(_values, _copyDict._values, _size*sizeof(U));
		}

		Dictionary<Key, U> operator=(const Dictionary<Key, U> &_copyDict);
		bool operator==(const Dictionary<Key, U> &_compare) const;
		bool operator!=(const Dictionary<Key, U> &_compare) const;
		bool hasKey(const Key &_key) const;
		U& operator[](const Key &_key); // Mutator
		const U& operator[](const Key &_key) const; // Accessor
		U& get(const Key &_key, const U& _default);
		bool deleteKey(const Key &_key);

		const size_t length() const;
		short int reserve(const size_t &_newBufferSize);
		bool shrink();
		const size_t bufferSize() const;

		Iterator<U> begin() {
			return Iterator(_values);
		}
		Iterator<U> end() {
			return Iterator(_values + this->length());
		}
		Iterator<Key> begin_keys() {
			return Iterator(_keys);
		}
		Iterator<Key> end_keys() {
			return Iterator(_keys + this->length());
		}

		~Dictionary() {
			if (_keys)
				delete[] _keys;
			if (_values)
				delete[] _values;
		}

		friend std::ostream& operator<< <>(std::ostream &_os, const Dictionary<Key, U> &_dict);
	};

} // namespace cppit