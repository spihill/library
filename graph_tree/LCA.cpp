namespace lca_n {
#include "../template/WeightedGraph.cpp"
#include "../for_include/has_graph_tag.cpp"
#include "../for_include/has_weighted_graph_tag.cpp"
using u32 = uint_fast32_t;
using i64 = int_fast64_t;
template<class WEIGHT> using super_graph = WeightedGraph<WEIGHT>;
template<class WEIGHT>
struct LCA : public super_graph<WEIGHT> {
	vector<vector<int>> dp;
	vector<int> depth;
	vector<WEIGHT> dist;
	u32 log2_n;
	LCA(u32 N) : super_graph<WEIGHT>(N), depth(N, -100000), dist(N, 0) {}
	template<class Graph>
	LCA(Graph& G) : LCA(G.size()) {
		static_assert(has_graph_tag_v<Graph>, "");
		construct_graph(G);
	}
	using super_graph<WEIGHT>::add_edge;
	void add_edge(u32 from, u32 to) {
		add_edge(from, to, 1);
	}
	void build(int root = 0) {
		log2_n = 0;
		for (int t = this->n; t; t /= 2, log2_n++);
		dp.resize(log2_n, vector<int>(this->n + 1, -1));
		dfs(root);
		for (u32 i = 1; i < log2_n; i++) {
			for (u32 j = 0; j < this->n; j++) {
				if (dp[i-1][j] == -1) dp[i][j] = -1;
				else dp[i][j] = dp[i-1][dp[i-1][j]];
			}
		}
	}
	void dfs(int root) {
		auto& e = this->e;
		stack<tuple<u32, int, int, WEIGHT>> s;
		s.emplace(root, -1, 0, 0);
		while (!s.empty()) {
			u32 now; int par, d; WEIGHT w;
			tie(now, par, d, w) = s.top(); s.pop();
			dp[0][now] = par;
			depth[now] = d;
			dist[now] = w;
			for (auto& x : e[now]) {
				if ((int) x.to != par) s.emplace(x.to, now, d + 1, w + x.weight);
			}
		}
	}
	u32 lca(u32 a, u32 b) {
		if (depth[a] > depth[b]) swap(a, b);
		for (int i = log2_n - 1; i >= 0 ; i--) {
			if (((depth[b] - depth[a]) >> i) & 1) b = dp[i][b];
		}
		if (a == b) return a;;
		for (int i = log2_n - 1; i >= 0; i--) {
			if (dp[i][a] != dp[i][b]) {
				a = dp[i][a];
				b = dp[i][b];
			}
		}
		return dp[0][a];
	}
	WEIGHT distance(u32 a, u32 b) {
		return dist[a] + dist[b] - 2 * dist[lca(a, b)];
	}
	u32 parent(u32 a) {
		return dp[0][a];
	}
	template<class Graph>
	enable_if_t<has_weighted_graph_tag_v<Graph>> construct_graph(const Graph& G) {
		for (u32 i = 0; i < G.size(); i++) {
			for (auto& x : G.e[i]) {
				add_edge(i, x.to, x.weight);
			}
		}
	}
	template<class Graph>
	enable_if_t<!has_weighted_graph_tag_v<Graph>> construct_graph(const Graph& G) {
		for (u32 i = 0; i < G.size(); i++) {
			for (auto& x : G.e[i]) {
				add_edge(i, x.to);
			}
		}
	}
};
template<class WEIGHT = long long>
LCA<WEIGHT> make_lca(u32 N) {
	return LCA<WEIGHT>(N);
}
template<class Graph, class WEIGHT = long long>
enable_if_t<has_graph_tag_v<Graph> && !has_weighted_graph_tag_v<Graph>, LCA<WEIGHT>> make_lca(Graph& G) {
	return LCA<WEIGHT>(G);
}
template<class Graph, class WEIGHT = typename Graph::WEIGHT_TYPE>
enable_if_t<has_weighted_graph_tag_v<Graph>, LCA<WEIGHT>> make_lca(Graph& G) {
	return LCA<WEIGHT>(G);
}
}
using lca_n::make_lca;
using lca_n::LCA;