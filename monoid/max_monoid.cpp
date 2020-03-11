namespace max_monoid_n {
#include "../for_include/monoid_wrapper.cpp"
template<class T>
struct max_monoid_impl {
	T val;
	max_monoid_impl(T v) : val(v) {}
	max_monoid_impl() : val(numeric_limits<T>::min()) {}
	max_monoid_impl<T> operator+(const max_monoid_impl<T>& rhs) const {
		return max_monoid_impl(max(this->val, rhs.val));
	}
};
template<class T, class Impl = max_monoid_impl<T>, class Wrapper = monoid_wrapper<Impl, T>>
struct max_monoid : Wrapper {
	using Wrapper::Wrapper;
};
}
using max_monoid_n::max_monoid;