#include <bits/stdc++.h>

using namespace std;

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

struct Vertex{};
using vertex = Vertex;

struct Edge
{
	int to;
	Edge(int t) : to(t) {}
	Edge() {}
};


using edge = Edge;
using graph = Graph<vertex, edge>;

template<class G>
struct LCA {
	int sz;
	vector<vector<int>> dp;
	vector<int> depth;
	int log2_n;
	LCA(G& g, int root) : sz(g.size()), depth(sz) {
		log2_n = 0;
		for (int t = sz; t; t /= 2, log2_n++);
		dp.resize(sz, vector<int>(log2_n, -1));
		dfs(g, root);
		for (int i = 0; i < sz; i++) {
			for (int j = 1; j < log2_n; j++) {
				int t = dp[i][j-1];
				dp[i][j] = t == -1 ? -1 : dp[t][j-1];
			}
		}
	}
	inline int size() { return sz;}
	void dfs(G& g, int root) {
		stack<tuple<int, int, int>> s;
		s.emplace(root, -1, 0);
		while (!s.empty()) {
			int now, par, d;
			tie(now, par, d) = s.top(); s.pop();
			dp[now][0] = par;
			depth[now] = d;
			for (auto& x: g.e[now]) {
				if (x.to != par) s.emplace(x.to, now, d+1);
			}
		}
	}
	int get(int a, int b) {
		if (depth[a] > depth[b]) swap(a, b);
		for (int i = 0; i < log2_n; i++) {
			if ((depth[b] - depth[a]) & (1 << i)) b = dp[b][i];
		}
		if (a == b) return a;
		for (int i = log2_n - 1; i >= 0; i--) {
			if (dp[a][i] != dp[b][i]) {
				a = dp[a][i];
				b = dp[b][i];
			}
		}
		return dp[a][0];
	}
};

using lca = LCA<graph>;

int main() {
	int N, Q;
	scanf("%d %d", &N, &Q);
	graph g(N);
	for (int i = 1; i < N; i++) {
		int a;
		scanf("%d", &a);
		g.add_edge(a, i);
	}
	lca L(g, 0);
	for (int i = 0; i < Q; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		printf("%d\n", L.get(a, b));
	}
}

/*
	Verified on https://judge.yosupo.jp/problem/lca
*/
