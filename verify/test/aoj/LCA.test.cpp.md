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
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :heavy_check_mark: test/aoj/LCA.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/LCA.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-20 01:44:55+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C&lang=ja">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C&lang=ja</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/for_include/make_graph2.cpp.html">for_include/make_graph2.cpp</a>
* :heavy_check_mark: <a href="../../../library/graph_tree/LCA.cpp.html">graph_tree/LCA.cpp</a>
* :heavy_check_mark: <a href="../../../library/helper/tag.cpp.html">helper/tag.cpp</a>
* :heavy_check_mark: <a href="../../../library/template/UnWeightedGraph.cpp.html">template/UnWeightedGraph.cpp</a>
* :heavy_check_mark: <a href="../../../library/template/WeightedGraph.cpp.html">template/WeightedGraph.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#include "../../graph_tree/LCA.cpp"

int main() {
	int V;
	cin >> V;
	auto L = make_graph(V);
	for (int i = 0; i < V; i++) {
		int k;
		cin >> k;
		for (int j = 0; j < k; j++) {
			int v;
			cin >> v;
			L.add_edge(i, v);
			L.add_edge(v, i);
		}
	}
	L.build(0);
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		int u, v;
		cin >> u >> v;
		cout << L.lca(u, v) << endl;
	}
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj/LCA.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#line 1 "test/aoj/../../graph_tree/LCA.cpp"
namespace lca_n {
#line 1 "test/aoj/../../graph_tree/../template/WeightedGraph.cpp"
#include<bits/stdc++.h>
using namespace std;
#line 1 "test/aoj/../../graph_tree/../template/UnWeightedGraph.cpp"
template<class VertexType = long long>
struct UnWeightedGraph {
	template<class T> static enable_if_t<is_integral<T>::value, size_t>  index(T x) {return x;}
	template<class T> static enable_if_t<is_integral<T>::value, T>     restore(T x) {return x;}
	template<class T> static enable_if_t<!is_integral<T>::value, size_t> index(T x) {return x.index();}
	template<class T> static enable_if_t<!is_integral<T>::value, T>    restore(T x) {return x.restore();}
	struct graph_tag {};
	vector<vector<size_t>> edge;
	const int n;
	UnWeightedGraph(size_t N) : edge(N), n(N) {}
	template<class T, class U> void add_edge(T from, U to) {
		edge[index(from)].push_back(index(to));
	}
	size_t size() const {
		return n;
	}
	void clear() {
		edge.clear();
	}
	using vertex_type = VertexType;
};#line 4 "test/aoj/../../graph_tree/../template/WeightedGraph.cpp"
template<class VertexType = long long, class WeightType = long long>
struct WeightedGraph : UnWeightedGraph<VertexType> {
	using UnWeightedGraph<VertexType>::index;
	using UnWeightedGraph<VertexType>::restore;
	using UnWeightedGraph<VertexType>::size;
	// using UnWeightedGraph<VertexType, WeightType>::graph_tag;
	struct weighted_graph_tag {};
	vector<vector<WeightType>> weight;
	WeightedGraph(size_t N) : UnWeightedGraph<VertexType>(N), weight(N) {}
	template<class T, class U> void add_edge(T from, U to, WeightType w) {
		this->edge[index(from)].push_back(index(to));
		weight[index(from)].push_back(w);
	}
	void clear() {
		this->edge.clear();
		weight.clear();
	}
	using vertex_type = VertexType;
	using weight_type = WeightType;
};#line 1 "test/aoj/../../graph_tree/../helper/tag.cpp"
template <class T>
class has_graph_tag {
	template <class U, typename O = typename U::graph_tag> static constexpr std::true_type check(int);
	template <class U> static constexpr std::false_type check(long);
public:
	static constexpr bool value = decltype(check<T>(0))::value;
};
template <class T> constexpr bool has_graph_tag_v = has_graph_tag<T>::value;

template <class T>
class has_weighted_graph_tag {
	template <class U, typename O = typename U::weighted_graph_tag> static constexpr std::true_type check(int);
	template <class U> static constexpr std::false_type check(long);
public:
	static constexpr bool value = decltype(check<T>(0))::value;
};
template <class T> constexpr bool has_weighted_graph_tag_v = has_weighted_graph_tag<T>::value;#line 4 "test/aoj/../../graph_tree/LCA.cpp"
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
	template<class X, class Y> void add_edge(X from, Y to) {
		add_edge(from, to, 1);
	}
	void build(int root = 0) {
		log2_n = 0;
		for (int t = this->n; t; t /= 2, log2_n++);
		dp.resize(log2_n, vector<int>(this->n, -1));
		dfs(root);
		for (int i = 1; i < log2_n; i++) {
			for (int j = 0; j < this->n; j++) {
				if (dp[i-1][j] == -1) dp[i][j] = -1;
				else dp[i][j] = dp[i-1][dp[i-1][j]];
			}
		}
	}
	void dfs(int root) {
		stack<tuple<size_t, size_t, int, W>> s;
		s.emplace(root, this->n, 0, 0);
		while (!s.empty()) {
			size_t now, par; int d; W w;
			tie(now, par, d, w) = s.top(); s.pop();
			dp[0][now] = par;
			depth[now] = d;
			dist[now] = w;
			for (size_t i = 0; i < this->edge[now].size(); i++) {
				if (this->edge[now][i] != par) s.emplace(this->edge[now][i], now, d + 1, w + this->weight[now][i]);
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
	template<class Graph>
	enable_if_t<has_weighted_graph_tag_v<Graph>> construct_graph(const Graph& G) {
		for (size_t i = 0; i < G.size(); i++) {
			for (int j = 0; j < G.edge[i].size(); j++) {
				add_edge(i, G.edge[i][j], G.weight[i][j]);
			}
		}
	}
	template<class Graph>
	enable_if_t<!has_weighted_graph_tag_v<Graph>> construct_graph(const Graph& G) {
		for (size_t i = 0; i < G.size(); i++) {
			for (int j = 0; j < G.edge[i].size(); j++) {
				add_edge(i, G.edge[i][j]);
			}
		}
	}
};
template<class T, class U> using graph = LCA<T, U>;
#line 1 "test/aoj/../../graph_tree/../for_include/make_graph2.cpp"
template<class T = long long, class U = long long>
graph<T, U> make_graph(size_t N) {
	return move(graph<T, U>(N));
}#line 84 "test/aoj/../../graph_tree/LCA.cpp"
}
template<class T, class U> using graph = lca_n::graph<T, U>;
using lca_n::make_graph;
using lca_n::LCA;#line 8 "test/aoj/LCA.test.cpp"

int main() {
	int V;
	cin >> V;
	auto L = make_graph(V);
	for (int i = 0; i < V; i++) {
		int k;
		cin >> k;
		for (int j = 0; j < k; j++) {
			int v;
			cin >> v;
			L.add_edge(i, v);
			L.add_edge(v, i);
		}
	}
	L.build(0);
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		int u, v;
		cin >> u >> v;
		cout << L.lca(u, v) << endl;
	}
}
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

