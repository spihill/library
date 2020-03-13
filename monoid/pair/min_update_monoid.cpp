namespace min_update_monoid_n {
#include "../min_monoid.cpp"
#include "../update_monoid.cpp"
template<class T, class U = T, class NODE = min_monoid<T>, class LAZY = update_monoid<U>>
struct min_update_monoid {
	using Node = NODE;
	using Lazy = LAZY;
	static Node apply(const Node& lhs, const LAZY& rhs) {
		if (rhs.val.second) return lhs;
		return Node(rhs.val.first);
	}
	static Lazy propagate(const Lazy& lhs, int len) {
		return lhs;
	}
};
} // namespace min_update_monoid
using min_update_monoid_n::min_update_monoid;