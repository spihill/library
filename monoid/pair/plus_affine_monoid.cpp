namespace plus_affine_monoid_n {
#include "../plus_monoid.cpp"
#include "../affine_monoid.cpp"
template<class T, class U = T, class NODE = plus_monoid<T>, class LAZY = affine_monoid<U>>
struct plus_affine_monoid {
	using Node = NODE;
	using Lazy = LAZY;
	static Node apply(const Node& lhs, const LAZY& rhs) {
		return Node(lhs.val * rhs.val.first + rhs.val.second);
	}
	static Lazy propagate(const Lazy& lhs, int len) {
		return Lazy(make_pair(lhs.val.first, lhs.val.second * len));
	}
};
} // namespace plus_affine_monoid
using plus_affine_monoid_n::plus_affine_monoid;