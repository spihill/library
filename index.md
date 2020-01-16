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
<script type="text/javascript" src="assets/js/copy-button.js"></script>
<link rel="stylesheet" href="assets/css/copy-button.css" />


# {{ site.title }}

[![Actions Status]({{ site.github.repository_url }}/workflows/verify/badge.svg)]({{ site.github.repository_url }}/actions)
<a href="{{ site.github.repository_url }}"><img src="https://img.shields.io/github/last-commit/{{ site.github.owner_name }}/{{ site.github.repository_name }}" /></a>

{% if site.description %}{{ site.description }}{% else %}This documentation is automatically generated by <a href="https://github.com/kmyk/online-judge-verify-helper">online-judge-verify-helper</a>.{% endif %}

## Library Files

<div id="ed469618898d75b149e5c7c4b6a1c415"></div>

### algorithm

* :warning: <a href="library/algorithm/dictionary_order.cpp.html">algorithm/dictionary_order.cpp</a>
* :heavy_check_mark: <a href="library/algorithm/meguru.cpp.html">algorithm/meguru.cpp</a>
* :heavy_check_mark: <a href="library/algorithm/syakutori.cpp.html">algorithm/syakutori.cpp</a>


<div id="8dc87745f885a4cc532acd7b15b8b5fe"></div>

### datastructure

* :heavy_check_mark: <a href="library/datastructure/BIT.cpp.html">BIT (Binary Indexed Tree)</a>
* :heavy_check_mark: <a href="library/datastructure/BIT_2D.cpp.html">２次元 BIT</a>
* :heavy_check_mark: <a href="library/datastructure/FibHeap.cpp.html">フィボナッチヒープ (Key)</a>
* :heavy_check_mark: <a href="library/datastructure/FibHeapMap.cpp.html">フィボナッチヒープ (Key and Value)</a>
* :heavy_check_mark: <a href="library/datastructure/SWAG.cpp.html">datastructure/SWAG.cpp</a>
* :heavy_check_mark: <a href="library/datastructure/SparseTable.cpp.html">datastructure/SparseTable.cpp</a>
* :heavy_check_mark: <a href="library/datastructure/UnionFind.cpp.html">datastructure/UnionFind.cpp</a>
* :warning: <a href="library/datastructure/Union_Find_Weight.cpp.html">datastructure/Union_Find_Weight.cpp</a>


<div id="7fda95de140943da319b7f24cc2c3f48"></div>

### datastructure/BinarySearchTree/develop

* :warning: <a href="library/datastructure/BinarySearchTree/develop/AVLMap.cpp.html">datastructure/BinarySearchTree/develop/AVLMap.cpp</a>
* :warning: <a href="library/datastructure/BinarySearchTree/develop/AVLSet.cpp.html">datastructure/BinarySearchTree/develop/AVLSet.cpp</a>
* :warning: <a href="library/datastructure/BinarySearchTree/develop/RBSTset.cpp.html">datastructure/BinarySearchTree/develop/RBSTset.cpp</a>
* :warning: <a href="library/datastructure/BinarySearchTree/develop/RedBlackSet.cpp.html">datastructure/BinarySearchTree/develop/RedBlackSet.cpp</a>


<div id="cbada5aa9c548d7605cff951f3e28eda"></div>

### datastructure/SegmentTree

* :heavy_check_mark: <a href="library/datastructure/SegmentTree/DynamicSegTree.cpp.html">動的セグメント木</a>
* :heavy_check_mark: <a href="library/datastructure/SegmentTree/LazySegmentTree.cpp.html">datastructure/SegmentTree/LazySegmentTree.cpp</a>
* :warning: <a href="library/datastructure/SegmentTree/RBST.cpp.html">datastructure/SegmentTree/RBST.cpp</a>
* :heavy_check_mark: <a href="library/datastructure/SegmentTree/SegmentTree.cpp.html">datastructure/SegmentTree/SegmentTree.cpp</a>


<div id="95687afb5d9a2a9fa39038f991640b0c"></div>

### dp

* :heavy_check_mark: <a href="library/dp/Knapsack.cpp.html">dp/Knapsack.cpp</a>
* :heavy_check_mark: <a href="library/dp/Knapsack_01.cpp.html">dp/Knapsack_01.cpp</a>
* :heavy_check_mark: <a href="library/dp/LCS.cpp.html">dp/LCS.cpp</a>
* :heavy_check_mark: <a href="library/dp/Levenshtein.cpp.html">dp/Levenshtein.cpp</a>
* :heavy_check_mark: <a href="library/dp/PartialSum_limited.cpp.html">dp/PartialSum_limited.cpp</a>


