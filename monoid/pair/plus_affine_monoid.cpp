namespace plus_affine_monoid_n {
#include "../plus_monoid.cpp"
#include "../affine_monoid.cpp"
#include "../../for_include/monoid_pair_wrapper.cpp"
template<class T, class U = T, class NODE = plus_monoid<T>, class LAZY = affine_monoid<U>>
struct plus_affine_monoid_impl {
	struct Lazy;
	struct Node : public NODE {
		using NODE::operator+;
		using NODE::NODE;
		Node operator+(const Lazy& rhs) const {
			return Node(this->val * rhs.val.first + rhs.val.second);
		}
	};
	struct Lazy : public LAZY {
		using LAZY::operator+;
		using LAZY::LAZY;
		inline Lazy operator*(int len) const {
			return Lazy(make_pair(this->val.first, this->val.second * len));
		}
	};
};
template<class T, class U = T, class Wrapper = monoid_pair_wrapper<plus_affine_monoid_impl<T, U>>>
struct plus_affine_monoid : Wrapper {
	using typename Wrapper::Node;
	using typename Wrapper::Lazy;
	using Wrapper::Wrapper;
};
} // namespace plus_update_monoid
using plus_affine_monoid_n::plus_affine_monoid;