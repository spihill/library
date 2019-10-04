template<class T, class U>
struct RMQ_RAQ {
	struct RMQ {
		const static T UNITY = numeric_limits<T>::max();
		T val;
		explicit RMQ(T v) : val(v) {}
		explicit RMQ() : val(UNITY) {}
		inline RMQ operator+(const RMQ& rhs) const {
			return RMQ(min(val, rhs.val));
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
			return RAQ(*this);
		}
	};
	friend inline RMQ operator+(const RMQ& lhs, const RAQ& rhs) {
		return RMQ(lhs.val + rhs.val);
	}
	using NODE = RMQ; using NODE_T = T;
	using LAZY = RAQ; using LAZY_T = U;
};