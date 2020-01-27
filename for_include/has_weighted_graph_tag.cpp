template <class T>
class has_weighted_graph_tag {
	template <class U> static constexpr std::true_type check(typename U::weighted_graph_tag*);
	template <class U> static constexpr std::false_type check(...);
public:
	static constexpr bool value = decltype(check<T>(nullptr))::value;
};
template <class T> constexpr bool has_weighted_graph_tag_v = has_weighted_graph_tag<T>::value;