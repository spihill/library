namespace plus_update_monoid_n {
#include "../plus_monoid.cpp"
#include "../update_monoid.cpp"
#include "../../for_include/monoid_pair_wrapper.cpp"
template<class T, class U = T, class NODE = plus_monoid<T>, class LAZY = update_monoid<U>>
struct plus_update_monoid_impl {
	struct Lazy;
	struct Node : public NODE {
		using NODE::operator+;
		using NODE::NODE;
		Node operator+(const Lazy& rhs) const {
			if (rhs.val.second) return *this;
			return Node(rhs.val.first);
		}
	};
	struct Lazy : public LAZY {
		using LAZY::operator+;
		using LAZY::LAZY;
		Lazy operator*(int len) const {
			if (this->val.second) return *this;
			return Lazy(this->val.first * len);
		}
	};
};
template<class T, class U = T, class Wrapper = monoid_pair_wrapper<plus_update_monoid_impl<T, U>>>
struct plus_update_monoid : Wrapper {
	using typename Wrapper::Node;
	using typename Wrapper::Lazy;
	using Wrapper::Wrapper;
};
} // namespace plus_update_monoid
using plus_update_monoid_n::plus_update_monoid;