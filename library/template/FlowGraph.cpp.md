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


# :heavy_check_mark: template/FlowGraph.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#66f6181bcb4cff4cd38fbc804a036db6">template</a>
* <a href="{{ site.github.repository_url }}/blob/master/template/FlowGraph.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-22 00:10:19+09:00




## Depends on

* :heavy_check_mark: <a href="UnWeightedGraph.cpp.html">template/UnWeightedGraph.cpp</a>


## Required by

* :heavy_check_mark: <a href="../graph/Dinic.cpp.html">最大流 (Dinic)</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/Dinic.test.cpp.html">test/aoj/Dinic.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
namespace flow_graph_n{
#include "UnWeightedGraph.cpp"
template<class VertexType = long long, class CapacityType = long long>
struct FlowGraph : UnWeightedGraph<VertexType> {
	using UnWeightedGraph<VertexType>::index;
	using UnWeightedGraph<VertexType>::restore;
	using UnWeightedGraph<VertexType>::size;
	struct flow_graph_tag {};
	vector<vector<CapacityType>> capacity;
	vector<vector<size_t>> revedge;
	FlowGraph(size_t N) : UnWeightedGraph<VertexType>(N), capacity(N), revedge(N) {}
	template<class T, class U> void add_edge(T from, U to, CapacityType c) {
		this->edge[index(from)].push_back(index(to));
		capacity[index(from)].push_back(c);
		revedge[index(from)].push_back(this->edge[index(to)].size());

		this->edge[index(to)].push_back(index(from));
		capacity[index(to)].push_back(CapacityType());
		revedge[index(to)].push_back(this->edge[index(from)].size()-1);
	}
	void clear() {
		this->edge.clear();
		capacity.clear();
		revedge.clear();
	}
	using capacity_type = CapacityType;
};
template<class V = long long, class C = long long>
FlowGraph<V, C> make_flow_graph(size_t N) {
	return move(FlowGraph<V, C>(N));
}
} // weighted_graph_n
template<class V, class C> using FlowGraph = flow_graph_n::FlowGraph<V, C>;
using flow_graph_n::make_flow_graph;
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "template/FlowGraph.cpp"
namespace flow_graph_n{
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
}#line 3 "template/FlowGraph.cpp"
template<class VertexType = long long, class CapacityType = long long>
struct FlowGraph : UnWeightedGraph<VertexType> {
	using UnWeightedGraph<VertexType>::index;
	using UnWeightedGraph<VertexType>::restore;
	using UnWeightedGraph<VertexType>::size;
	struct flow_graph_tag {};
	vector<vector<CapacityType>> capacity;
	vector<vector<size_t>> revedge;
	FlowGraph(size_t N) : UnWeightedGraph<VertexType>(N), capacity(N), revedge(N) {}
	template<class T, class U> void add_edge(T from, U to, CapacityType c) {
		this->edge[index(from)].push_back(index(to));
		capacity[index(from)].push_back(c);
		revedge[index(from)].push_back(this->edge[index(to)].size());

		this->edge[index(to)].push_back(index(from));
		capacity[index(to)].push_back(CapacityType());
		revedge[index(to)].push_back(this->edge[index(from)].size()-1);
	}
	void clear() {
		this->edge.clear();
		capacity.clear();
		revedge.clear();
	}
	using capacity_type = CapacityType;
};
template<class V = long long, class C = long long>
FlowGraph<V, C> make_flow_graph(size_t N) {
	return move(FlowGraph<V, C>(N));
}
} // weighted_graph_n
template<class V, class C> using FlowGraph = flow_graph_n::FlowGraph<V, C>;
using flow_graph_n::make_flow_graph;
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

