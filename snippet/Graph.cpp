#include "Edge.cpp"
struct Graph {
	int sz;
	vector<vector<Edge>> e;
	Graph(int n) : sz(n), e(n) {}
	template<class... Args>
	inline void add_edge(int pos, Args... args) {
		e[pos].emplace_back(args...);
	}
	inline int size() {
		return sz;
	}
};