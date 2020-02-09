namespace affine_monoid_n {
#include "../for_include/monoid.cpp"
template<class T>
struct affine_monoid : public monoid_base<pair<T, T>> {
	using monoid = affine_monoid;
	using monoid_base<pair<T, T>>::monoid_base;
	affine_monoid() : affine_monoid(pair<T, T>(1, 0)) {}
	monoid operator+(const monoid& rhs) const {
		return monoid(pair<T, T>(rhs.val.first * this->val.first, rhs.val.first * this->val.second + rhs.val.second));
	}
};
}
using affine_monoid_n::affine_monoid;