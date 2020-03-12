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

* category: <a href="../../../index.html#0d0c91c0cca30af9c1c9faef0cf04aa9">test/aoj</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/LCA.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-13 00:19:42+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C&lang=ja">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C&lang=ja</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/for_include/has_graph_tag.cpp.html">for_include/has_graph_tag.cpp</a>
* :heavy_check_mark: <a href="../../../library/for_include/has_weighted_graph_tag.cpp.html">for_include/has_weighted_graph_tag.cpp</a>
* :heavy_check_mark: <a href="../../../library/graph_tree/LCA.cpp.html">graph_tree/LCA.cpp</a>
* :heavy_check_mark: <a href="../../../library/template/Graph.cpp.html">template/Graph.cpp</a>
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
#include "../../template/UnWeightedGraph.cpp"
#include "../../template/WeightedGraph.cpp"


vector<int> solve1(int V, const vector<vector<int>>& g, vector<int>& A, vector<int>& B) {
	vector<int> res;
	auto L = make_lca(V);
	for (int i = 0; i < V; i++) {
		for (auto x : g[i]) {
			L.add_edge(i, x);
			L.add_edge(x, i);
		}
	}
	L.build();
	for (size_t i = 0; i < A.size(); i++) {
		res.push_back(L.lca(A[i], B[i]));
	}
	return res;
}

vector<int> solve2(int V, const vector<vector<int>>& g, vector<int>& A, vector<int>& B) {
	vector<int> res;
	auto G = make_unweighted_graph(V);
	for (int i = 0; i < V; i++) {
		for (auto x : g[i]) {
			G.add_edge(i, x);
			G.add_edge(x, i);
		}
	}
	auto L = make_lca(G);
	L.build(0);
	for (size_t i = 0; i < A.size(); i++) {
		res.push_back(L.lca(A[i], B[i]));
	}
	return res;
}

vector<int> solve3(int V, const vector<vector<int>>& g, vector<int>& A, vector<int>& B) {
	vector<int> res;
	auto G = make_weighted_graph(V);
	for (int i = 0; i < V; i++) {
		for (auto x : g[i]) {
			G.add_edge(i, x, 1);
			G.add_edge(x, i, 1);
		}
	}
	auto L = make_lca(G);
	L.build(0);
	for (size_t i = 0; i < A.size(); i++) {
		res.push_back(L.lca(A[i], B[i]));
	}
	return res;
}

