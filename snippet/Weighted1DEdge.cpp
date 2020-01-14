template<class W>
struct Edge {
	using type = Edge<W>;
	int from;
	int to;
	W w;
	template<class... Args> Edge(int f, int t, Args... args) : from(f), to(t), w(args...) {}
	inline bool operator<(const Edge& rhs) const { return w < rhs.w; }
#include "../for_include/compare_operators.cpp"
};
template<class W>
struct Edges : private vector<Edge<W>> {
	using type = vector<Edge<W>>;
	Edges() : type() {}
	Edges(int n) : type() {assert(0 && "Constructor must be empty");}
	template<class... Args> void add_edge(int u, int v, Args... args) {
		(*this).emplace_back(u, v, args...);
	}
#include "../for_include/vec.cpp"
};