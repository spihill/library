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


# :heavy_check_mark: template/UnWeightedRevEdgeGraph.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#66f6181bcb4cff4cd38fbc804a036db6">template</a>
* <a href="{{ site.github.repository_url }}/blob/master/template/UnWeightedRevEdgeGraph.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-24 00:56:25+09:00




## Depends on

* :heavy_check_mark: <a href="RevEdgeGraph.cpp.html">template/RevEdgeGraph.cpp</a>


## Required by

* :heavy_check_mark: <a href="../graph/SCC.cpp.html">graph/SCC.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/yosupo/SCC.test.cpp.html">test/yosupo/SCC.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
namespace unweighted_revedge_graph_n {
#include "RevEdgeGraph.cpp"
using u32 = uint_fast32_t;
struct Vertex {};
struct Edge {
	u32 to;
	Edge(u32 x) : to(x) {}
};
using UnWeightedRevEdgeGraph = RevEdgeGraph<Edge, Vertex>;
UnWeightedRevEdgeGraph make_unweighted_graph(u32 N) {
	return UnWeightedRevEdgeGraph(N);
}
}
using unweighted_revedge_graph_n::UnWeightedRevEdgeGraph;
using unweighted_revedge_graph_n::make_unweighted_graph;
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "template/UnWeightedRevEdgeGraph.cpp"
namespace unweighted_revedge_graph_n {
#line 1 "template/RevEdgeGraph.cpp"
template<class EDGE, class VERTEX>
struct RevEdgeGraph {
	using u32 = uint_fast32_t;
	using u64 = uint_fast64_t;
	struct graph_tag {};
	struct revedge_graph_tag {};
	const u32 n;
	vector<vector<EDGE>> e;
	vector<vector<EDGE>> re;
	vector<VERTEX> v;
	vector<u64> idx;
	vector<u64> ridx;
	RevEdgeGraph(u32 N) : n(N), e(n), re(n), v(n) {}
	template<class...  Args> void add_edge(u32 from, u32 to, Args... args) {
		idx.push_back((static_cast<u64>(from) << 32) | e[from].size());
		e[from].emplace_back(to, args...);
		idx.push_back((static_cast<u64>(from) << 32) | re[to].size());
		re[to].emplace_back(from, args...);
	}
	u32 size() const {return n;}
	using EDGE_TYPE = EDGE;
	using VERTEX_TYPE = VERTEX;
};
#line 3 "template/UnWeightedRevEdgeGraph.cpp"
using u32 = uint_fast32_t;
struct Vertex {};
struct Edge {
	u32 to;
	Edge(u32 x) : to(x) {}
};
using UnWeightedRevEdgeGraph = RevEdgeGraph<Edge, Vertex>;
UnWeightedRevEdgeGraph make_unweighted_graph(u32 N) {
	return UnWeightedRevEdgeGraph(N);
}
}
using unweighted_revedge_graph_n::UnWeightedRevEdgeGraph;
using unweighted_revedge_graph_n::make_unweighted_graph;

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

