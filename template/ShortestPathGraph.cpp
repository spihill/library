namespace shortest_path_graph_n {
#include "Graph.cpp"
using u32 = uint_fast32_t;
using i64 = int_fast64_t;
template<class WEIGHT>
struct Vertex {
	WEIGHT dist;
	bool valid;
};
template<class WEIGHT>
struct Edge {
	u32 to;
	WEIGHT weight;
	Edge(u32 x, WEIGHT w) : to(x), weight(w) {}
};
template<class WEIGHT>
struct ShortestPathGraph : Graph<Edge<WEIGHT>, Vertex<WEIGHT>> {
	struct shortest_path_graph_tag {};
	ShortestPathGraph(u32 N) : Graph<Edge<WEIGHT>, Vertex<WEIGHT>>(N) {}
	WEIGHT& dist(u32 i) {return this->v[i].dist;}
	bool& valid(u32 i) {return this->v[i].valid;}
	using WEIGHT_TYPE = WEIGHT;
};
template<class WEIGHT = long long>
ShortestPathGraph<WEIGHT> make_shortest_path_graph(u32 N) {
	return move(ShortestPathGraph<WEIGHT>(N));
}
} // shortest_path_graph_n
using shortest_path_graph_n::ShortestPathGraph;
using shortest_path_graph_n::make_shortest_path_graph;
