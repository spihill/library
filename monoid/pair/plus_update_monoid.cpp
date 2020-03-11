namespace plus_update_monoid_n {
#include "../plus_monoid.cpp"
#include "../update_monoid.cpp"
#include "../../for_include/monoid_pair.cpp"
template<class T, class U = T>
struct plus_update_monoid : public monoid_pair_base<plus_monoid<T>, update_monoid<U>> {
	using super = monoid_pair_base<plus_monoid<T>, update_monoid<U>>;
	struct Lazy;
	struct Node : public super::Node {
		using super::Node::operator+;
		using super::Node::Node;
		inline Node operator+(const Lazy& rhs) const {
			if (rhs.val.second) return *this;
			return Node(rhs.val.first);
		}
	};
	struct Lazy : public super::Lazy {
		using super::Lazy::operator+;
		using super::Lazy::Lazy;
		inline Lazy operator*(int len) const {
			if (this->val.second) return *this;
			return Lazy(this->val.first * len);
		}
	};
};
} // namespace plus_update_monoid
using plus_update_monoid_n::plus_update_monoid;