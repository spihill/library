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
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :heavy_check_mark: test/aoj/Kruskal_2.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/Kruskal_2.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-24 00:56:25+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/12/ALDS1_12_A">https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/12/ALDS1_12_A</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/datastructure/UnionFind.cpp.html">Union Find Tree</a>
* :heavy_check_mark: <a href="../../../library/for_include/has_weighted_graph_tag.cpp.html">for_include/has_weighted_graph_tag.cpp</a>
* :heavy_check_mark: <a href="../../../library/graph/Kruskal.cpp.html">graph/Kruskal.cpp</a>
* :heavy_check_mark: <a href="../../../library/template/Graph.cpp.html">template/Graph.cpp</a>
* :heavy_check_mark: <a href="../../../library/template/WeightedGraph.cpp.html">template/WeightedGraph.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/12/ALDS1_12_A"
#include <bits/stdc++.h>
 
using namespace std;

#include "../../graph/Kruskal.cpp"
#include "../../template/WeightedGraph.cpp"

int main() {
    int n; cin >> n;
	auto G = make_weighted_graph(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int c; cin >> c;
            if (c >= 0) G.add_edge(i, j, c);
        }
    }
    cout << Kruskal(G) << endl;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj/Kruskal_2.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/12/ALDS1_12_A"
#include <bits/stdc++.h>
 
using namespace std;

#line 1 "test/aoj/../../graph/Kruskal.cpp"
namespace kruskal_n {
#line 1 "test/aoj/../../graph/../datastructure/UnionFind.cpp"
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
#line 1 "test/aoj/../../graph/../for_include/has_weighted_graph_tag.cpp"
template <class T>
class has_weighted_graph_tag {
	template <class U, typename O = typename U::weighted_graph_tag> static constexpr std::true_type check(int);
	template <class U> static constexpr std::false_type check(long);
public:
	static constexpr bool value = decltype(check<T>(0))::value;
};
template <class T> constexpr bool has_weighted_graph_tag_v = has_weighted_graph_tag<T>::value;#line 4 "test/aoj/../../graph/Kruskal.cpp"
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
using kruskal_n::Kruskal;#line 1 "test/aoj/../../template/WeightedGraph.cpp"
namespace weighted_graph_n{
#line 1 "test/aoj/../../template/Graph.cpp"
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
};#line 3 "test/aoj/../../template/WeightedGraph.cpp"
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
using weighted_graph_n::make_weighted_graph;#line 8 "test/aoj/Kruskal_2.test.cpp"

int main() {
    int n; cin >> n;
	auto G = make_weighted_graph(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int c; cin >> c;
            if (c >= 0) G.add_edge(i, j, c);
        }
    }
    cout << Kruskal(G) << endl;
}
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