<div id="8be7b0dfa7a3a788ad1d174f54f0cafd"></div>

### for_include

* :heavy_check_mark: <a href="library/for_include/compare_operators.cpp.html">for_include/compare_operators.cpp</a>
* :heavy_check_mark: <a href="library/for_include/vec.cpp.html">for_include/vec.cpp</a>


<div id="f8b0b924ebd7046dbfa85a856e4682c8"></div>

### graph

* :heavy_check_mark: <a href="library/graph/Bellmanford.cpp.html">graph/Bellmanford.cpp</a>
* :heavy_check_mark: <a href="library/graph/Dijkstra.cpp.html">graph/Dijkstra.cpp</a>
* :heavy_check_mark: <a href="library/graph/Dinic.cpp.html">graph/Dinic.cpp</a>
* :heavy_check_mark: <a href="library/graph/FibDijkstra.cpp.html">graph/FibDijkstra.cpp</a>
* :heavy_check_mark: <a href="library/graph/FibPrim.cpp.html">graph/FibPrim.cpp</a>
* :heavy_check_mark: <a href="library/graph/Kruskal.cpp.html">graph/Kruskal.cpp</a>
* :heavy_check_mark: <a href="library/graph/Prim.cpp.html">graph/Prim.cpp</a>
* :heavy_check_mark: <a href="library/graph/SCC.cpp.html">graph/SCC.cpp</a>
* :warning: <a href="library/graph/TopologicalSort.cpp.html">graph/TopologicalSort.cpp</a>
* :heavy_check_mark: <a href="library/graph/WarshallFloyd.cpp.html">graph/WarshallFloyd.cpp</a>
* :heavy_check_mark: <a href="library/graph/is_Biparite.cpp.html">graph/is_Biparite.cpp</a>


<div id="95854e999cb9c227e468acd41a41ac58"></div>

### graph/develop

* :warning: <a href="library/graph/develop/Ford_Fulkerson.cpp.html">graph/develop/Ford_Fulkerson.cpp</a>


<div id="30dc6b0f67189f880dafb8046d6141e6"></div>

### graph/develop/test

* :heavy_check_mark: <a href="library/graph/develop/test/FibDijkstra.cpp.html">graph/develop/test/FibDijkstra.cpp</a>


<div id="f93f3ae32620f7630b3615eae399affa"></div>

### graph_tree

* :heavy_check_mark: <a href="library/graph_tree/Diameter.cpp.html">graph_tree/Diameter.cpp</a>
* :heavy_check_mark: <a href="library/graph_tree/LCA.cpp.html">graph_tree/LCA.cpp</a>


<div id="2ce58b44113eaf8f045cee2f9f04f29c"></div>

### graph_tree/develop

* :warning: <a href="library/graph_tree/develop/Centroid.cpp.html">graph_tree/develop/Centroid.cpp</a>


<div id="e5c0d69cda55dfeb297768498dd24c1e"></div>

### graph_tree/verify

* :warning: <a href="library/graph_tree/verify/Diameter.cpp.html">graph_tree/verify/Diameter.cpp</a>
* :warning: <a href="library/graph_tree/verify/LCA_Centroid.cpp.html">graph_tree/verify/LCA_Centroid.cpp</a>


<div id="7e676e9e663beb40fd133f5ee24487c2"></div>

### math

* :warning: <a href="library/math/FFT.cpp.html">高速フーリエ変換</a>
* :heavy_check_mark: <a href="library/math/Factorize.cpp.html">素因数分解</a>
* :heavy_check_mark: <a href="library/math/Matrix.cpp.html">行列</a>
* :heavy_check_mark: <a href="library/math/ModComb.cpp.html">Mod Combination</a>
* :heavy_check_mark: <a href="library/math/ModComb_compiletime.cpp.html">コンパイル時前計算 Mod Combination</a>
* :heavy_check_mark: <a href="library/math/ModInt.cpp.html">ModInt</a>
* :heavy_check_mark: <a href="library/math/NTT.cpp.html">Number Theoretic Transform (NTT)</a>
* :heavy_check_mark: <a href="library/math/ctz.cpp.html">__builtin_ctz の代用関数</a>
* :heavy_check_mark: <a href="library/math/extgcd.cpp.html">拡張ユークリッドの互除法</a>
* :heavy_check_mark: <a href="library/math/gcd.cpp.html">最大公約数</a>
* :heavy_check_mark: <a href="library/math/lcm.cpp.html">最小公倍数</a>
* :heavy_check_mark: <a href="library/math/monoid_t.cpp.html">math/monoid_t.cpp</a>
* :heavy_check_mark: <a href="library/math/msb_pos.cpp.html">msb の位置を調べる</a>


