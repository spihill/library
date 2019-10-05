template<class T = long long, class U = T>
struct RMQ_slow {
	T val;
	explicit RMQ_slow(T v) : val(v) {}
	explicit RMQ_slow() : val() {}
	inline RMQ_slow operator+(const RMQ_slow& rhs) const {
		return RMQ_slow(min(val, rhs.val));
	}
	inline void assign(const U v) {
		val = v;
	}
	using NODE_T = T; using ASSIGN_T = U;
};