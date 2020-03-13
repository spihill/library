namespace plus_plus_monoid_n {
#include "../plus_monoid.cpp"
template<class T, class U = T, class NODE = plus_monoid<T>, class LAZY = plus_monoid<U>>
struct plus_plus_monoid {
	using Node = NODE;
	using Lazy = LAZY;
	static Node apply(const Node& lhs, const LAZY& rhs) {
		return Node(lhs.val + rhs.val);
	}
	static Lazy propagate(const Lazy& lhs, int len) {
		return Lazy(lhs.val * len);
	}
};
} // namespace plus_plus_monoid
using plus_plus_monoid_n::plus_plus_monoid;