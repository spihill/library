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
struct Vertex_Cost
{
	T cost;
	Vertex_Cost(T v1) : cost(v1) {}
	Vertex_Cost() {}
	inline bool operator<(const Vertex_Cost r) const {
		return cost < r.cost;
	}
	inline bool operator>(const Vertex_Cost r) const {
		return r < *this;
	}
	inline bool operator>=(const Vertex_Cost r) const {
		return !(*this < r);
	}
	inline bool operator<=(const Vertex_Cost r) const {
		return !(r < *this);
	}
	inline bool operator==(const Vertex_Cost r) const {
		return !(r < *this) && !(*this < r);
	}
	inline bool operator!=(const Vertex_Cost r) const {
		return (r < *this) || (*this < r);
	}
};
using vertex = Vertex_Cost<dijkstra_cost>;

template<class T>
struct Edge_Cost
{
	int to;
	T cost;
	Edge_Cost(int t, T c) : to(t), cost(c) {}
	Edge_Cost() {}
	inline bool operator<(const Edge_Cost rhs) const {
		return cost < rhs.cost;
	}
	inline bool operator>(const Edge_Cost rhs) const {
		return rhs < *this;
	}
	inline bool operator>=(const Edge_Cost rhs) const {
		return !(*this < rhs);
	}
	inline bool operator<=(const Edge_Cost rhs) const {
		return !(*this > rhs);
	}
	inline bool operator==(const Edge_Cost rhs) const {
		return *this <= rhs && *this >= rhs;
	}
	inline bool operator!=(const Edge_Cost rhs) const {
		return !(*this == rhs);
	}
};
using edge = Edge_Cost<dijkstra_cost>;
using graph = Graph<vertex, edge>;

template<class T, class V, class E>
void Dijkstra(Graph<V, E>& G, int s, T INF_COST)
{
	auto &v = G.v;
	auto &e = G.e;
	for (auto& vv : v) vv.cost = INF_COST;
	priority_queue<E, vector<E>, greater<E>> q;
	q.emplace(s, 0);
	while (!q.empty()) {
		auto a = q.top();
		q.pop();
		if (a.cost >= v[a.to].cost) continue;
		v[a.to].cost = a.cost;
		for (auto& p : e[a.to]) {
			if (p.cost == INF_COST) continue;
			if (a.cost + p.cost < v[p.to].cost) q.emplace(p.to, a.cost + p.cost);
		}
	}
}