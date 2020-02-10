namespace max_monoid_n {
#include "../for_include/monoid.cpp"
template<class T>
struct max_monoid : public monoid_base<T> {
	using monoid = max_monoid;
	using monoid_base<T>::monoid_base;
	max_monoid() : max_monoid(numeric_limits<T>::min()) {}
	monoid operator+(const monoid& rhs) const {
		return monoid(max(this->val, rhs.val));
	}
};
}
using max_monoid_n::max_monoid;