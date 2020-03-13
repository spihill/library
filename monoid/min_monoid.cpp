namespace min_monoid_n {
template<class T>
struct min_monoid {
	using monoid_type = T;
	T val;
	min_monoid(T v) : val(v) {}
	min_monoid() : val(numeric_limits<T>::max()) {}
	static min_monoid merge(const min_monoid& lhs, const min_monoid& rhs) {
		return min_monoid(min(lhs.val, rhs.val));
	}
};
}
using min_monoid_n::min_monoid;