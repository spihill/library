template<class F>
struct Edge {
	int to;
	F cap;
	int rev;
	Edge(int x, F y, int z) : to(x), cap(y), rev(z) {}
};
template<class F>
struct Edges : private vector<vector<Edge<F>>> {
	using type = vector<vector<Edge<F>>>;
	template<class... Args> Edges(Args... args) : type(args...) {}
	template<class... Args> void add_edge(int u, int v, Args... args) {
		(*this)[u].emplace_back(v, args...);
	}
#include "../for_include/vec.cpp"
};