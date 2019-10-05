template<class T = long long, class U = T>
struct RSQ_slow {
	T val;
	explicit RSQ_slow(T v) : val(v) {}
	explicit RSQ_slow() : val() {}
	inline RSQ_slow operator+(const RSQ_slow& rhs) const {
		return RSQ_slow(val + rhs.val);
	}
	inline void assign(const U v) {
		val += v;
	}
	using NODE_T = T; using ASSIGN_T = U;
};