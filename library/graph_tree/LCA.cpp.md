---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :warning: graph_tree/LCA.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f93f3ae32620f7630b3615eae399affa">graph_tree</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph_tree/LCA.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-19 20:47:29+09:00




## Depends on

* :heavy_check_mark: <a href="../for_include/make_graph.cpp.html">for_include/make_graph.cpp</a>
* :heavy_check_mark: <a href="../helper/tag.cpp.html">helper/tag.cpp</a>
* :heavy_check_mark: <a href="../template/UnWeightedGraph.cpp.html">template/UnWeightedGraph.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
namespace lca_n {
#include "../template/UnWeightedGraph.cpp"
#include "../helper/tag.cpp"
template<class T> using graph = UnWeightedGraph<T>;
#include "../for_include/make_graph.cpp"
template<class T>
struct LCA : public graph<T> {
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
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph_tree/LCA.cpp"
namespace lca_n {
#line 1 "graph_tree/../template/UnWeightedGraph.cpp"
template<class VertexType = long long>
struct UnWeightedGraph {
	template<class T> static enable_if_t<is_integral<T>::value, size_t>  index(T x) {return x;}
	template<class T> static enable_if_t<is_integral<T>::value, T>     restore(T x) {return x;}
	template<class T> static enable_if_t<!is_integral<T>::value, size_t> index(T x) {return x.index();}
	template<class T> static enable_if_t<!is_integral<T>::value, T>    restore(T x) {return x.restore();}
	struct graph_tag {};
	vector<vector<size_t>> edge;
	UnWeightedGraph(size_t N) : edge(N) {}
	template<class T, class U> void add_edge(T from, U to) {
		edge[index(from)].push_back(index(to));
	}
	size_t size() const {
		return edge.size();
	}
	void clear() {
		edge.clear();
	}
	using vertex_type = VertexType;
};#line 1 "graph_tree/../helper/tag.cpp"
template <class T>
class has_graph_tag {
	template <class U, typename O = typename U::graph_tag> static constexpr std::true_type check(int);
	template <class U> static constexpr std::false_type check(long);
public:
	static constexpr bool value = decltype(check<T>(0))::value;
};
template <class T> constexpr bool has_graph_tag_v = has_graph_tag<T>::value;#line 4 "graph_tree/LCA.cpp"
template<class T> using graph = UnWeightedGraph<T>;
#line 1 "graph_tree/../for_include/make_graph.cpp"
template<class T = long long>
graph<T> make_graph(size_t N) {
	return move(graph<T>(N));
}#line 6 "graph_tree/LCA.cpp"
template<class T>
struct LCA : public graph<T> {
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
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

