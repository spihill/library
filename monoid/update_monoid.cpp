namespace update_monoid_n {
#include "../for_include/monoid_wrapper.cpp"
template<class T>
struct update_monoid_impl {
	pair<T, char> val;
	update_monoid_impl(T v) : val(v, 0) {}
	update_monoid_impl() : val(T(), 1) {}
	update_monoid_impl<T> operator+(const update_monoid_impl<T>& rhs) const {
		if (rhs.val.second) return *this;
		return rhs;
	}
};
template<class T, class Impl = update_monoid_impl<T>, class Wrapper = monoid_wrapper<Impl, T>>
struct update_monoid : Wrapper {
	using Wrapper::Wrapper;
};
}
using update_monoid_n::update_monoid;