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


# :heavy_check_mark: graph/Dijkstra.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/Dijkstra.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-24 00:56:25+09:00




## Depends on

* :heavy_check_mark: <a href="../for_include/has_shortest_path_graph_tag.cpp.html">for_include/has_shortest_path_graph_tag.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/Dijkstra.test.cpp.html">test/aoj/Dijkstra.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/Dijkstra_2.test.cpp.html">test/aoj/Dijkstra_2.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/Dijkstra_3.test.cpp.html">test/aoj/Dijkstra_3.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
namespace dijkstra_n {
using u32 = uint_fast32_t;
#include "../for_include/has_shortest_path_graph_tag.cpp"
template<class Graph, class WEIGHT = typename Graph::WEIGHT_TYPE>
enable_if_t<has_shortest_path_graph_tag_v<Graph>> Dijkstra(Graph& G, u32 start, WEIGHT INF_COST) {
	auto& e = G.e;
	for (u32 i = 0; i < G.size(); i++) {
		G.dist(i) = INF_COST;
		G.valid(i) = false;
	}
	using Q_T = pair<WEIGHT, int>;
	priority_queue<Q_T, vector<Q_T>, greater<>> q;
	q.emplace(WEIGHT(0), start);
	while (!q.empty()) {
		auto a = q.top(); q.pop();
		G.valid(a.second) = 1;
		if (a.first >= G.dist(a.second)) continue;
		G.dist(a.second) = a.first;
		for (auto& x : e[a.second]) {
			if (x.weight == INF_COST) continue;
			if (a.first + x.weight < G.dist(x.to)) q.emplace(a.first + x.weight, x.to);
		}
	}
}
}
using dijkstra_n::Dijkstra;
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/Dijkstra.cpp"
namespace dijkstra_n {
using u32 = uint_fast32_t;
#line 1 "graph/../for_include/has_shortest_path_graph_tag.cpp"
template <class T>
class has_shortest_path_graph_tag {
	template <class U, typename O = typename U::shortest_path_graph_tag> static constexpr std::true_type check(int);
	template <class U> static constexpr std::false_type check(long);
public:
	static constexpr bool value = decltype(check<T>(0))::value;
};
template <class T> constexpr bool has_shortest_path_graph_tag_v = has_shortest_path_graph_tag<T>::value;#line 4 "graph/Dijkstra.cpp"
template<class Graph, class WEIGHT = typename Graph::WEIGHT_TYPE>
enable_if_t<has_shortest_path_graph_tag_v<Graph>> Dijkstra(Graph& G, u32 start, WEIGHT INF_COST) {
	auto& e = G.e;
	for (u32 i = 0; i < G.size(); i++) {
		G.dist(i) = INF_COST;
		G.valid(i) = false;
	}
	using Q_T = pair<WEIGHT, int>;
	priority_queue<Q_T, vector<Q_T>, greater<>> q;
	q.emplace(WEIGHT(0), start);
	while (!q.empty()) {
		auto a = q.top(); q.pop();
		G.valid(a.second) = 1;
		if (a.first >= G.dist(a.second)) continue;
		G.dist(a.second) = a.first;
		for (auto& x : e[a.second]) {
			if (x.weight == INF_COST) continue;
			if (a.first + x.weight < G.dist(x.to)) q.emplace(a.first + x.weight, x.to);
		}
	}
}
}
using dijkstra_n::Dijkstra;
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

