#include "FlowEdge.cpp"
template<class F>
struct Graph {
	const int sz;
	Edges<F> e;
	Graph(int n) : sz(n), e(sz) {}
	// add_edge(from, to, cap)
	template<class... Args> void add_edge(int from, int to, F cap) {
		e.add_edge(from, to, cap, e[to].size());
		e.add_edge(to, from, 0, e[from].size()-1);
	}
	int size() {
		return sz;
	}
};