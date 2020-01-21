template <class T>
class has_flow_graph_tag {
	template <class U, typename O = typename U::flow_graph_tag> static constexpr std::true_type check(int);
	template <class U> static constexpr std::false_type check(long);
public:
	static constexpr bool value = decltype(check<T>(0))::value;
};
template <class T> constexpr bool has_flow_graph_tag_v = has_flow_graph_tag<T>::value;