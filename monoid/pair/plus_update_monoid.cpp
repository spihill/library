namespace plus_update_monoid_n {
#include "../plus_monoid.cpp"
#include "../update_monoid.cpp"
template<class T, class U = T, class NODE = plus_monoid<T>, class LAZY = update_monoid<U>>
struct plus_update_monoid {
	using Node = NODE;
	using Lazy = LAZY;
	static Node apply(const Node& lhs, const LAZY& rhs) {
		if (rhs.val.second) return lhs;
		return Node(rhs.val.first);
	}
	static Lazy propagate(const Lazy& lhs, int len) {
		if (lhs.val.second) return lhs;
		return Lazy(lhs.val.first * len);
	}
};
} // namespace plus_update_monoid
using plus_update_monoid_n::plus_update_monoid;