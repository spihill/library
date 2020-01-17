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
    - Last commit date: 2020-01-17 13:24:36+09:00


* グラフが DAG であるとき、頂点のトポロジカル順序を求める。
* 戻り値は、トポロジカル順序に並んだ頂点番号の列。
* DAG でないときは戻り値は空の vector になる。
* AOJ では模範解を下のようなアルゴリズムで作っているらしく、Output が完全に一致する。


## Depends on

* :heavy_check_mark: <a href="../for_include/vec.cpp.html">for_include/vec.cpp</a>
* :heavy_check_mark: <a href="../snippet/Edge.cpp.html">snippet/Edge.cpp</a>


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
#include "../snippet/Edge.cpp"
vector<int> TopologicalSort(Edges& e) {
	const size_t V = e.size();
	vector<char> visited(V, 0);
	vector<int> res;
	auto dfs = [&](auto&& dfs, int v) -> void {
		visited[v] = true;
		for (auto& x : e[v]) {
			if (!visited[x.to]) dfs(dfs, x.to);
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
using graph = topological_sort_n::Edges;
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
#line 1 "graph/../snippet/Edge.cpp"
struct Edge {
	int to;
	Edge(int t) : to(t) {}
};
struct Edges : private vector<vector<Edge>> {
	using type = vector<vector<Edge>>;
	void add_edge(int u, int v) {
		(*this)[u].emplace_back(v);
	}
	template<class... Args> Edges(Args... args) : vector<vector<Edge>>(args...) {}
#line 1 "graph/../snippet/../for_include/vec.cpp"
	using type::begin; using type::end; using type::rbegin; using type::rend;
	using type::cbegin; using type::cend; using type::crbegin; using type::crend;
	using type::size; using type::operator[]; using type::at; using type::back; using type::front;
	using type::reserve; using type::resize; using type::assign; using type::shrink_to_fit;
	using type::clear; using type::erase; using type::insert; using type::swap; 
	using type::push_back; using type::pop_back; using type::emplace_back; using type::empty;
	using typename vector<typename type::value_type, allocator<typename type::value_type>>::iterator;#line 12 "graph/../snippet/Edge.cpp"
};#line 10 "graph/TopologicalSort.cpp"
vector<int> TopologicalSort(Edges& e) {
	const size_t V = e.size();
	vector<char> visited(V, 0);
	vector<int> res;
	auto dfs = [&](auto&& dfs, int v) -> void {
		visited[v] = true;
		for (auto& x : e[v]) {
			if (!visited[x.to]) dfs(dfs, x.to);
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
using graph = topological_sort_n::Edges;
using topological_sort_n::TopologicalSort;
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

