template<class T = long long, class U = T>
struct RMQ {
	T val;
	constexpr static T UNITY = numeric_limits<T>::max();
	explicit RMQ(T v) : val(v) {}
	explicit RMQ() : val(UNITY) {}
	inline RMQ operator+(const RMQ& rhs) const {
		return RMQ(min(val, rhs.val));
	}
	inline void assign(const U v) {
		val = v;
	}
	using NODE_T = T; using ASSIGN_T = U;
};