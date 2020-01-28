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


# :heavy_check_mark: test/aoj/TopologicalSort.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/TopologicalSort.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-29 00:41:13+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/4/GRL_4_B">https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/4/GRL_4_B</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/for_include/has_graph_tag.cpp.html">for_include/has_graph_tag.cpp</a>
* :heavy_check_mark: <a href="../../../library/graph/TopologicalSort.cpp.html">トポロジカルソート</a>
* :heavy_check_mark: <a href="../../../library/template/Graph.cpp.html">template/Graph.cpp</a>
* :heavy_check_mark: <a href="../../../library/template/UnWeightedGraph.cpp.html">template/UnWeightedGraph.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/4/GRL_4_B"
#include<bits/stdc++.h>

using namespace std;

#include "../../graph/TopologicalSort.cpp"
#include "../../template/UnWeightedGraph.cpp"

int main() {
	size_t V, E; cin >> V >> E;
	auto G = make_unweighted_graph(V); 
	for (size_t i = 0; i < E; i++) {
		int v, u; cin >> v >> u;
		G.add_edge(v, u);
	}
	auto res = TopologicalSort(G);
	for (auto& x : res) cout << x << endl;

	assert(res.size() == V);
	assert(1 <= V && V <= 10000);
	assert(0 <= E && E <= 100000);
	vector<int> idx(V);
	for (size_t i = 0; i < V; i++) {
		idx.at(res.at(i)) = i;
	}
	for (size_t i = 0; i < V; i++) {
		for (auto& x: G.e.at(i)) {
			assert(idx.at(i) < idx.at(x.to));
		}
	}
	sort(res.begin(), res.end());
	res.erase(unique(res.begin(), res.end()), res.end());
	assert((int)res.size() == V);
	for (size_t i = 0; i < V; i++) {
		assert(i == res.at(i));
	}
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj/TopologicalSort.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/4/GRL_4_B"
#include<bits/stdc++.h>

using namespace std;

#line 1 "test/aoj/../../graph/TopologicalSort.cpp"
/**
 * @title トポロジカルソート
 * @brief グラフが DAG であるとき、頂点のトポロジカル順序を求める。
 * @brief 戻り値は、トポロジカル順序に並んだ頂点番号の列。
 * @brief DAG でないときは戻り値は空の vector になる。
 * @brief AOJ では模範解を下のようなアルゴリズムで作っているらしく、Output が完全に一致する。
 */
namespace topological_sort_n {
#line 1 "test/aoj/../../graph/../for_include/has_graph_tag.cpp"
template <class T>
class has_graph_tag {
	template <class U> static constexpr std::true_type check(typename U::graph_tag*);
	template <class U> static constexpr std::false_type check(...);
public:
	static constexpr bool value = decltype(check<T>(nullptr))::value;
};
template <class T> constexpr bool has_graph_tag_v = has_graph_tag<T>::value;#line 10 "test/aoj/../../graph/TopologicalSort.cpp"
using u32 = uint_fast32_t;
template<class Graph>
enable_if_t<has_graph_tag_v<Graph>, vector<u32>> TopologicalSort(const Graph& G) {
	const u32 n = G.size();
	auto& e = G.e;
	vector<char> visited(n, 0);
	vector<u32> res;
	auto dfs = [&](auto&& dfs, int v) -> void {
		visited[v] = true;
		for (auto& x : e[v]) {
			if (!visited[x.to]) dfs(dfs, x.to);
		}
		res.push_back(v);
	};
	for (u32 i = 0; i < n; i++) {
		if (!visited[i]) dfs(dfs, i);
	}
	if (res.size() < n) return vector<u32>(0);
	reverse(res.begin(), res.end());
	return move(res);
}
} // namespace topological_sort_n

using topological_sort_n::TopologicalSort;#line 1 "test/aoj/../../template/UnWeightedGraph.cpp"
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
};#line 3 "test/aoj/../../template/UnWeightedGraph.cpp"
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
using unweighted_graph_n::make_unweighted_graph;#line 8 "test/aoj/TopologicalSort.test.cpp"

int main() {
	size_t V, E; cin >> V >> E;
	auto G = make_unweighted_graph(V); 
	for (size_t i = 0; i < E; i++) {
		int v, u; cin >> v >> u;
		G.add_edge(v, u);
	}
	auto res = TopologicalSort(G);
	for (auto& x : res) cout << x << endl;

	assert(res.size() == V);
	assert(1 <= V && V <= 10000);
	assert(0 <= E && E <= 100000);
	vector<int> idx(V);
	for (size_t i = 0; i < V; i++) {
		idx.at(res.at(i)) = i;
	}
	for (size_t i = 0; i < V; i++) {
		for (auto& x: G.e.at(i)) {
			assert(idx.at(i) < idx.at(x.to));
		}
	}
	sort(res.begin(), res.end());
	res.erase(unique(res.begin(), res.end()), res.end());
	assert((int)res.size() == V);
	for (size_t i = 0; i < V; i++) {
		assert(i == res.at(i));
	}
}
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

