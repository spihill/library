template<class Edge>
struct Edges_Matrix {
	vector<vector<Edge>> E;
	int n;
	void init(int sz) {
		n = sz;
		E.resize(n, vector<Edge>(n));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				E[i][j].from = i;
				E[i][j].to = j;
			}
		}
	}
	void add_edge(Edge e) {
		E[from][to] = e;
	}
	vector<Edge>& operator[](int x) {
		return E[x];
	}
	size_t size() {
		return n;
	}
};
using edges = Edges_Matrix<edge>;
/*
	Depends on 
		- Edge_Cost or Edge_Cap_Rev
*/