int main() {
	int V; cin >> V;
	vector<vector<int>> g(V);
	for (int i = 0; i < V; i++) {
		int k;
		cin >> k;
		for (int j = 0; j < k; j++) {
			int v;
			cin >> v;
			g[i].push_back(v);
		}
	}
	int Q; cin >> Q;
	vector<int> A, B;
	for (int i = 0; i < Q; i++) {
		int u, v; cin >> u >> v;
		A.push_back(u);
		B.push_back(v);
	}
	auto r1 = solve1(V, g, A, B);
	auto r2 = solve2(V, g, A, B);
	auto r3 = solve3(V, g, A, B);
	assert(r1 == r2);
	assert(r1 == r3);
	for (auto x : r2) {
		cout << x << endl;
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
namespace weighted_graph_n{
#line 1 "test/aoj/../../graph_tree/../template/Graph.cpp"
template<class EDGE, class VERTEX>
struct Graph {
	using u32 = uint_fast32_t;
	using i32 = int_fast32_t;
	using u64 = uint_fast64_t;
	struct graph_tag {};
	const u32 n;
	vector<vector<EDGE>> e;
	vector<VERTEX> v;
	vector<u64> idx;
	Graph(u32 N) : n(N), e(n), v(n) {}
	template<class...  Args> void add_edge(u32 from, u32 to, Args... args) {
		idx.push_back((static_cast<u64>(from) << 32) | e[from].size());
		e[from].emplace_back(to, args...);
	}
	u32 size() const {return n;}
	using EDGE_TYPE = EDGE;
	using VERTEX_TYPE = VERTEX;
};
#line 3 "test/aoj/../../graph_tree/../template/WeightedGraph.cpp"
using u32 = uint_fast32_t;
using i64 = int_fast64_t;
struct Vertex {};
template<class WEIGHT>
struct Edge {
	u32 to;
	WEIGHT weight;
	Edge(u32 x, WEIGHT w) : to(x), weight(w) {}
};
template<class WEIGHT>
struct WeightedGraph : public Graph<Edge<WEIGHT>, Vertex> {
	struct weighted_graph_tag {};
	WeightedGraph(u32 N) : Graph<Edge<WEIGHT>, Vertex>(N) {}
	using WEIGHT_TYPE = WEIGHT;
};
template<class WEIGHT = i64>
WeightedGraph<WEIGHT> make_weighted_graph(u32 N) {
	return WeightedGraph<WEIGHT>(N);
}
} // weighted_graph_n
using weighted_graph_n::WeightedGraph;
using weighted_graph_n::make_weighted_graph;
#line 1 "test/aoj/../../graph_tree/../for_include/has_graph_tag.cpp"
template <class T>
class has_graph_tag {
	template <class U> static constexpr std::true_type check(typename U::graph_tag*);
	template <class U> static constexpr std::false_type check(...);
public:
	static constexpr bool value = decltype(check<T>(nullptr))::value;
};
template <class T> constexpr bool has_graph_tag_v = has_graph_tag<T>::value;
#line 1 "test/aoj/../../graph_tree/../for_include/has_weighted_graph_tag.cpp"
template <class T>
class has_weighted_graph_tag {
	template <class U> static constexpr std::true_type check(typename U::weighted_graph_tag*);
	template <class U> static constexpr std::false_type check(...);
public:
	static constexpr bool value = decltype(check<T>(nullptr))::value;
};
template <class T> constexpr bool has_weighted_graph_tag_v = has_weighted_graph_tag<T>::value;
#line 5 "test/aoj/../../graph_tree/LCA.cpp"
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
#line 1 "test/aoj/../../template/UnWeightedGraph.cpp"
namespace unweighted_graph_n {
#line 1 "test/aoj/../../template/Graph.cpp"
template<class EDGE, class VERTEX>
struct Graph {
	using u32 = uint_fast32_t;
	using i32 = int_fast32_t;
	using u64 = uint_fast64_t;
	struct graph_tag {};
	const u32 n;
	vector<vector<EDGE>> e;
	vector<VERTEX> v;
	vector<u64> idx;
	Graph(u32 N) : n(N), e(n), v(n) {}
	template<class...  Args> void add_edge(u32 from, u32 to, Args... args) {
		idx.push_back((static_cast<u64>(from) << 32) | e[from].size());
		e[from].emplace_back(to, args...);
	}
	u32 size() const {return n;}
	using EDGE_TYPE = EDGE;
	using VERTEX_TYPE = VERTEX;
};
#line 3 "test/aoj/../../template/UnWeightedGraph.cpp"
using u32 = uint_fast32_t;
struct Vertex {};
struct Edge {
	u32 to;
	Edge(u32 x) : to(x) {}
};
using UnWeightedGraph = Graph<Edge, Vertex>;
UnWeightedGraph make_unweighted_graph(u32 N) {
	return UnWeightedGraph(N);
}
}
using unweighted_graph_n::UnWeightedGraph;
using unweighted_graph_n::make_unweighted_graph;
#line 1 "test/aoj/../../template/WeightedGraph.cpp"
namespace weighted_graph_n{
#line 1 "test/aoj/../../template/Graph.cpp"
template<class EDGE, class VERTEX>
struct Graph {
	using u32 = uint_fast32_t;
	using i32 = int_fast32_t;
	using u64 = uint_fast64_t;
	struct graph_tag {};
	const u32 n;
	vector<vector<EDGE>> e;
	vector<VERTEX> v;
	vector<u64> idx;
	Graph(u32 N) : n(N), e(n), v(n) {}
	template<class...  Args> void add_edge(u32 from, u32 to, Args... args) {
		idx.push_back((static_cast<u64>(from) << 32) | e[from].size());
		e[from].emplace_back(to, args...);
	}
	u32 size() const {return n;}
	using EDGE_TYPE = EDGE;
	using VERTEX_TYPE = VERTEX;
};
#line 3 "test/aoj/../../template/WeightedGraph.cpp"
using u32 = uint_fast32_t;
using i64 = int_fast64_t;
struct Vertex {};
template<class WEIGHT>
struct Edge {
	u32 to;
	WEIGHT weight;
	Edge(u32 x, WEIGHT w) : to(x), weight(w) {}
};
template<class WEIGHT>
struct WeightedGraph : public Graph<Edge<WEIGHT>, Vertex> {
	struct weighted_graph_tag {};
	WeightedGraph(u32 N) : Graph<Edge<WEIGHT>, Vertex>(N) {}
	using WEIGHT_TYPE = WEIGHT;
};
template<class WEIGHT = i64>
WeightedGraph<WEIGHT> make_weighted_graph(u32 N) {
	return WeightedGraph<WEIGHT>(N);
}
} // weighted_graph_n
using weighted_graph_n::WeightedGraph;
using weighted_graph_n::make_weighted_graph;
#line 10 "test/aoj/LCA.test.cpp"


vector<int> solve1(int V, const vector<vector<int>>& g, vector<int>& A, vector<int>& B) {
	vector<int> res;
	auto L = make_lca(V);
	for (int i = 0; i < V; i++) {
		for (auto x : g[i]) {
			L.add_edge(i, x);
			L.add_edge(x, i);
		}
	}
	L.build();
	for (size_t i = 0; i < A.size(); i++) {
		res.push_back(L.lca(A[i], B[i]));
	}
	return res;
}

vector<int> solve2(int V, const vector<vector<int>>& g, vector<int>& A, vector<int>& B) {
	vector<int> res;
	auto G = make_unweighted_graph(V);
	for (int i = 0; i < V; i++) {
		for (auto x : g[i]) {
			G.add_edge(i, x);
			G.add_edge(x, i);
		}
	}
	auto L = make_lca(G);
	L.build(0);
	for (size_t i = 0; i < A.size(); i++) {
		res.push_back(L.lca(A[i], B[i]));
	}
	return res;
}

vector<int> solve3(int V, const vector<vector<int>>& g, vector<int>& A, vector<int>& B) {
	vector<int> res;
	auto G = make_weighted_graph(V);
	for (int i = 0; i < V; i++) {
		for (auto x : g[i]) {
			G.add_edge(i, x, 1);
			G.add_edge(x, i, 1);
		}
	}
	auto L = make_lca(G);
	L.build(0);
	for (size_t i = 0; i < A.size(); i++) {
		res.push_back(L.lca(A[i], B[i]));
	}
	return res;
}

int main() {
	int V; cin >> V;
	vector<vector<int>> g(V);
	for (int i = 0; i < V; i++) {
		int k;
		cin >> k;
		for (int j = 0; j < k; j++) {
			int v;
			cin >> v;
			g[i].push_back(v);
		}
	}
	int Q; cin >> Q;
	vector<int> A, B;
	for (int i = 0; i < Q; i++) {
		int u, v; cin >> u >> v;
		A.push_back(u);
		B.push_back(v);
	}
	auto r1 = solve1(V, g, A, B);
	auto r2 = solve2(V, g, A, B);
	auto r3 = solve3(V, g, A, B);
	assert(r1 == r2);
	assert(r1 == r3);
	for (auto x : r2) {
		cout << x << endl;
	}
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

