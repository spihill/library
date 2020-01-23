namespace unweighted_graph_n {
#include "Graph.cpp"
using u32 = uint_fast32_t;
struct Vertex {};
struct Edge {
	u32 to;
	Edge(u32 x) : to(x) {}
};
using UnWeightedGraph = Graph<Edge, Vertex>;
UnWeightedGraph make_unweighted_graph(u32 N) {
	return UnWeightedGraph(N);
}
}
using unweighted_graph_n::UnWeightedGraph;
using unweighted_graph_n::make_unweighted_graph;