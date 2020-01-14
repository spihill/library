struct Edge {
	int to;
	Edge(int t) : to(t) {}
};
struct Edges : private vector<vector<Edge>> {
	using type = vector<vector<Edge>>;
	void add_edge(int u, int v) {
		(*this)[u].emplace_back(v);
	}
	template<class... Args> Edges(Args... args) : vector<vector<Edge>>(args...) {}
#include "../for_include/vec.cpp"
};