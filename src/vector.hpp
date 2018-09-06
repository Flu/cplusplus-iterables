namespace cppit {

	template<typename T>
	class Vector {
	private:
		T* _vector;
		size_t _size, _bufferSize;
	public:
		Vector() {
			_vector = nullptr;
			_size = 0ul;
			_bufferSize = 20ul;
		}

		Vector(T *_initArray) {
			_bufferSize = 20ul;
			if (!_initArray)
				exit(1);
			std::cout << "yeah";
			T* _initPointer;
			for (_initPointer = _initArray; !_initPointer; _initPointer++);
			_size  = _initPointer - _initArray;

			if (_size > _bufferSize)
				_bufferSize = _size + 15ul;
			_vector = _initArray;
			_initArray = nullptr;
		}

		~Vector() {
			if (_vector)
				delete[] _vector;
		}
	};

} // namespace cppit