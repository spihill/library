template<class V, class E>
struct Graph
{
	int sz;
	vector<V> v;
	vector<vector<E>> e;
	Graph(int n) : sz(n), v(n), e(n) {}
	template<class... Args>
	inline void assign_vertex(int pos, Args... args) {
		v[pos] = V(args...);
	}
	template<class... Args>
	inline void add_edge(int pos, Args... args) {
		e[pos].emplace_back(args...);
	}
	inline int size() {
		return sz;
	}
};
struct Vertex{};
using vertex = Vertex;
struct Edge
{
	int to;
	int cost;
	Edge(int t, int c) : to(t), cost(c) {}
	Edge() {}
};

using edge = Edge;
using graph = Graph<vertex, edge>;

int Diameter(graph& G) {
	auto dfs = [&G](auto f, int start, int& goal, int par = -1) -> int {
		goal = start;
		int res = 0;
		for (auto& e: G.e[start]) {
			if (e.to == par) continue;
			int t;
			int r = f(f, e.to, t, start);
			r += e.cost;
			if (r > res) {
				res = r;
				goal = t;
			}
		}
		return res;
	};
	int g;
	dfs(dfs, 0, g);
	return dfs(dfs, g, g);
}