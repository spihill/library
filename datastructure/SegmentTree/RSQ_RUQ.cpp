template<class T, class U>
struct RSQ_RUQ {
	struct RSQ {
		T val;
		constexpr static T UNITY = 0;
		explicit RSQ(T v) : val(v) {}
		explicit RSQ() : val(UNITY) {}
		inline RSQ operator+(const RSQ& rhs) const {
			return RSQ(val + rhs.val);
		}
	};
	struct RUQ {
		U val;
		constexpr static U UNITY = numeric_limits<U>::min();
		explicit RUQ(U v) : val(v) {}
		explicit RUQ() : val(UNITY) {}
		inline RUQ operator+(const RUQ& rhs) const {
			return RUQ(rhs.val);
		}
		inline RUQ operator*(const int len) const {
			return RUQ(val * len);
		}
	};
	friend inline RSQ operator+(const RSQ& lhs, const RUQ& rhs) {
		return RSQ(rhs.val);
	}
	using NODE = RSQ; using NODE_T = T;
	using LAZY = RUQ; using LAZY_T = U;
};