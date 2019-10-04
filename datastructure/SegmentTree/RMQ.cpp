template<class T = long long, class U = T>
struct RMQ {
	T val;
	const static T UNITY = numeric_limits<T>::max();
	const static U DAMMY = 0;
	explicit RMQ(T v) : val(v) {}
	explicit RMQ() : val(UNITY) {}
	inline RMQ operator+(const RMQ& rhs) const {
		return RMQ(min(val, rhs.val));
	}
	inline void assign(const U v) {
		val = v;
	}
};