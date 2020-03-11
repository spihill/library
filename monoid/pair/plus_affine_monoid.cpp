namespace plus_affine_monoid_n {
#include "../affine_monoid.cpp"
#include "../plus_monoid.cpp"
#include "../../for_include/monoid_pair.cpp"
template<class T, class U = T>
struct plus_affine_monoid : public monoid_pair_base<plus_monoid<T>, affine_monoid<U>> {
	using super = monoid_pair_base<plus_monoid<T>, affine_monoid<U>>;
	struct Lazy;
	struct Node : public super::Node {
		using super::Node::operator+;
		using super::Node::Node;
		Node operator+(const Lazy& rhs) const {
			return Node(this->val * rhs.val.first + rhs.val.second);
		}
	};
	struct Lazy : public super::Lazy {
		using super::Lazy::operator+;
		using super::Lazy::operator=;
		using super::Lazy::Lazy;
		inline Lazy operator*(int len) const {
			return Lazy(make_pair(this->val.first, this->val.second * len));
		}
	};
};
} // namespace plus_affine_monoid_n
using plus_affine_monoid_n::plus_affine_monoid;