struct Graph {
	struct Vertex{};
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
struct LCA : public Graph {
	vector<vector<int>> lca_dp;
	vector<int> depth;
	int log2_n;
	LCA(int n) : Graph(n), depth(sz, -100000) {}
	void lca_build(int root) {
		log2_n = 0;
		for (int t = sz; t; t /= 2, log2_n++);
		lca_dp.resize(log2_n, vector<int>(sz, -1));
		lca_dfs(root);
		for (int i = 1; i < log2_n; i++) {
			for (int j = 0; j < sz; j++) {
				if (lca_dp[i-1][j] == -1) lca_dp[i][j] = -1;
				else lca_dp[i][j] = lca_dp[i-1][lca_dp[i-1][j]];
			}
		}
	}
	void lca_dfs(int root) {
		stack<tuple<int, int, int>> s;
		s.emplace(root, -1, 0);
		while (!s.empty()) {
			int now, par, d;
			tie(now, par, d) = s.top(); s.pop();
			lca_dp[0][now] = par;
			depth[now] = d;
			for (auto& x: e[now]) {
				if (x.to != par) s.emplace(x.to, now, d+1);
			}
		}
	}
	int get_lca(int a, int b) {
		if (depth[a] > depth[b]) swap(a, b);
		for (int i = log2_n - 1; i >= 0 ; i--) {
			if (((depth[b] - depth[a]) >> i) & 1) b = lca_dp[i][b];
		}
		if (a == b) return a;
		for (int i = log2_n - 1; i >= 0; i--) {
			if (lca_dp[i][a] != lca_dp[i][b]) {
				a = lca_dp[i][a];
				b = lca_dp[i][b];
			}
		}
		return lca_dp[0][a];
	}
	int lca_distace(int a, int b) {
		return depth[a] + depth[b] - 2 * depth[get_lca(a, b)];
	}
};