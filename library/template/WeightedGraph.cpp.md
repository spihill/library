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


# :heavy_check_mark: template/WeightedGraph.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#66f6181bcb4cff4cd38fbc804a036db6">template</a>
* <a href="{{ site.github.repository_url }}/blob/master/template/WeightedGraph.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-21 01:10:37+09:00




## Depends on

* :heavy_check_mark: <a href="UnWeightedGraph.cpp.html">template/UnWeightedGraph.cpp</a>


## Required by

* :heavy_check_mark: <a href="../graph_tree/LCA.cpp.html">graph_tree/LCA.cpp</a>
* :heavy_check_mark: <a href="ShortestPathGraph.cpp.html">template/ShortestPathGraph.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/Bellmanford.test.cpp.html">test/aoj/Bellmanford.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/Dijkstra.test.cpp.html">test/aoj/Dijkstra.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/Dijkstra_2.test.cpp.html">test/aoj/Dijkstra_2.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/Dijkstra_3.test.cpp.html">test/aoj/Dijkstra_3.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/LCA.test.cpp.html">test/aoj/LCA.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
namespace weighted_graph_n{
#include "UnWeightedGraph.cpp"
template<class VertexType = long long, class WeightType = long long>
struct WeightedGraph : UnWeightedGraph<VertexType> {
	using UnWeightedGraph<VertexType>::index;
	using UnWeightedGraph<VertexType>::restore;
	using UnWeightedGraph<VertexType>::size;
	struct weighted_graph_tag {};
	vector<vector<WeightType>> weight;
	WeightedGraph(size_t N) : UnWeightedGraph<VertexType>(N), weight(N) {}
	template<class T, class U> void add_edge(T from, U to, WeightType w) {
		this->edge[index(from)].push_back(index(to));
		weight[index(from)].push_back(w);
	}
	void clear() {
		this->edge.clear();
		weight.clear();
	}
	using weight_type = WeightType;
};
template<class T = long long, class W = long long>
WeightedGraph<T, W> make_weighted_graph(size_t N) {
	return move(WeightedGraph<T, W>(N));
}
} // weighted_graph_n
template<class T, class W> using WeightedGraph = weighted_graph_n::WeightedGraph<T, W>;
using weighted_graph_n::make_weighted_graph;
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "template/WeightedGraph.cpp"
namespace weighted_graph_n{
#line 1 "template/UnWeightedGraph.cpp"
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
}#line 3 "template/WeightedGraph.cpp"
template<class VertexType = long long, class WeightType = long long>
struct WeightedGraph : UnWeightedGraph<VertexType> {
	using UnWeightedGraph<VertexType>::index;
	using UnWeightedGraph<VertexType>::restore;
	using UnWeightedGraph<VertexType>::size;
	struct weighted_graph_tag {};
	vector<vector<WeightType>> weight;
	WeightedGraph(size_t N) : UnWeightedGraph<VertexType>(N), weight(N) {}
	template<class T, class U> void add_edge(T from, U to, WeightType w) {
		this->edge[index(from)].push_back(index(to));
		weight[index(from)].push_back(w);
	}
	void clear() {
		this->edge.clear();
		weight.clear();
	}
	using weight_type = WeightType;
};
template<class T = long long, class W = long long>
WeightedGraph<T, W> make_weighted_graph(size_t N) {
	return move(WeightedGraph<T, W>(N));
}
} // weighted_graph_n
template<class T, class W> using WeightedGraph = weighted_graph_n::WeightedGraph<T, W>;
using weighted_graph_n::make_weighted_graph;
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

