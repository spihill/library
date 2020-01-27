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


# :heavy_check_mark: graph/Kruskal.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/Kruskal.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-27 18:45:58+09:00




## Depends on

* :heavy_check_mark: <a href="../datastructure/UnionFind.cpp.html">Union Find Tree</a>
* :heavy_check_mark: <a href="../for_include/has_weighted_graph_tag.cpp.html">for_include/has_weighted_graph_tag.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/Kruskal.test.cpp.html">test/aoj/Kruskal.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/Kruskal_2.test.cpp.html">test/aoj/Kruskal_2.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
namespace kruskal_n {
#include "../datastructure/UnionFind.cpp"
#include "../for_include/has_weighted_graph_tag.cpp"
using u32 = uint32_t;
using u64 = uint64_t;
constexpr u32 upper_bits(u64 x) {return x >> 32;}
constexpr u32 lower_bits(u64 x) {return static_cast<u32>(x & numeric_limits<u32>::max());}
template<class Graph, class WEIGHT = typename Graph::WEIGHT_TYPE>
enable_if_t<has_weighted_graph_tag_v<Graph>, WEIGHT> Kruskal(const Graph& G) {
	auto idx = G.idx;
	sort(idx.begin(), idx.end(), [&](u64 a, u64 b) {
		return G.e[upper_bits(a)][lower_bits(a)].weight < G.e[upper_bits(b)][lower_bits(b)].weight;
	});
	UnionFind u(G.size());
	WEIGHT res = 0;
	for (u64 i : idx) {
		if (u.unite(upper_bits(i), G.e[upper_bits(i)][lower_bits(i)].to)) res += G.e[upper_bits(i)][lower_bits(i)].weight;
	}
	return res;
}
}
using kruskal_n::Kruskal;
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/Kruskal.cpp"
namespace kruskal_n {
#line 1 "graph/../datastructure/UnionFind.cpp"
/** 
 * @title Union Find Tree
 * @brief 初期化以外の各操作がほぼ$O(1)$で完了すると思ってよい。 0-indexed
 */
struct UnionFind {
	vector<int> par;
	UnionFind(int a) : par(a, -1) {}
// 頂点 x の親を返す
	int root(int x) { return par[x] < 0 ? x : par[x] = root(par[x]);}
// @brief 頂点 x と 頂点 y が連結されているか
	bool same(int x, int y) { return root(x) == root(y);}
// @brief 頂点 x と 頂点 y を連結する。すでに連結していたら false
	bool unite(int x, int y) {
		x = root(x);
		y = root(y);
		if (x == y) return false;
		if (size(x) < size(y)) swap(x, y);
		par[x] += par[y];
		par[y] = x;
		return true;
	}
// @brief 頂点 x が所属しているグループのサイズを返す
	int size(int x) { return -par[root(x)];}
};
#line 1 "graph/../for_include/has_weighted_graph_tag.cpp"
template <class T>
class has_weighted_graph_tag {
	template <class U> static constexpr std::true_type check(typename U::weighted_graph_tag*);
	template <class U> static constexpr std::false_type check(...);
public:
	static constexpr bool value = decltype(check<T>(nullptr))::value;
};
template <class T> constexpr bool has_weighted_graph_tag_v = has_weighted_graph_tag<T>::value;#line 4 "graph/Kruskal.cpp"
using u32 = uint32_t;
using u64 = uint64_t;
constexpr u32 upper_bits(u64 x) {return x >> 32;}
constexpr u32 lower_bits(u64 x) {return static_cast<u32>(x & numeric_limits<u32>::max());}
template<class Graph, class WEIGHT = typename Graph::WEIGHT_TYPE>
enable_if_t<has_weighted_graph_tag_v<Graph>, WEIGHT> Kruskal(const Graph& G) {
	auto idx = G.idx;
	sort(idx.begin(), idx.end(), [&](u64 a, u64 b) {
		return G.e[upper_bits(a)][lower_bits(a)].weight < G.e[upper_bits(b)][lower_bits(b)].weight;
	});
	UnionFind u(G.size());
	WEIGHT res = 0;
	for (u64 i : idx) {
		if (u.unite(upper_bits(i), G.e[upper_bits(i)][lower_bits(i)].to)) res += G.e[upper_bits(i)][lower_bits(i)].weight;
	}
	return res;
}
}
using kruskal_n::Kruskal;
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

