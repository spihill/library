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


# :heavy_check_mark: for_include/compare_operators.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#8be7b0dfa7a3a788ad1d174f54f0cafd">for_include</a>
* <a href="{{ site.github.repository_url }}/blob/master/for_include/compare_operators.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-14 23:47:38+09:00




## Required by

* :heavy_check_mark: <a href="../graph/Bellmanford.cpp.html">graph/Bellmanford.cpp</a>
* :heavy_check_mark: <a href="../graph/Dijkstra.cpp.html">graph/Dijkstra.cpp</a>
* :heavy_check_mark: <a href="../graph/FibDijkstra.cpp.html">graph/FibDijkstra.cpp</a>
* :heavy_check_mark: <a href="../graph/FibPrim.cpp.html">graph/FibPrim.cpp</a>
* :heavy_check_mark: <a href="../graph/Kruskal.cpp.html">graph/Kruskal.cpp</a>
* :heavy_check_mark: <a href="../graph/Prim.cpp.html">graph/Prim.cpp</a>
* :heavy_check_mark: <a href="../graph/WarshallFloyd.cpp.html">graph/WarshallFloyd.cpp</a>
* :heavy_check_mark: <a href="../graph/develop/test/FibDijkstra.cpp.html">graph/develop/test/FibDijkstra.cpp</a>
* :heavy_check_mark: <a href="../graph_tree/Diameter.cpp.html">graph_tree/Diameter.cpp</a>
* :heavy_check_mark: <a href="../snippet/Weighted12DGraph.cpp.html">snippet/Weighted12DGraph.cpp</a>
* :heavy_check_mark: <a href="../snippet/Weighted1DEdge.cpp.html">snippet/Weighted1DEdge.cpp</a>
* :heavy_check_mark: <a href="../snippet/WeightedEdge.cpp.html">snippet/WeightedEdge.cpp</a>
* :heavy_check_mark: <a href="../snippet/WeightedGraph.cpp.html">snippet/WeightedGraph.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/Bellmanford.test.cpp.html">test/aoj/Bellmanford.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/Diameter.test.cpp.html">test/aoj/Diameter.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/Dijkstra.test.cpp.html">test/aoj/Dijkstra.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/Dijkstra_2.test.cpp.html">test/aoj/Dijkstra_2.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/Dijkstra_3.test.cpp.html">test/aoj/Dijkstra_3.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/FibHeapMap_Dijkstra.test.cpp.html">test/aoj/FibHeapMap_Dijkstra.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/FibHeap_Dijkstra.test.cpp.html">test/aoj/FibHeap_Dijkstra.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/FibPrim.test.cpp.html">test/aoj/FibPrim.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/Kruskal.test.cpp.html">test/aoj/Kruskal.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/Kruskal_2.test.cpp.html">test/aoj/Kruskal_2.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/Prim.test.cpp.html">test/aoj/Prim.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/Prim_2.test.cpp.html">test/aoj/Prim_2.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/WarshallFloyd.test.cpp.html">test/aoj/WarshallFloyd.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
	inline bool operator>(const type& rhs) const { return rhs < *this; }
	inline bool operator>=(const type& rhs) const { return !(*this < rhs); }
	inline bool operator<=(const type& rhs) const { return !(rhs < *this); }
	inline bool operator==(const type& rhs) const { return !(*this < rhs) && !(rhs < *this); }
	inline bool operator!=(const type& rhs) const { return (*this < rhs) || (rhs < *this); }
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "for_include/compare_operators.cpp"
	inline bool operator>(const type& rhs) const { return rhs < *this; }
	inline bool operator>=(const type& rhs) const { return !(*this < rhs); }
	inline bool operator<=(const type& rhs) const { return !(rhs < *this); }
	inline bool operator==(const type& rhs) const { return !(*this < rhs) && !(rhs < *this); }
	inline bool operator!=(const type& rhs) const { return (*this < rhs) || (rhs < *this); }
```
{% endraw %}

<a href="../../index.html">Back to top page</a>
