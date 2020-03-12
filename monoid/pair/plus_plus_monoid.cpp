namespace plus_plus_monoid_n {
#include "../plus_monoid.cpp"
#include "../../for_include/monoid_pair_wrapper.cpp"
template<class T, class U = T, class NODE = plus_monoid<T>, class LAZY = plus_monoid<U>>
struct plus_plus_monoid_impl {
	struct Lazy;
	struct Node : public NODE {
		using NODE::operator+;
		using NODE::NODE;
		Node operator+(const Lazy& rhs) const {
			return Node(this->val + rhs.val);
		}
	};
	struct Lazy : public LAZY {
		using LAZY::operator+;
		using LAZY::LAZY;
		Lazy operator*(int len) const {
			return Lazy(this->val * len);
		}
	};
};
template<class T, class U = T, class Wrapper = monoid_pair_wrapper<plus_plus_monoid_impl<T, U>>>
struct plus_plus_monoid : Wrapper {
	using typename Wrapper::Node;
	using typename Wrapper::Lazy;
	using Wrapper::Wrapper;
};
} // namespace plus_plus_monoid
using plus_plus_monoid_n::plus_plus_monoid;