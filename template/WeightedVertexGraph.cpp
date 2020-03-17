namespace weighted_vertex_graph_n {
template<class EDGE, class VERTEX>
struct Graph {
	using u32 = uint_fast32_t;
	using i32 = int_fast32_t;
	using u64 = uint_fast64_t;
	struct graph_tag {};
	const u32 n;
	vector<vector<EDGE>> e;
	vector<VERTEX> v;
	vector<u64> idx;
	Graph(u32 N) : n(N), e(n), v(n) {}
	template<class...  Args> void add_edge(u32 from, u32 to, Args... args) {
		idx.push_back((static_cast<u64>(from) << 32) | e[from].size());
		e[from].emplace_back(to, args...);
	}
	u32 size() const {return n;}
	using EDGE_TYPE = EDGE;
	using VERTEX_TYPE = VERTEX;
};
using u32 = uint_fast32_t;
template<class T>
struct Vertex {
	T val;
};
struct Edge {
	u32 to;
	Edge(u32 x) : to(x) {}
};
template<class T> using WeightedVertexGraph = Graph<Edge, Vertex<T>>;

template<class T>
WeightedVertexGraph<T> make_weighted_vertex_graph(u32 N) {
	return WeightedVertexGraph<T>(N);
}
}
using weighted_vertex_graph_n::WeightedVertexGraph;
using weighted_vertex_graph_n::make_weighted_vertex_graph;