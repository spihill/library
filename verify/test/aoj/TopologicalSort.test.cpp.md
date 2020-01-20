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
    - Last commit date: 2020-01-21 01:10:37+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/4/GRL_4_B">https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/4/GRL_4_B</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/graph/TopologicalSort.cpp.html">トポロジカルソート</a>
* :heavy_check_mark: <a href="../../../library/helper/tag.cpp.html">helper/tag.cpp</a>
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
	int V, E; cin >> V >> E;
	auto G = make_unweighted_graph(V); 
	for (int i = 0; i < E; i++) {
		int v, u; cin >> v >> u;
		G.add_edge(v, u);
	}
	auto res = TopologicalSort(G);
	for (auto& x : res) cout << x << endl;

	assert((int) res.size() == V);
	assert(1 <= V && V <= 10000);
	assert(0 <= E && E <= 100000);
	vector<int> idx(V);
	for (int i = 0; i < V; i++) {
		idx.at(res.at(i)) = i;
	}
	for (int i = 0; i < V; i++) {
		for (auto& x: G.edge.at(i)) {
			assert(idx.at(i) < idx.at(x));
		}
	}
	sort(res.begin(), res.end());
	res.erase(unique(res.begin(), res.end()), res.end());
	assert((int)res.size() == V);
	for (int i = 0; i < V; i++) {
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
#line 1 "test/aoj/../../graph/../helper/tag.cpp"
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
template <class T> constexpr bool has_weighted_graph_tag_v = has_weighted_graph_tag<T>::value;

template <class T>
class has_shortest_path_graph_tag {
	template <class U, typename O = typename U::shortest_path_graph_tag> static constexpr std::true_type check(int);
	template <class U> static constexpr std::false_type check(long);
public:
	static constexpr bool value = decltype(check<T>(0))::value;
};
template <class T> constexpr bool has_shortest_path_graph_tag_v = has_shortest_path_graph_tag<T>::value;#line 10 "test/aoj/../../graph/TopologicalSort.cpp"
template<class Graph, class V = typename Graph::vertex_type>
enable_if_t<has_graph_tag_v<Graph>, vector<V>> TopologicalSort(Graph& G) {
	const size_t n = G.size();
	auto& e = G.edge;
	vector<char> visited(n, 0);
	vector<V> res;
	auto dfs = [&](auto&& dfs, int v) -> void {
		visited[v] = true;
		for (auto& x : e[v]) {
			if (!visited[x]) dfs(dfs, x);
		}
		res.push_back(Graph::restore(v));
	};
	for (size_t i = 0; i < n; i++) {
		if (!visited[i]) dfs(dfs, i);
	}
	if (res.size() < n) return vector<V>(0);
	reverse(res.begin(), res.end());
	return move(res);
}
} // namespace topological_sort_n
using topological_sort_n::TopologicalSort;#line 1 "test/aoj/../../template/UnWeightedGraph.cpp"
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
};
template<class T = long long>
UnWeightedGraph<T> make_unweighted_graph(size_t N) {
	return move(UnWeightedGraph<T>(N));
}#line 8 "test/aoj/TopologicalSort.test.cpp"

int main() {
	int V, E; cin >> V >> E;
	auto G = make_unweighted_graph(V); 
	for (int i = 0; i < E; i++) {
		int v, u; cin >> v >> u;
		G.add_edge(v, u);
	}
	auto res = TopologicalSort(G);
	for (auto& x : res) cout << x << endl;

	assert((int) res.size() == V);
	assert(1 <= V && V <= 10000);
	assert(0 <= E && E <= 100000);
	vector<int> idx(V);
	for (int i = 0; i < V; i++) {
		idx.at(res.at(i)) = i;
	}
	for (int i = 0; i < V; i++) {
		for (auto& x: G.edge.at(i)) {
			assert(idx.at(i) < idx.at(x));
		}
	}
	sort(res.begin(), res.end());
	res.erase(unique(res.begin(), res.end()), res.end());
	assert((int)res.size() == V);
	for (int i = 0; i < V; i++) {
		assert(i == res.at(i));
	}
}
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

