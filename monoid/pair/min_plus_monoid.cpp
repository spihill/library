namespace min_plus_monoid_n {
#include "../min_monoid.cpp"
#include "../plus_monoid.cpp"
template<class T, class U = T, class NODE = min_monoid<T>, class LAZY = plus_monoid<U>>
struct min_plus_monoid {
	using Node = NODE;
	using Lazy = LAZY;
	static Node apply(const Node& lhs, const LAZY& rhs) {
		return Node(lhs.val + rhs.val);
	}
	static Lazy propagate(const Lazy& lhs, int len) {
		return Lazy(lhs.val);
	}
};
} // namespace min_plus_monoid
using min_plus_monoid_n::min_plus_monoid;