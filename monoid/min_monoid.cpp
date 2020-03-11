namespace min_monoid_n {
#include "../for_include/monoid_wrapper.cpp"
template<class T>
struct min_monoid_impl {
	T val;
	min_monoid_impl(T v) : val(v) {}
	min_monoid_impl() : val(numeric_limits<T>::max()) {}
	min_monoid_impl<T> operator+(const min_monoid_impl<T>& rhs) const {
		return min_monoid_impl(min(this->val, rhs.val));
	}
};
template<class T, class Impl = min_monoid_impl<T>, class Wrapper = monoid_wrapper<Impl, T>>
struct min_monoid : Wrapper {
	using Wrapper::Wrapper;
};
}
using min_monoid_n::min_monoid;