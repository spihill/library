template<class T = long long, class U = T>
struct RSQ {
	T val;
	const static T UNITY = 0;
	const static U DAMMY = 0;
	explicit RSQ(T v) : val(v) {}
	explicit RSQ() : val(UNITY) {}
	inline RSQ operator+(const RSQ& rhs) const {
		return RSQ(val + rhs.val);
	}
	inline void assign(const U v) {
		val += v;
	}
};