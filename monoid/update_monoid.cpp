namespace update_monoid_n {
#include "../for_include/monoid.cpp"
template<class T>
struct update_monoid : public monoid_base<T> {
	using monoid = update_monoid;
	using monoid_base<T>::monoid_base;
	bool unit;
	update_monoid() : monoid_base<T>(T()), unit(true) {}
	monoid operator+(const monoid& rhs) const {
		if (rhs.unit) return *this;
		return rhs;
	}
};
}
using update_monoid_n::update_monoid;