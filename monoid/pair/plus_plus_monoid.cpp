namespace plus_plus_monoid_n {
#include "../plus_monoid.cpp"
#include "../../for_include/monoid_pair.cpp"
template<class T, class U = T>
struct plus_plus_monoid : public monoid_pair_base<plus_monoid<T>, plus_monoid<U>> {
	using super = monoid_pair_base<plus_monoid<T>, plus_monoid<U>>;
	struct Lazy;
	struct Node : public super::Node {
		using super::Node::operator+;
		using super::Node::operator=;
		using super::Node::Node;
		Node(typename super::Node node) : super::Node(node) {}
		Node() : super::Node() {}
		Node operator+(const Lazy& rhs) const {
			return Node(this->val + rhs.val);
		}
	};
	struct Lazy : public super::Lazy {
		using super::Lazy::operator+;
		using super::Lazy::operator=;
		using super::Lazy::Lazy;
		Lazy operator*(int len) const {
			return Lazy(this->val * len);
		}
		bool is_unity() const {
			return this->val == T();
		}
	};
};
} // namespace plus_plus_monoid_n
using plus_plus_monoid_n::plus_plus_monoid;