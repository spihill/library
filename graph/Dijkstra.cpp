using dijkstra_cost = $1;

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

template<class T>
struct Vertex
{
	T cost;
	Vertex(T v1) : cost(v1) {}
	Vertex() {}
};
using vertex = Vertex<dijkstra_cost>;

template<class T>
struct Edge
{
	int to;
	T cost;
	Edge(int t, T c) : to(t), cost(c) {}
	Edge() {}
};
using edge = Edge<dijkstra_cost>;
using graph = Graph<vertex, edge>;

template<class V, class E>
void Dijkstra(Graph<V, E>& G, int s, dijkstra_cost INF_COST)
{
	auto &v = G.v;
	auto &e = G.e;
	for (auto& vv : v) vv.cost = INF_COST;
	using Q_T = pair<dijkstra_cost, int>;
	priority_queue<Q_T, vector<Q_T>, greater<>> q;
	q.emplace(0, s);
	while (!q.empty()) {
		auto a = q.top();
		q.pop();
		if (a.first >= v[a.second].cost) continue;
		v[a.second].cost = a.first;
		for (auto& p : e[a.second]) {
			if (p.cost == INF_COST) continue;
			if (a.first + p.cost < v[p.to].cost) q.emplace(a.first + p.cost, p.to);
		}
	}
}