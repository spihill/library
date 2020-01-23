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


# :heavy_check_mark: graph_tree/Diameter.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f93f3ae32620f7630b3615eae399affa">graph_tree</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph_tree/Diameter.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-24 01:14:30+09:00




## Depends on

* :heavy_check_mark: <a href="../for_include/has_weighted_graph_tag.cpp.html">for_include/has_weighted_graph_tag.cpp</a>
* :heavy_check_mark: <a href="../template/Graph.cpp.html">template/Graph.cpp</a>
* :heavy_check_mark: <a href="../template/WeightedGraph.cpp.html">template/WeightedGraph.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/Diameter.test.cpp.html">test/aoj/Diameter.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
namespace diameter_n {
#include "../template/WeightedGraph.cpp"
#include "../for_include/has_weighted_graph_tag.cpp"
using u32 = uint_fast32_t;
template<class Graph, class WEIGHT = typename Graph::WEIGHT_TYPE>
WEIGHT Diameter(Graph& G) {
	auto dfs = [&](auto f, u32 start, u32& goal, u32 par = numeric_limits<u32>::max()) -> WEIGHT {
		goal = start;
		WEIGHT res = 0;
		for (auto& i: G.e[start]) {
			if (i.to == par) continue;
			u32 t;
			WEIGHT r = f(f, i.to, t, start);
			r += i.weight;
			if (r > res) {
				res = r;
				goal = t;
			}
		}
		return res;
	};
	u32 g;
	dfs(dfs, 0, g);
	return dfs(dfs, g, g);
}
}
using diameter_n::Diameter;
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph_tree/Diameter.cpp"
namespace diameter_n {
#line 1 "graph_tree/../template/WeightedGraph.cpp"
namespace weighted_graph_n{
#line 1 "graph_tree/../template/Graph.cpp"
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
};#line 3 "graph_tree/../template/WeightedGraph.cpp"
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
using weighted_graph_n::make_weighted_graph;#line 1 "graph_tree/../for_include/has_weighted_graph_tag.cpp"
template <class T>
class has_weighted_graph_tag {
	template <class U, typename O = typename U::weighted_graph_tag> static constexpr std::true_type check(int);
	template <class U> static constexpr std::false_type check(long);
public:
	static constexpr bool value = decltype(check<T>(0))::value;
};
template <class T> constexpr bool has_weighted_graph_tag_v = has_weighted_graph_tag<T>::value;#line 4 "graph_tree/Diameter.cpp"
using u32 = uint_fast32_t;
template<class Graph, class WEIGHT = typename Graph::WEIGHT_TYPE>
WEIGHT Diameter(Graph& G) {
	auto dfs = [&](auto f, u32 start, u32& goal, u32 par = numeric_limits<u32>::max()) -> WEIGHT {
		goal = start;
		WEIGHT res = 0;
		for (auto& i: G.e[start]) {
			if (i.to == par) continue;
			u32 t;
			WEIGHT r = f(f, i.to, t, start);
			r += i.weight;
			if (r > res) {
				res = r;
				goal = t;
			}
		}
		return res;
	};
	u32 g;
	dfs(dfs, 0, g);
	return dfs(dfs, g, g);
}
}
using diameter_n::Diameter;
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

