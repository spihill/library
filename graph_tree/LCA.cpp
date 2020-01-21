namespace lca_n {
#include "../template/WeightedGraph.cpp"
#include "../for_include/has_graph_tag.cpp"
#include "../for_include/has_weighted_graph_tag.cpp"
template<class T, class W> using super_graph = WeightedGraph<T, W>;
template<class T, class W>
struct LCA : public super_graph<T, W> {
	vector<vector<int>> dp;
	vector<int> depth;
	vector<W> dist;
	int log2_n;
	LCA(size_t N) : super_graph<T, W>(N), depth(N, -100000), dist(N, 0) {}
	template<class Graph>
	LCA(Graph& G) : LCA(G.size()) {
		static_assert(has_graph_tag_v<Graph>);
		construct_graph(G);
	}
	using super_graph<T, W>::add_edge;
	using super_graph<T, W>::size;
	using super_graph<T, W>::index;
	using super_graph<T, W>::restore;
	template<class X, class Y> void add_edge(X from, Y to) {
		add_edge(from, to, 1);
	}
	void build(int root = 0) {
		log2_n = 0;
		for (int t = this->n; t; t /= 2, log2_n++);
		dp.resize(log2_n, vector<int>(this->n + 1, -1));
		dfs(root);
		for (int i = 1; i < log2_n; i++) {
			for (int j = 0; j < this->n; j++) {
				if (dp[i-1][j] == -1) dp[i][j] = -1;
				else dp[i][j] = dp[i-1][dp[i-1][j]];
			}
		}
	}
	void dfs(int root) {
		stack<tuple<size_t, int, int, W>> s;
		s.emplace(root, -1, 0, 0);
		while (!s.empty()) {
			size_t now; int par, d; W w;
			tie(now, par, d, w) = s.top(); s.pop();
			dp[0][now] = par;
			depth[now] = d;
			dist[now] = w;
			for (size_t i = 0; i < this->edge[now].size(); i++) {
				if ((int) this->edge[now][i] != par) s.emplace(this->edge[now][i], now, d + 1, w + this->weight[now][i]);
			}
		}
	}
	T lca(T A, T B) {
		int a = index(A);
		int b = index(B);
		if (depth[a] > depth[b]) swap(a, b);
		for (int i = log2_n - 1; i >= 0 ; i--) {
			if (((depth[b] - depth[a]) >> i) & 1) b = dp[i][b];
		}
		if (a == b) return restore(a);
		for (int i = log2_n - 1; i >= 0; i--) {
			if (dp[i][a] != dp[i][b]) {
				a = dp[i][a];
				b = dp[i][b];
			}
		}
		return restore(dp[0][a]);
	}
	W distance(T a, T b) {
		return dist[index(a)] + dist[index(b)] - 2 * dist[index(lca(a, b))];
	}
	template<class Graph>
	enable_if_t<has_weighted_graph_tag_v<Graph>> construct_graph(const Graph& G) {
		for (size_t i = 0; i < G.size(); i++) {
			for (size_t j = 0; j < G.edge[i].size(); j++) {
				assert(G.edge[i].size() == G.weight[i].size());
				add_edge(i, G.edge[i][j], G.weight[i][j]);
			}
		}
	}
	template<class Graph>
	enable_if_t<!has_weighted_graph_tag_v<Graph>> construct_graph(const Graph& G) {
		for (size_t i = 0; i < G.size(); i++) {
			for (size_t j = 0; j < G.edge[i].size(); j++) {
				add_edge(i, G.edge[i][j]);
			}
		}
	}
};
template<class T, class U> using graph = LCA<T, U>;
template<class T = long long, class U = long long>
graph<T, U> make_lca(size_t N) {
	return move(graph<T, U>(N));
}
template<class Graph, class T = typename Graph::vertex_type, class U = long long>
enable_if_t<has_graph_tag_v<Graph> && !has_weighted_graph_tag_v<Graph>, graph<T, U>> make_lca(Graph& G) {
	return move(graph<T, U>(G));
}
template<class Graph, class T = typename Graph::vertex_type, class U = typename Graph::weight_type>
enable_if_t<has_weighted_graph_tag_v<Graph>, graph<T, U>> make_lca(Graph& G) {
	return move(graph<T, U>(G));
}
}
using lca_n::make_lca;
using lca_n::LCA;