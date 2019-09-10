template<class T>
struct Graph {
	struct Vertex {
		T cost;
		Vertex(T v1) : cost(v1) {}
		Vertex() {}
	};
	struct Edge {
		int to;
		T cost;
		Edge(int t, T c) : to(t), cost(c) {}
		Edge() {}
	};
	int sz;
	vector<Vertex> v;
	vector<vector<Edge>> e;
	Graph(int n) : sz(n), v(n), e(n) {}
	template<class... Args>
	inline void assign_vertex(int pos, Args... args) {
		v[pos] = Vertex(args...);
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
struct Dijkstra : public Graph<T> {
	Dijkstra(int n) : Graph<T>(n) {}
	void Dijkstra_solve(int start, T INF_COST) {
		auto& v = this->v;
		auto& e = this->e;
		for (auto& vv : v) vv.cost = INF_COST;
		using Q_T = pair<T, int>;
		priority_queue<Q_T, vector<Q_T>, greater<>> q;
		q.emplace(0, start);
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
};