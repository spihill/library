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
    - Last commit date: 2020-01-24 00:56:25+09:00




## Depends on

* :heavy_check_mark: <a href="RevGraph.cpp.html">template/RevGraph.cpp</a>


## Required by

* :heavy_check_mark: <a href="../graph/Dinic.cpp.html">最大流 (Dinic)</a>
* :heavy_check_mark: <a href="../graph/FordFulkerson.cpp.html">最大流 (Ford-Fulkerson)</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/Dinic.test.cpp.html">test/aoj/Dinic.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/FordFulkerson.test.cpp.html">test/aoj/FordFulkerson.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
namespace flow_graph_n{
#include "RevGraph.cpp"
using u32 = uint_fast32_t;
using i64 = int_fast64_t;
struct Vertex {};
template<class CAPACITY>
struct Edge {
	u32 to;
	u32 rev;
	CAPACITY capacity;
	Edge(u32 x, u32 y, CAPACITY c) : to(x), rev(y), capacity(c) {}
	Edge(u32 x, u32 y, CAPACITY c, int) : to(x), rev(y), capacity(0) {}
};
template<class CAPACITY = i64>
struct FlowGraph : RevGraph<Edge<CAPACITY>, Vertex> {
	struct flow_graph_tag {};
	FlowGraph(u32 N) : RevGraph<Edge<CAPACITY>, Vertex>(N) {}
	using CAPACITY_TYPE = CAPACITY;
};
template<class CAPACITY = i64>
FlowGraph<CAPACITY> make_flow_graph(u32 N) {
	return FlowGraph<CAPACITY>(N);
}
} // flow_graph_n
using flow_graph_n::FlowGraph;
using flow_graph_n::make_flow_graph;
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "template/FlowGraph.cpp"
namespace flow_graph_n{
#line 1 "template/RevGraph.cpp"
template<class EDGE, class VERTEX>
struct RevGraph {
	using u32 = uint_fast32_t;
	using u64 = uint_fast64_t;
	struct graph_tag {};
	struct rev_graph_tag {};
	const u32 n;
	vector<vector<EDGE>> e;
	vector<VERTEX> v;
	vector<u64> idx;
	RevGraph(u32 N) : n(N), e(n), v(n) {}
	template<class...  Args> void add_edge(u32 from, u32 to, Args... args) {
		idx.push_back((static_cast<u64>(from) << 32) | e[from].size());
		e[from].emplace_back(to, e[to].size(), args...);
		idx.push_back((static_cast<u64>(to) << 32) | e[to].size());
		e[to].emplace_back(from, e[from].size()-1, args..., 0);
	}
	u32 size() const {return n;}
	using EDGE_TYPE = EDGE;
	using VERTEX_TYPE = VERTEX;
};
#line 3 "template/FlowGraph.cpp"
using u32 = uint_fast32_t;
using i64 = int_fast64_t;
struct Vertex {};
template<class CAPACITY>
struct Edge {
	u32 to;
	u32 rev;
	CAPACITY capacity;
	Edge(u32 x, u32 y, CAPACITY c) : to(x), rev(y), capacity(c) {}
	Edge(u32 x, u32 y, CAPACITY c, int) : to(x), rev(y), capacity(0) {}
};
template<class CAPACITY = i64>
struct FlowGraph : RevGraph<Edge<CAPACITY>, Vertex> {
	struct flow_graph_tag {};
	FlowGraph(u32 N) : RevGraph<Edge<CAPACITY>, Vertex>(N) {}
	using CAPACITY_TYPE = CAPACITY;
};
template<class CAPACITY = i64>
FlowGraph<CAPACITY> make_flow_graph(u32 N) {
	return FlowGraph<CAPACITY>(N);
}
} // flow_graph_n
using flow_graph_n::FlowGraph;
using flow_graph_n::make_flow_graph;

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

