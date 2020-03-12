namespace min_plus_monoid_n {
#include "../min_monoid.cpp"
#include "../plus_monoid.cpp"
#include "../../for_include/monoid_pair_wrapper.cpp"
template<class T, class U = T, class NODE = min_monoid<T>, class LAZY = plus_monoid<U>>
struct min_plus_monoid_impl {
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
			return Lazy(this->val);
		}
	};
};
template<class T, class U = T, class Wrapper = monoid_pair_wrapper<min_plus_monoid_impl<T, U>>>
struct min_plus_monoid : Wrapper {
	using typename Wrapper::Node;
	using typename Wrapper::Lazy;
	using Wrapper::Wrapper;
};
} // namespace min_plus_monoid
using min_plus_monoid_n::min_plus_monoid;