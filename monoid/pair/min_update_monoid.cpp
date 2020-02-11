namespace min_update_monoid_n {
#include "../min_monoid.cpp"
#include "../update_monoid.cpp"
#include "../../for_include/monoid_pair.cpp"
template<class T, class U = T>
struct min_update_monoid : public monoid_pair_base<min_monoid<T>, update_monoid<U>> {
	using super = monoid_pair_base<min_monoid<T>, update_monoid<U>>;
	struct Lazy;
	struct Node : public super::Node {
		using super::Node::operator+;
		using super::Node::operator=;
		using super::Node::Node;
		Node(typename super::Node node) : super::Node(node) {}
		Node() : super::Node() {}
		Node operator+(const Lazy& rhs) const {
			return Node(rhs.val);
		}
	};
	struct Lazy : public super::Lazy {
		using super::Lazy::operator+;
		using super::Lazy::operator=;
		using super::Lazy::Lazy;
		Lazy operator*(int len) const {
			return Lazy(this->val);
		}
		bool is_unity() const {
			return this->unit;
		}
	};
};
} // namespace min_update_monoid_n
using min_update_monoid_n::min_update_monoid;