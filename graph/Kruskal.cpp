template<class T>
struct Graph {
	struct Vertex {};
	struct Edge {
		int from;
		int to;
		T cost;
		Edge(int t, T c) : to(t), cost(c) {}
		Edge(int t, int u, T c) : from(t), to(u), cost(c) {}
		bool operator<(const Edge& r) {
			return this->cost < r.cost;
		}
		Edge() {}
	};
	int sz;
	vector<Vertex> v;
	vector<vector<Edge>> e;
	vector<Edge> edges;
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
struct Kruskal : public Graph<T> {
	Kruskal(int n) : Graph<T>(n) {};
	template<class... Args>
	void Kruskal_add_edge(int pos, Args... args) {
		this->e[pos].emplace_back(args...);
		this->edges.emplace_back(pos, args...);
	}
	T Kruskal_solve() {
		sort(this->edges.begin(), this->edges.end());
		UnionFind u(this->sz);
		T res = 0;
		for (auto &x : this->edges) {
			if (u.unite(x.from, x.to)) res += x.cost;
		}
		return res;
	}
};
