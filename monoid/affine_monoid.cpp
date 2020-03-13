namespace affine_monoid_n {
template<class T>
struct affine_monoid {
	using monoid_type = pair<T, T>;
	pair<T, T> val;
	affine_monoid() : affine_monoid(pair<T, T>(1, 0)) {}
	affine_monoid(pair<T, T> v) : val(v) {}
	affine_monoid(T f, T s) : val(f, s) {}
	static affine_monoid merge(const affine_monoid& lhs, const affine_monoid& rhs) {
		return affine_monoid(pair<T, T>(rhs.val.first * lhs.val.first, rhs.val.first * lhs.val.second + rhs.val.second));
	}
};
}
using affine_monoid_n::affine_monoid;