<div id="c3437aaac8e99d51d51e80f390e49b05"></div>

### monoid

* :heavy_check_mark: <a href="library/monoid/affine_monoid.cpp.html">monoid/affine_monoid.cpp</a>
* :heavy_check_mark: <a href="library/monoid/max_monoid.cpp.html">monoid/max_monoid.cpp</a>
* :heavy_check_mark: <a href="library/monoid/min_monoid.cpp.html">monoid/min_monoid.cpp</a>
* :heavy_check_mark: <a href="library/monoid/plus_monoid.cpp.html">monoid/plus_monoid.cpp</a>
* :heavy_check_mark: <a href="library/monoid/update_monoid.cpp.html">monoid/update_monoid.cpp</a>


<div id="8bd1ab4c7cd9516f57d0eb7bdbde5819"></div>

### monoid/pair

* :heavy_check_mark: <a href="library/monoid/pair/min_plus_monoid.cpp.html">monoid/pair/min_plus_monoid.cpp</a>
* :heavy_check_mark: <a href="library/monoid/pair/min_update_monoid.cpp.html">monoid/pair/min_update_monoid.cpp</a>
* :heavy_check_mark: <a href="library/monoid/pair/plus_plus_monoid.cpp.html">monoid/pair/plus_plus_monoid.cpp</a>
* :heavy_check_mark: <a href="library/monoid/pair/plus_update_monoid.cpp.html">monoid/pair/plus_update_monoid.cpp</a>


<div id="54de4c5e0ecfc39083b31b56ee36cb19"></div>

### snippet

* :heavy_check_mark: <a href="library/snippet/Edge.cpp.html">snippet/Edge.cpp</a>
* :heavy_check_mark: <a href="library/snippet/FlowEdge.cpp.html">snippet/FlowEdge.cpp</a>
* :heavy_check_mark: <a href="library/snippet/FlowGraph.cpp.html">snippet/FlowGraph.cpp</a>
* :heavy_check_mark: <a href="library/snippet/Graph.cpp.html">snippet/Graph.cpp</a>
* :warning: <a href="library/snippet/SegNode.cpp.html">snippet/SegNode.cpp</a>
* :warning: <a href="library/snippet/SegNode_slow.cpp.html">snippet/SegNode_slow.cpp</a>
* :heavy_check_mark: <a href="library/snippet/Weighted12DGraph.cpp.html">snippet/Weighted12DGraph.cpp</a>
* :heavy_check_mark: <a href="library/snippet/Weighted1DEdge.cpp.html">snippet/Weighted1DEdge.cpp</a>
* :heavy_check_mark: <a href="library/snippet/WeightedEdge.cpp.html">snippet/WeightedEdge.cpp</a>
* :heavy_check_mark: <a href="library/snippet/WeightedGraph.cpp.html">snippet/WeightedGraph.cpp</a>
* :warning: <a href="library/snippet/class2.cpp.html">snippet/class2.cpp</a>
* :warning: <a href="library/snippet/class3.cpp.html">snippet/class3.cpp</a>
* :warning: <a href="library/snippet/class4.cpp.html">snippet/class4.cpp</a>
* :warning: <a href="library/snippet/class5.cpp.html">snippet/class5.cpp</a>
* :warning: <a href="library/snippet/monoid.cpp.html">snippet/monoid.cpp</a>


<div id="b45cffe084dd3d20d928bee85e7b0f21"></div>

### string

* :heavy_check_mark: <a href="library/string/RollingHash.cpp.html">string/RollingHash.cpp</a>
* :heavy_check_mark: <a href="library/string/Z_algorithm.cpp.html">string/Z_algorithm.cpp</a>


<div id="4a931512ce65bdc9ca6808adf92d8783"></div>

### tools

* :warning: <a href="library/tools/RandomClass.cpp.html">tools/RandomClass.cpp</a>


## Verify Files

