namespace min_monoid_n {
#include "../for_include/monoid.cpp"
template<class T>
struct min_monoid : public monoid_base<T> {
	using monoid = min_monoid;
	using monoid_base<T>::monoid_base;
	min_monoid() : min_monoid(numeric_limits<T>::max()) {}
	monoid operator+(const monoid& rhs) const {
		return monoid(min(this->val, rhs.val));
	}
};
}
using min_monoid_n::min_monoid;