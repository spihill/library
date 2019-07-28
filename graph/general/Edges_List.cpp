template<class Edge>
struct Edges_List {
	vector<vector<Edge>> E;
	int n;
	void init(int sz) {
		n = sz;
		E.resize(sz);
	}
	void add_edge(Edge e) {
		E[e.from].emplace_back(e);
	}
	vector<Edge>& operator[](int x) {
		return E[x];
	}
	size_t size() {
		return n;
	}
};
using edges = Edges_List<edge>;
/*
	Depends on 
		- Edge_Cost or Edge_Cap_Rev
*/