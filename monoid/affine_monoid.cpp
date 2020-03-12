namespace affine_monoid_n {
#include "../for_include/monoid_wrapper.cpp"
template<class T>
struct affine_monoid_impl {
	pair<T, T> val;
	affine_monoid_impl(pair<T, T> v) : val(v) {}
	affine_monoid_impl() : affine_monoid_impl(pair<T, T>(1, 0)) {}
	affine_monoid_impl<T> operator+(const affine_monoid_impl& rhs) const {
		return affine_monoid_impl(pair<T, T>(rhs.val.first * this->val.first, rhs.val.first * this->val.second + rhs.val.second));
	}
};
template<class T, class Impl = affine_monoid_impl<T>, class Wrapper = monoid_wrapper<Impl, pair<T, T>>>
struct affine_monoid : Wrapper {
	using Wrapper::Wrapper;
};
}
using affine_monoid_n::affine_monoid;

// namespace update_monoid_n {
// #include "../for_include/monoid_wrapper.cpp"
// template<class T>
// struct update_monoid_impl {
// 	pair<T, char> val;
// 	update_monoid_impl(T v) : val(v, 0) {}
// 	update_monoid_impl() : val(T(), 1) {}
// 	update_monoid_impl<T> operator+(const update_monoid_impl<T>& rhs) const {
// 		if (rhs.val.second) return *this;
// 		return rhs;
// 	}
// };
// template<class T, class Impl = update_monoid_impl<T>, class Wrapper = monoid_wrapper<Impl, T>>
// struct update_monoid : Wrapper {
// 	using Wrapper::Wrapper;
// };
// }
// using update_monoid_n::update_monoid;