template<class T, class U>
struct RSQ_RAQ {
	struct RSQ {
		const static T UNITY = 0;
		T val;
		explicit RSQ(T v) : val(v) {}
		explicit RSQ() : val(UNITY) {}
		inline RSQ operator+(const RSQ& rhs) const {
			return RSQ(val + rhs.val);
		}
	};
	struct RAQ {
		const static U UNITY = 0;
		U val;
		explicit RAQ(U v) : val(v) {}
		explicit RAQ() : val(UNITY) {}
		inline RAQ operator+(const RAQ& rhs) const {
			return RAQ(val + rhs.val);
		}
		inline RAQ operator*(const int len) const {
			return RAQ(val * len);
		}
	};
	friend RSQ operator+(const RSQ& lhs, const RAQ& rhs) {
		return RSQ(lhs.val + rhs.val);
	}
	using NODE = RSQ; using NODE_T = T;
	using LAZY = RAQ; using LAZY_T = U;
};