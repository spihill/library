#include <bits/stdc++.h>
using namespace std;
namespace monoid_pair_n {
#include "../for_include/is_monoid.cpp"
template<class NODE, class LAZY>
struct monoid_pair_base {
	static_assert(is_monoid_v<NODE> && is_monoid_v<LAZY>, "");
	struct monoid_pair_tag {};
	struct Lazy_m : LAZY {
		using LAZY::LAZY;
		using LAZY::operator+;
		using LAZY::operator=;
		Lazy_m(LAZY x) : LAZY(x) {}
		Lazy_m() : LAZY() {}
	};
	struct Node_m : NODE {
		using NODE::NODE;
		using NODE::operator+;
		using NODE::operator=;
		Node_m(NODE x) : NODE(x) {}
		Node_m() : NODE() {}
	};
};
} // namespace monoid_pair_base
using monoid_pair_n::monoid_pair_base;
