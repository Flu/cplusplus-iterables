namespace cppit {

	template<class... Args>
	class Tuple {
	public:
		void print() {
			std::cout << std::endl;
		}
		void operator[](long index) {}
	};

	template<class T, class... Args>
	class Tuple<T, Args...> : public Tuple<Args...> {
		T elem;
	public:
		Tuple(T init, Args... args) : Tuple<Args...>(args...) {
			this->elem = init;
		}

		T& operator[](const long &index) {
			if (index == 0)
				return elem;
			Tuple<Args...>::operator[](index - 1);
		}

		void print() {
			std::cout << elem << ", ";
			Tuple<Args...>::print();
		}
	};

} // namespace cppit