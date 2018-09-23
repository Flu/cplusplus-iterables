namespace cppit {

	template<typename T>
	std::ostream& operator<<(std::ostream& _os, const Vector<T>& _output);

	template<typename T>
	class Vector {
	private:
		T* _vector;
		size_t _size, _bufferSize;

		inline void swap(T &a, T &b);
		size_t partition(
			const long long &_start,
			const long long &_end,
			std::function<bool(const T&, const T&)> _comp);
	public:
		Vector() {
			_vector = nullptr;
			_size = 0ul;
			_bufferSize = 20ul;
		}

		Vector(const size_t &_size, const T &&_rvalue) {
			_size = _size;
			_bufferSize = _size;
			_vector = new T[_bufferSize];
			for (size_t index; index < _size; index++)
				_vector[index] = _rvalue;
		}

		Vector(const T *_initArray, const size_t _initSize) {
			_bufferSize = 20ul;
			if (!_initArray)
				exit(1);

			_size = _initSize;

			if (_size > _bufferSize)
				_bufferSize = _size + 15ul;
			
			if (!(_vector = new T[_bufferSize]))
				exit(2);
			memmove(_vector, _initArray, _size*sizeof(T));
		}

		Vector(const Vector<T> &_dr) {
			_vector = nullptr;
			_size = 0ul;
			_bufferSize = 20ul;

			if (!_dr._vector)
				exit(1);
			_size = _dr._size;
			if (_size > _bufferSize)
				_bufferSize = _size + 15ul;
			
			if (!(_vector = new T[_bufferSize]))
				exit(2);
			memmove(_vector, _dr._vector, _size*sizeof(T));
		}

		const size_t length() const;
		short int push_back(const T &_elem);
		short int push_front(const T &_elem);
		short int insert(const T &_elem, const size_t &_pos);
		T pop();
		T& operator[](const long long &_pos);
		void swap(Vector<T> &_swapVector);
		bool operator==(const Vector<T> &_compareVector);
		inline short int operator+=(const T &_elem);
		Vector<T> operator=(const Vector<T> &_copyVector);
		Vector<T> sort(
			const long long &_start,
			const long long &_end,
			std::function<bool(const T&, const T&)> _comp = [](const T &a, const T &b) {
				if (a < b) return true;
				return false;
			});

		short int reserve(const size_t &_newBufferSize);
		bool shrink();
		size_t bufferSize() const;		

		friend std::ostream& operator<< <>(std::ostream &_os, const Vector &_output);

		~Vector() {
			if (_vector)
				delete[] _vector;
		}
	};

} // namespace cppit