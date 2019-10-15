#include "WeightedEdge.cpp"
template<class W>
struct Graph {
	const int sz;
	Edges<W> e;
	Graph(int n) : sz(n), e(sz) {}
	template<class... Args> void add_edge(int u, int v, Args... args) {
		e.add_edge(u, v, args...);
	}
	int size() {
		return sz;
	}
};