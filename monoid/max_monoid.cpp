namespace max_monoid_n {
template<class T>
struct max_monoid {
	using monoid_type = T;
	T val;
	max_monoid(T v) : val(v) {}
	max_monoid() : val(numeric_limits<T>::min()) {}
	static max_monoid merge(const max_monoid& lhs, const max_monoid& rhs) {
		return max_monoid(max(lhs.val, rhs.val));
	}
};
}
using max_monoid_n::max_monoid;