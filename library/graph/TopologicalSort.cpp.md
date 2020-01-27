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
    - Last commit date: 2020-01-27 18:45:58+09:00


* グラフが DAG であるとき、頂点のトポロジカル順序を求める。
* 戻り値は、トポロジカル順序に並んだ頂点番号の列。
* DAG でないときは戻り値は空の vector になる。
* AOJ では模範解を下のようなアルゴリズムで作っているらしく、Output が完全に一致する。


## Depends on

* :heavy_check_mark: <a href="../for_include/has_graph_tag.cpp.html">for_include/has_graph_tag.cpp</a>


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
#include "../for_include/has_graph_tag.cpp"
using u32 = uint_fast32_t;
template<class Graph>
enable_if_t<has_graph_tag_v<Graph>, vector<u32>> TopologicalSort(const Graph& G) {
	const size_t n = G.size();
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
	for (size_t i = 0; i < n; i++) {
		if (!visited[i]) dfs(dfs, i);
	}
	if (res.size() < n) return vector<u32>(0);
	reverse(res.begin(), res.end());
	return move(res);
}
} // namespace topological_sort_n

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
#line 1 "graph/../for_include/has_graph_tag.cpp"
template <class T>
class has_graph_tag {
	template <class U> static constexpr std::true_type check(typename U::graph_tag*);
	template <class U> static constexpr std::false_type check(...);
public:
	static constexpr bool value = decltype(check<T>(nullptr))::value;
};
template <class T> constexpr bool has_graph_tag_v = has_graph_tag<T>::value;#line 10 "graph/TopologicalSort.cpp"
using u32 = uint_fast32_t;
template<class Graph>
enable_if_t<has_graph_tag_v<Graph>, vector<u32>> TopologicalSort(const Graph& G) {
	const size_t n = G.size();
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
	for (size_t i = 0; i < n; i++) {
		if (!visited[i]) dfs(dfs, i);
	}
	if (res.size() < n) return vector<u32>(0);
	reverse(res.begin(), res.end());
	return move(res);
}
} // namespace topological_sort_n

using topological_sort_n::TopologicalSort;
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

