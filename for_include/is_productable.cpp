namespace is_productable_n {
template <class T1, class T2 = T1>
class is_productable {
	template <class U1, class U2> static constexpr auto check(U1*, U2*) -> decltype(
		declval<U1>() * declval<U2>(), true_type()
	);
	template <class U1, class U2> static constexpr auto check(...) -> false_type;
public:
	static constexpr bool value = decltype(check<T1, T2>(nullptr, nullptr))::value;
};
template <class T, class U = T>
constexpr bool is_productable_v = is_productable<T, U>::value;
} // namespace is_productable_n
using is_productable_n::is_productable;
using is_productable_n::is_productable_v;