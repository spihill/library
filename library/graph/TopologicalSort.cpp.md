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


# :heavy_check_mark: トポロジカルソート

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/TopologicalSort.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-20 23:28:38+09:00


* グラフが DAG であるとき、頂点のトポロジカル順序を求める。
* 戻り値は、トポロジカル順序に並んだ頂点番号の列。
* DAG でないときは戻り値は空の vector になる。
* AOJ では模範解を下のようなアルゴリズムで作っているらしく、Output が完全に一致する。


## Depends on

* :heavy_check_mark: <a href="../for_include/make_graph.cpp.html">for_include/make_graph.cpp</a>
* :heavy_check_mark: <a href="../helper/tag.cpp.html">helper/tag.cpp</a>
* :heavy_check_mark: <a href="../template/UnWeightedGraph.cpp.html">template/UnWeightedGraph.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/TopologicalSort.test.cpp.html">test/aoj/TopologicalSort.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * @title トポロジカルソート
 * @brief グラフが DAG であるとき、頂点のトポロジカル順序を求める。
 * @brief 戻り値は、トポロジカル順序に並んだ頂点番号の列。
 * @brief DAG でないときは戻り値は空の vector になる。
 * @brief AOJ では模範解を下のようなアルゴリズムで作っているらしく、Output が完全に一致する。
 */
namespace topological_sort_n {
#include "../template/UnWeightedGraph.cpp"
#include "../helper/tag.cpp"
template<class T> using graph = UnWeightedGraph<T>;
#include "../for_include/make_graph.cpp"
template<class T>
enable_if_t<has_graph_tag_v<graph<T>>, vector<int>> TopologicalSort(graph<T>& G) {
	const size_t V = G.size();
	auto& e = G.edge;
	vector<char> visited(V, 0);
	vector<int> res;
	auto dfs = [&](auto&& dfs, int v) -> void {
		visited[v] = true;
		for (auto& x : e[v]) {
			if (!visited[x]) dfs(dfs, x);
		}
		res.push_back(v);
	};
	for (size_t i = 0; i < V; i++) {
		if (!visited[i]) dfs(dfs, i);
	}
	if (res.size() < V) return vector<int>(0);
	reverse(res.begin(), res.end());
	return move(res);
}
} // namespace topological_sort_n
template<class T = long long> using graph = topological_sort_n::graph<T>;
using topological_sort_n::make_graph;
using topological_sort_n::TopologicalSort;
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/TopologicalSort.cpp"
/**
 * @title トポロジカルソート
 * @brief グラフが DAG であるとき、頂点のトポロジカル順序を求める。
 * @brief 戻り値は、トポロジカル順序に並んだ頂点番号の列。
 * @brief DAG でないときは戻り値は空の vector になる。
 * @brief AOJ では模範解を下のようなアルゴリズムで作っているらしく、Output が完全に一致する。
 */
namespace topological_sort_n {
#line 1 "graph/../template/UnWeightedGraph.cpp"
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
}#line 1 "graph/../helper/tag.cpp"
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
template <class T> constexpr bool has_weighted_graph_tag_v = has_weighted_graph_tag<T>::value;#line 11 "graph/TopologicalSort.cpp"
template<class T> using graph = UnWeightedGraph<T>;
#line 1 "graph/../for_include/make_graph.cpp"
template<class T = long long>
graph<T> make_graph(size_t N) {
	return move(graph<T>(N));
}#line 13 "graph/TopologicalSort.cpp"
template<class T>
enable_if_t<has_graph_tag_v<graph<T>>, vector<int>> TopologicalSort(graph<T>& G) {
	const size_t V = G.size();
	auto& e = G.edge;
	vector<char> visited(V, 0);
	vector<int> res;
	auto dfs = [&](auto&& dfs, int v) -> void {
		visited[v] = true;
		for (auto& x : e[v]) {
			if (!visited[x]) dfs(dfs, x);
		}
		res.push_back(v);
	};
	for (size_t i = 0; i < V; i++) {
		if (!visited[i]) dfs(dfs, i);
	}
	if (res.size() < V) return vector<int>(0);
	reverse(res.begin(), res.end());
	return move(res);
}
} // namespace topological_sort_n
template<class T = long long> using graph = topological_sort_n::graph<T>;
using topological_sort_n::make_graph;
using topological_sort_n::TopologicalSort;
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

