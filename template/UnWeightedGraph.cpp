template<class VertexType = long long>
struct UnWeightedGraph {
	template<class T> static enable_if_t<is_integral<T>::value, size_t>  index(T x) {return x;}
	template<class T> static enable_if_t<is_integral<T>::value, T>     restore(T x) {return x;}
	template<class T> static enable_if_t<!is_integral<T>::value, size_t> index(T x) {return x.index();}
	template<class T> static enable_if_t<!is_integral<T>::value, T>    restore(T x) {return x.restore();}
	struct graph_tag {};
	vector<vector<size_t>> edge;
	const int n;
	UnWeightedGraph(size_t N) : edge(N), n(N) {}
	template<class T, class U> void add_edge(T from, U to) {
		edge[index(from)].push_back(index(to));
	}
	size_t size() const {
		return n;
	}
	void clear() {
		edge.clear();
	}
	using vertex_type = VertexType;
};
template<class T = long long>
UnWeightedGraph<T> make_unweighted_graph(size_t N) {
	return move(UnWeightedGraph<T>(N));
}