struct Graph {
	struct Vertex {
		Vertex() {}
	};
	struct Edge {
		int to;
		Edge(int t) : to(t) {}
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
struct TopologicalSort : public Graph {
	TopologicalSort(int n) : Graph(n) {}
	pair<bool, vector<int>> Topological_solve() {
		int V = size();
		vector<char> visited(V, false);
		vector<int> cnt(V, 0);
		for (int i = 0; i < V; i++) {
			for (auto& x : e[i]) {
				cnt[x.to]++;
			}
		}
		stack<int> s;
		vector<int> res;
		for (int i = 0; i < V; i++) {
			if (cnt[i] == 0) s.push(i);
		}
		while (!s.empty()) {
			int v = s.top(); s.pop();
			res.push_back(v);
			for (auto& x : e[v]) {
				if (--cnt[x.to] == 0) s.push(x.to);
			}
		}
		return make_pair((int)res.size() == size(), res);
	}
};