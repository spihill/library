#include "is_monoid.cpp"
#include "is_addable.cpp"
#include "is_productable.cpp"
template <class T>
class has_Node {
	template <class U> static constexpr bool check(typename U::Node*) { return true;}
	template <class U> static constexpr bool check(...) { return false;}
public:
	static constexpr bool value = check<T>(nullptr);
};
template <class T>
class has_Lazy {
	template <class U> static constexpr bool check(typename U::Lazy*) { return true;}
	template <class U> static constexpr bool check(...) { return false;}
public:
	static constexpr bool value = check<T>(nullptr);
};
template<class MonoidPair>
struct monoid_pair_wrapper {
	using Node = typename MonoidPair::Node;
	using Lazy = typename MonoidPair::Lazy;
	static_assert(has_Node<MonoidPair>::value, "monoid_pair_wrapper : not have Node");
	static_assert(has_Lazy<MonoidPair>::value, "monoid_pair_wrapper : not have Lazy");
	static_assert(is_monoid_v<Node>, "monoid_pair_wrapper : Node is not monoid");
	static_assert(is_monoid_v<Lazy>, "monoid_pair_wrapper : Lazy is not monoid");
	static_assert(is_addable_v<Node, Lazy>, "monoid_pair_wrapper : cannot Node + Lazy");
	static_assert(is_productable_v<Lazy, int>, "monoid_pair_wrapper : cannot Lazy * int");
	struct monoid_pair_tag {};
};