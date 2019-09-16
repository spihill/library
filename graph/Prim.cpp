template<class T>
struct Graph {
	struct Vertex {};
	struct Edge {
		int from;
		int to;
		T cost;
		Edge(int t, T c) : to(t), cost(c) {}
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
struct Prim : public Graph<T> {
	Prim(int n) : Graph<T>(n) {};
	T Prim_solve() {
		T res = 0;
		vector<char> used(this->sz, 0);
		priority_queue<pair<T, int>, vector<pair<T, int>>, greater<>> q;
		q.emplace(0, 0);
		while (!q.empty()) {
			auto p = q.top(); q.pop();
			if (used[p.second] != 0) continue;
			used[p.second] = 1;
			res += p.first;
			for (auto& x : this->e[p.second]) {
				q.emplace(x.cost, x.to);
			}
		}
		return res;
	}
};
