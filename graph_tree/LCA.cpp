namespace lca_n {
#include "../snippet/Graph.cpp"
struct LCA : public Graph {
	vector<vector<int>> dp;
	vector<int> depth;
	int log2_n;
	LCA(int n) : Graph(n), depth(sz, -100000) {}
	void build(int root) {
		log2_n = 0;
		for (int t = sz; t; t /= 2, log2_n++);
		dp.resize(log2_n, vector<int>(sz, -1));
		dfs(root);
		for (int i = 1; i < log2_n; i++) {
			for (int j = 0; j < sz; j++) {
				if (dp[i-1][j] == -1) dp[i][j] = -1;
				else dp[i][j] = dp[i-1][dp[i-1][j]];
			}
		}
	}
	void dfs(int root) {
		stack<tuple<int, int, int>> s;
		s.emplace(root, -1, 0);
		while (!s.empty()) {
			int now, par, d;
			tie(now, par, d) = s.top(); s.pop();
			dp[0][now] = par;
			depth[now] = d;
			for (auto& x: e[now]) {
				if (x.to != par) s.emplace(x.to, now, d+1);
			}
		}
	}
	int lca(int a, int b) {
		if (depth[a] > depth[b]) swap(a, b);
		for (int i = log2_n - 1; i >= 0 ; i--) {
			if (((depth[b] - depth[a]) >> i) & 1) b = dp[i][b];
		}
		if (a == b) return a;
		for (int i = log2_n - 1; i >= 0; i--) {
			if (dp[i][a] != dp[i][b]) {
				a = dp[i][a];
				b = dp[i][b];
			}
		}
		return dp[0][a];
	}
	int distance(int a, int b) {
		return depth[a] + depth[b] - 2 * depth[lca(a, b)];
	}
};
}
using graph = lca_n::LCA;