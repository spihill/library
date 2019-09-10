template<class T>
struct Graph {
	struct Vertex {
		T cost;
		bool valid = false; // 到達不能または無限にコストが減るときfalse
		Vertex(T v1) : cost(v1) {}
		Vertex() {}
	};
	struct Edge {
		int from;
		int to;
		T cost;
		Edge(int t, T c) : to(t), cost(c) {}
		Edge(int t, int u, T c) : from(t), to(u), cost(c) {}
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
		edges.emplace_back(pos, args...);
	}
	inline int size() {
		return sz;
	}
};
template<class T>
struct Bellmanford : public Graph<T> {
	Bellmanford(int n) : Graph<T>(n) {};
	void Bellman_solve(int s, T INF_COST) {
		auto& v = this->v;
		auto& e = this->e;
		for (auto& vv : v) vv.cost = INF_COST, vv.valid = false;
		v[s].cost = 0, v[s].valid = true;
		for (int i = 0; i + 1 < (int) v.size(); i++) {
			for (auto& x: this->edges) {
				if (v[x.from].cost == INF_COST) continue;
				v[x.to].cost = min(v[x.to].cost, v[x.from].cost + x.cost);
				v[x.to].valid = true;
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
};