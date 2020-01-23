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
    - Last commit date: 2020-01-24 00:56:25+09:00




## Depends on

* :heavy_check_mark: <a href="../for_include/has_shortest_path_graph_tag.cpp.html">for_include/has_shortest_path_graph_tag.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/Bellmanford.test.cpp.html">test/aoj/Bellmanford.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
namespace bellman_n {
using u32 = uint_fast32_t;
#include "../for_include/has_shortest_path_graph_tag.cpp"
template<class Graph, class WEIGHT = typename Graph::WEIGHT_TYPE>
enable_if_t<has_shortest_path_graph_tag_v<Graph>> Bellmanford(Graph& G, u32 start, WEIGHT INF_COST) {
	for (u32 i = 0; i < G.size(); i++) {
		G.dist(i) = INF_COST;
		G.valid(i) = false;
	}
	auto& e = G.e;
	G.dist(start) = 0, G.valid(start) = 1;
	for (u32 i = 0; i + 1 < G.size(); i++) {
		for (u32 j = 0; j < G.size(); j++) {
			for (auto& x : e[j]) {
				if (G.dist(j) == INF_COST) continue;
				G.dist(x.to) = min(G.dist(x.to), G.dist(j) + x.weight);
				G.valid(x.to) = true;
			}
		}
	}
	auto valid_check = [&](auto&& f, int pos) {
		if (!G.valid(pos)) return;
		G.valid(pos) = false;
		for (auto& x: e[pos]) {
			f(f, x.to);
		}
	};
	for (u32 i = 0; i < G.size(); i++) {
		for (auto& x : e[i]) {
			if (G.dist(i) == INF_COST) continue;
			if (G.dist(x.to) > G.dist(i) + x.weight) {
				valid_check(valid_check, x.to);
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
using u32 = uint_fast32_t;
#line 1 "graph/../for_include/has_shortest_path_graph_tag.cpp"
template <class T>
class has_shortest_path_graph_tag {
	template <class U, typename O = typename U::shortest_path_graph_tag> static constexpr std::true_type check(int);
	template <class U> static constexpr std::false_type check(long);
public:
	static constexpr bool value = decltype(check<T>(0))::value;
};
template <class T> constexpr bool has_shortest_path_graph_tag_v = has_shortest_path_graph_tag<T>::value;#line 4 "graph/Bellmanford.cpp"
template<class Graph, class WEIGHT = typename Graph::WEIGHT_TYPE>
enable_if_t<has_shortest_path_graph_tag_v<Graph>> Bellmanford(Graph& G, u32 start, WEIGHT INF_COST) {
	for (u32 i = 0; i < G.size(); i++) {
		G.dist(i) = INF_COST;
		G.valid(i) = false;
	}
	auto& e = G.e;
	G.dist(start) = 0, G.valid(start) = 1;
	for (u32 i = 0; i + 1 < G.size(); i++) {
		for (u32 j = 0; j < G.size(); j++) {
			for (auto& x : e[j]) {
				if (G.dist(j) == INF_COST) continue;
				G.dist(x.to) = min(G.dist(x.to), G.dist(j) + x.weight);
				G.valid(x.to) = true;
			}
		}
	}
	auto valid_check = [&](auto&& f, int pos) {
		if (!G.valid(pos)) return;
		G.valid(pos) = false;
		for (auto& x: e[pos]) {
			f(f, x.to);
		}
	};
	for (u32 i = 0; i < G.size(); i++) {
		for (auto& x : e[i]) {
			if (G.dist(i) == INF_COST) continue;
			if (G.dist(x.to) > G.dist(i) + x.weight) {
				valid_check(valid_check, x.to);
			}
		}
	}
}
}
using bellman_n::Bellmanford;
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

