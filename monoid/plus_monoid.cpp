namespace plus_monoid_n {
template<class T>
struct plus_monoid {
	using monoid_type = T;
	T val;
	plus_monoid(T v) : val(v) {}
	plus_monoid() : val(0) {}
	static plus_monoid merge(const plus_monoid& lhs, const plus_monoid& rhs) {
		return plus_monoid(lhs.val + rhs.val);
	}
};
}
using plus_monoid_n::plus_monoid;