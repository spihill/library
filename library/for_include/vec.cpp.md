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


# :heavy_check_mark: for_include/vec.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#8be7b0dfa7a3a788ad1d174f54f0cafd">for_include</a>
* <a href="{{ site.github.repository_url }}/blob/master/for_include/vec.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-15 01:52:18+09:00




## Required by

* :heavy_check_mark: <a href="../graph/Bellmanford.cpp.html">graph/Bellmanford.cpp</a>
* :heavy_check_mark: <a href="../graph/FibDijkstra.cpp.html">graph/FibDijkstra.cpp</a>
* :heavy_check_mark: <a href="../graph/FibPrim.cpp.html">graph/FibPrim.cpp</a>
* :heavy_check_mark: <a href="../graph/Kruskal.cpp.html">graph/Kruskal.cpp</a>
* :heavy_check_mark: <a href="../graph/Prim.cpp.html">graph/Prim.cpp</a>
* :heavy_check_mark: <a href="../graph/WarshallFloyd.cpp.html">graph/WarshallFloyd.cpp</a>
* :heavy_check_mark: <a href="../graph_tree/Diameter.cpp.html">graph_tree/Diameter.cpp</a>
* :warning: <a href="../snippet/FlowEdge.cpp.html">snippet/FlowEdge.cpp</a>
* :warning: <a href="../snippet/FlowGraph.cpp.html">snippet/FlowGraph.cpp</a>
* :heavy_check_mark: <a href="../snippet/Weighted12DGraph.cpp.html">snippet/Weighted12DGraph.cpp</a>
* :heavy_check_mark: <a href="../snippet/Weighted1DEdge.cpp.html">snippet/Weighted1DEdge.cpp</a>
* :heavy_check_mark: <a href="../snippet/WeightedEdge.cpp.html">snippet/WeightedEdge.cpp</a>
* :heavy_check_mark: <a href="../snippet/WeightedGraph.cpp.html">snippet/WeightedGraph.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/Bellmanford.test.cpp.html">test/aoj/Bellmanford.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/Diameter.test.cpp.html">test/aoj/Diameter.test.cpp</a>
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
	using type::begin; using type::end; using type::rbegin; using type::rend;
	using type::cbegin; using type::cend; using type::crbegin; using type::crend;
	using type::size; using type::operator[]; using type::at; using type::back; using type::front;
	using type::reserve; using type::resize; using type::assign; using type::shrink_to_fit;
	using type::clear; using type::erase; using type::insert; using type::swap; 
	using type::push_back; using type::pop_back; using type::emplace_back; using type::empty;
	using typename vector<typename type::value_type, allocator<typename type::value_type>>::iterator;
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "for_include/vec.cpp"
	using type::begin; using type::end; using type::rbegin; using type::rend;
	using type::cbegin; using type::cend; using type::crbegin; using type::crend;
	using type::size; using type::operator[]; using type::at; using type::back; using type::front;
	using type::reserve; using type::resize; using type::assign; using type::shrink_to_fit;
	using type::clear; using type::erase; using type::insert; using type::swap; 
	using type::push_back; using type::pop_back; using type::emplace_back; using type::empty;
	using typename vector<typename type::value_type, allocator<typename type::value_type>>::iterator;
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

