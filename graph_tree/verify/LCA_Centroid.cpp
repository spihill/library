#include <bits/stdc++.h>

using namespace std;

const int INF = 1e7;

struct Graph {
	struct Vertex {
		int dist;
		Vertex() : dist(INF) {}
	};
	struct Edge {
		int to;
		Edge(int t) : to(t) {}
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

struct Centroid : public LCA {
	vector<bool> dead;
	vector<int> subsize;
	vector<int> par;
	vector<vector<Edge>> child_par;
	vector<vector<Edge>> par_child;
	vector<char> ok;
	Centroid(int n) : LCA(n), dead(sz, false), subsize(sz, sz), par(sz, -1), child_par(n), par_child(n), ok(n) {}
	void centroid_dfs(int v, int chsize, int& res, int p = -1) {
		stack<int> s;
		stack<int> st;
		st.push(v);
		par[v] = -1;
		while (!st.empty()) {
			auto t = st.top(); st.pop();
			subsize[t] = 1;
			s.push(t); 
			ok[t] = 1;
			for (auto& x: e[t]) {
				if (dead[x.to] || par[t] == x.to) continue;
				par[x.to] = t;
				st.push(x.to);
			}
		}
		while (!s.empty()) {
			auto t = s.top(); s.pop();
			st.push(t);
			if (par[t] != -1) {
				subsize[par[t]] += subsize[t];
				if (subsize[t] > chsize / 2) {
					ok[par[t]] = 0;
				}
			}
		}
		while (true) {
			auto t = st.top(); st.pop();
			if (ok[t] && (chsize + 1) / 2 <= subsize[t]) {
				res = t;
				return;
			}
		}
	}
	int centroid_build(int root = 0) {
		vector<int> next;
		int r = centroid_find(root, next);
		for (auto& x: next) {
			int t = centroid_build(x);
			par_child[r].emplace_back(t);
			child_par[t].emplace_back(r);
		}
		return r;
	}
	int centroid_find(int root, vector<int>& next_root) {
		int centor;
		centroid_dfs(root, subsize[root], centor);
		if (par[centor] >= 0) subsize[par[centor]] = subsize[root] - subsize[centor];
		dead[centor] = true;
		for (auto& x: e[centor]) {
			if (dead[x.to]) continue;
			next_root.emplace_back(x.to);
		}
		return centor;
	}
};
using centroid = Centroid;

void paint(centroid& C, int x) {
	C.v[x].dist = 0;
	int now = x;
	while (C.child_par[now].size()) {
		now = C.child_par[now][0].to;
		C.v[now].dist = min(C.v[now].dist, C.lca_distace(x, now));
	}
}
int calc(centroid& C, int x) {
	int res = C.v[x].dist;
	int now = x;
	while (C.child_par[now].size()) {
		now = C.child_par[now][0].to;
		res = min(res, C.v[now].dist + C.lca_distace(x, now));
	}
	return res;
}

int main() {
	int N, Q;
	cin >> N >> Q;
	centroid C(N);
	for (int i = 0; i < N - 1; i++) {
		int a, b;
		cin >> a >> b;
		a--;b--;
		C.add_edge(a, b);
		C.add_edge(b, a);
	}
	C.centroid_build();
	C.lca_build(0);
	paint(C, 0);
	for (int i = 0; i < Q; i++) {
		int a, b;
		cin >> a >> b;
		b--;
		if (a == 1) {
			paint(C, b);
		} else {
			cout << calc(C, b) << endl;
		}
	}
}

/*
	verified on http://codeforces.com/problemset/problem/342/E?csrf_token=48bbc47f9ea12f460aa78060e1c2d281
*/