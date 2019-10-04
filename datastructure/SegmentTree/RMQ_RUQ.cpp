template<class T, class U>
struct RMQ_RUQ {
	struct RMQ {
		const static T UNITY = numeric_limits<T>::max();
		T val;
		explicit RMQ(T v) : val(v) {}
		explicit RMQ() : val(UNITY) {}
		inline RMQ operator+(const RMQ& rhs) const {
			return RMQ(min(val, rhs.val));
		}
	};
	struct RUQ {
		const static U UNITY = numeric_limits<U>::min();
		U val;
		explicit RUQ(U v) : val(v) {}
		explicit RUQ() : val(UNITY) {}
		inline RUQ operator+(const RUQ& rhs) const {
			return RUQ(rhs.val);
		}
		inline RUQ operator*(const int len) const {
			return RUQ(*this);
		}
	};
	friend inline RMQ operator+(const RMQ& lhs, const RUQ& rhs) {
		return RMQ(rhs.val);
	}
	using NODE = RMQ; using NODE_T = T;
	using LAZY = RUQ; using LAZY_T = U;
};