namespace min_update_monoid_n {
#include "../min_monoid.cpp"
#include "../update_monoid.cpp"
#include "../../for_include/monoid_pair_wrapper.cpp"
template<class T, class U = T, class NODE = min_monoid<T>, class LAZY = update_monoid<U>>
struct min_update_monoid_impl {
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
			return this->val.first;
		}
	};
};
template<class T, class U = T, class Wrapper = monoid_pair_wrapper<min_update_monoid_impl<T, U>>>
struct min_update_monoid : Wrapper {
	using typename Wrapper::Node;
	using typename Wrapper::Lazy;
	using Wrapper::Wrapper;
};
} // namespace min_update_monoid
using min_update_monoid_n::min_update_monoid;