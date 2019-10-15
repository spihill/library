namespace edge_2d_n {
#include "WeightedEdge.cpp"
}
namespace edge_1d_n {
#include "Weighted1DEdge.cpp"
}
template<class W>
struct Graph {
	const int sz;
	edge_2d_n::Edges<W> e;
	edge_1d_n::Edges<W> edges;
	Graph(int n) : sz(n), e(sz), edges() {}
	template<class... Args> void add_edge(int u, int v, Args... args) {
		e.add_edge(u, v, args...);
		edges.add_edge(u, v, args...);
	}
	int size() {
		return sz;
	}
};