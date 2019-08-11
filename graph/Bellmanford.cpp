using bellman_cost = $1;
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
	// from, to, cost
	template<class... Args>
	inline void add_edge(int pos, Args... args) {
		e[pos].emplace_back(args...);
	}
	inline int size() {
		return sz;
	}
};

template<class T>
struct Vertex
{
	T cost;
	bool valid = false; // 到達不能または無限にコストが減るときfalse
	Vertex(T v1) : cost(v1) {}
	Vertex() {}
};
using vertex = Vertex<bellman_cost>;

template<class T>
struct Edge
{
	int to;
	T cost;
	Edge(int t, T c) : to(t), cost(c) {}
	Edge() {}
};
using edge = Edge<bellman_cost>;
using graph = Graph<vertex, edge>;

template<class V, class E>
void Bellmanford(Graph<V, E>& G, int s, bellman_cost INF_COST)
{
	auto &v = G.v;
	auto &e = G.e;
	for (auto& vv : v) vv.cost = INF_COST, vv.valid = false;
	v[s].cost = 0, v[s].valid = true;
	for (int i = 0; i + 1 < (int) v.size(); i++) {
		for (int j = 0; j < (int) v.size(); j++) {
			for (auto& x: e[j]) {
				if (v[j].cost == INF_COST) continue;
				v[x.to].cost = min(v[x.to].cost, v[j].cost + x.cost);
				v[x.to].valid = true;
			}
		}
	}
	auto valid_check = [&](auto f, int pos) {
		if (!v[pos].valid) return;
		v[pos].valid = false;
		for (auto& y: e[pos]) {
			f(f, y.to);
		}
	};
	for (int i = 0; i < (int) v.size(); i++) {
		for (auto& x: e[i]) {
			if (v[i].cost == INF_COST) continue;
			if (v[x.to].cost > v[i].cost + x.cost) {
				valid_check(valid_check, x.to);
			}
		}
	}
}
