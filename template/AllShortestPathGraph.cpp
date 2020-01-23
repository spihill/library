namespace all_shortest_path_graph_n {
#include "Graph.cpp"
using u32 = uint_fast32_t;
using i64 = int_fast64_t;
struct Vertex {};
template<class WEIGHT>
struct Edge {
	u32 to;
	WEIGHT weight;
	Edge(u32 x, WEIGHT w) : to(x), weight(w) {}
};
template<class WEIGHT>
struct AllShortestPathGraph : Graph<Edge<WEIGHT>, Vertex> {
	struct all_shortest_path_graph_tag {};
	vector<vector<WEIGHT>> dist;
	vector<vector<bool>> valid;
	AllShortestPathGraph(u32 N) : Graph<Edge<WEIGHT>, Vertex>(N), dist(N, vector<WEIGHT>(N)), valid(N, vector<bool>(N)) {}
	using WEIGHT_TYPE = WEIGHT;
};
template<class WEIGHT = long long>
AllShortestPathGraph<WEIGHT> make_all_shortest_path_graph(u32 N) {
	return move(AllShortestPathGraph<WEIGHT>(N));
}
} // all_shortest_path_graph_n
using all_shortest_path_graph_n::AllShortestPathGraph;
using all_shortest_path_graph_n::make_all_shortest_path_graph;
