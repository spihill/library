namespace unweighted_revedge_graph_n {
#include "RevEdgeGraph.cpp"
using u32 = uint_fast32_t;
struct Vertex {};
struct Edge {
	u32 to;
	Edge(u32 x) : to(x) {}
};
using UnWeightedRevEdgeGraph = RevEdgeGraph<Edge, Vertex>;
UnWeightedRevEdgeGraph make_unweighted_graph(u32 N) {
	return UnWeightedRevEdgeGraph(N);
}
}
using unweighted_revedge_graph_n::UnWeightedRevEdgeGraph;
using unweighted_revedge_graph_n::make_unweighted_graph;