* :heavy_check_mark: <a href="verify/test/aoj/BIT_2D_1.test.cpp.html">test/aoj/BIT_2D_1.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/BIT_2D_2.test.cpp.html">test/aoj/BIT_2D_2.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/Bellmanford.test.cpp.html">test/aoj/Bellmanford.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/Diameter.test.cpp.html">test/aoj/Diameter.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/Dijkstra.test.cpp.html">test/aoj/Dijkstra.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/Dijkstra_2.test.cpp.html">test/aoj/Dijkstra_2.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/Dijkstra_3.test.cpp.html">test/aoj/Dijkstra_3.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/Dinic.test.cpp.html">test/aoj/Dinic.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/DynamicSetgree_RMQ.test.cpp.html">test/aoj/DynamicSetgree_RMQ.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/DynamicSetgree_RSQ.test.cpp.html">test/aoj/DynamicSetgree_RSQ.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/Factorize_map.test.cpp.html">test/aoj/Factorize_map.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/Factorize_vec.test.cpp.html">test/aoj/Factorize_vec.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/FibHeap.test.cpp.html">test/aoj/FibHeap.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/FibHeapMap_Dijkstra.test.cpp.html">test/aoj/FibHeapMap_Dijkstra.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/FibHeap_Dijkstra.test.cpp.html">test/aoj/FibHeap_Dijkstra.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/FibPrim.test.cpp.html">test/aoj/FibPrim.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/Knapsack.test.cpp.html">test/aoj/Knapsack.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/Knapsack_01.test.cpp.html">test/aoj/Knapsack_01.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/Kruskal.test.cpp.html">test/aoj/Kruskal.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/Kruskal_2.test.cpp.html">test/aoj/Kruskal_2.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/LCA.test.cpp.html">test/aoj/LCA.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/LCM.test.cpp.html">test/aoj/LCM.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/LCS.test.cpp.html">test/aoj/LCS.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/LazySegmentTree_RMQ_RAQ.test.cpp.html">test/aoj/LazySegmentTree_RMQ_RAQ.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/LazySegmentTree_RMQ_RUQ.test.cpp.html">test/aoj/LazySegmentTree_RMQ_RUQ.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/LazySegmentTree_RSQ_RAQ.test.cpp.html">test/aoj/LazySegmentTree_RSQ_RAQ.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/LazySegmentTree_RSQ_RUQ.test.cpp.html">test/aoj/LazySegmentTree_RSQ_RUQ.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/Levenshtein.test.cpp.html">test/aoj/Levenshtein.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/Matrix.test.cpp.html">test/aoj/Matrix.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/ModComb.test.cpp.html">test/aoj/ModComb.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/ModComb_compiletime.test.cpp.html">test/aoj/ModComb_compiletime.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/ModInt_Power.test.cpp.html">test/aoj/ModInt_Power.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/Prim.test.cpp.html">test/aoj/Prim.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/Prim_2.test.cpp.html">test/aoj/Prim_2.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/RollingHash.test.cpp.html">test/aoj/RollingHash.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/SegmentTree_RMQ.test.cpp.html">test/aoj/SegmentTree_RMQ.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/SegmentTree_RMQ_2.test.cpp.html">test/aoj/SegmentTree_RMQ_2.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/SegmentTree_RSQ.test.cpp.html">test/aoj/SegmentTree_RSQ.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/UnionFind.test.cpp.html">test/aoj/UnionFind.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/WarshallFloyd.test.cpp.html">test/aoj/WarshallFloyd.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/extgcd.test.cpp.html">test/aoj/extgcd.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/is_Biparite.test.cpp.html">test/aoj/is_Biparite.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/meguru.test.cpp.html">test/aoj/meguru.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/meguru_2.test.cpp.html">test/aoj/meguru_2.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/syakutori_DSL_3_A.test.cpp.html">test/aoj/syakutori_DSL_3_A.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/aoj/syakutori_DSL_3_C.test.cpp.html">test/aoj/syakutori_DSL_3_C.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/yosupo/BIT_1.test.cpp.html">test/yosupo/BIT_1.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/yosupo/BIT_2.test.cpp.html">test/yosupo/BIT_2.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/yosupo/DynamicSegTree_Affine.test.cpp.html">test/yosupo/DynamicSegTree_Affine.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/yosupo/DynamicSegTree_Affine_2.test.cpp.html">test/yosupo/DynamicSegTree_Affine_2.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/yosupo/NTT.test.cpp.html">test/yosupo/NTT.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/yosupo/NTT_mod.test.cpp.html">test/yosupo/NTT_mod.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/yosupo/SCC.test.cpp.html">test/yosupo/SCC.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/yosupo/SegTree_Affine.test.cpp.html">test/yosupo/SegTree_Affine.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/yosupo/SparseTable_RMQ.test.cpp.html">test/yosupo/SparseTable_RMQ.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/yosupo/UnionFind.test.cpp.html">test/yosupo/UnionFind.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/yosupo/Z_algorithm.test.cpp.html">test/yosupo/Z_algorithm.test.cpp</a>

