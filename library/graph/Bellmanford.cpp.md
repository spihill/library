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


# :heavy_check_mark: graph/Bellmanford.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/Bellmanford.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-22 01:17:18+09:00




## Depends on

* :heavy_check_mark: <a href="../for_include/has_shortest_path_graph_tag.cpp.html">for_include/has_shortest_path_graph_tag.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/Bellmanford.test.cpp.html">test/aoj/Bellmanford.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
namespace bellman_n {
#include "../for_include/has_shortest_path_graph_tag.cpp"
template<class Graph, class V, class W = typename Graph::weight_type>
enable_if_t<has_shortest_path_graph_tag_v<Graph>> Bellmanford(Graph& G, V Start, W INF_COST) {
	size_t start = Graph::index(Start);
	auto& dist = G.dist;
	auto& valid = G.valid;
	auto& edge = G.edge;
	auto& weight = G.weight;
	for (auto& d : dist) d = INF_COST;
	for (auto& v: valid) v = 0;
	dist[start] = 0, valid[start] = 1;
	for (size_t i = 0; i + 1 < G.size(); i++) {
		for (size_t j = 0; j < G.size(); j++) {
			for (size_t k = 0; k < edge[j].size(); k++) {
				if (dist[j] == INF_COST) continue;
				dist[edge[j][k]] = min(dist[edge[j][k]], dist[j] + weight[j][k]);
				valid[edge[j][k]] = true;
			}
		}
	}
	auto valid_check = [&](auto f, int pos) {
		if (!valid[pos]) return;
		valid[pos] = false;
		for (auto& y: edge[pos]) {
			f(f, y);
		}
	};
	for (size_t i = 0; i < G.size(); i++) {
		for (size_t j = 0; j < edge[i].size(); j++) {
			if (dist[i] == INF_COST) continue;
			if (dist[edge[i][j]] > dist[i] + weight[i][j]) {
				valid_check(valid_check, edge[i][j]);
			}
		}
	}
}
}
using bellman_n::Bellmanford;
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/Bellmanford.cpp"
namespace bellman_n {
#line 1 "graph/../for_include/has_shortest_path_graph_tag.cpp"
template <class T>
class has_shortest_path_graph_tag {
	template <class U, typename O = typename U::shortest_path_graph_tag> static constexpr std::true_type check(int);
	template <class U> static constexpr std::false_type check(long);
public:
	static constexpr bool value = decltype(check<T>(0))::value;
};
template <class T> constexpr bool has_shortest_path_graph_tag_v = has_shortest_path_graph_tag<T>::value;#line 3 "graph/Bellmanford.cpp"
template<class Graph, class V, class W = typename Graph::weight_type>
enable_if_t<has_shortest_path_graph_tag_v<Graph>> Bellmanford(Graph& G, V Start, W INF_COST) {
	size_t start = Graph::index(Start);
	auto& dist = G.dist;
	auto& valid = G.valid;
	auto& edge = G.edge;
	auto& weight = G.weight;
	for (auto& d : dist) d = INF_COST;
	for (auto& v: valid) v = 0;
	dist[start] = 0, valid[start] = 1;
	for (size_t i = 0; i + 1 < G.size(); i++) {
		for (size_t j = 0; j < G.size(); j++) {
			for (size_t k = 0; k < edge[j].size(); k++) {
				if (dist[j] == INF_COST) continue;
				dist[edge[j][k]] = min(dist[edge[j][k]], dist[j] + weight[j][k]);
				valid[edge[j][k]] = true;
			}
		}
	}
	auto valid_check = [&](auto f, int pos) {
		if (!valid[pos]) return;
		valid[pos] = false;
		for (auto& y: edge[pos]) {
			f(f, y);
		}
	};
	for (size_t i = 0; i < G.size(); i++) {
		for (size_t j = 0; j < edge[i].size(); j++) {
			if (dist[i] == INF_COST) continue;
			if (dist[edge[i][j]] > dist[i] + weight[i][j]) {
				valid_check(valid_check, edge[i][j]);
			}
		}
	}
}
}
using bellman_n::Bellmanford;
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

