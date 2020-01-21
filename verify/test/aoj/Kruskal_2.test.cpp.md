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
    - Last commit date: 2020-01-22 01:53:39+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/12/ALDS1_12_A">https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/12/ALDS1_12_A</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/datastructure/UnionFind.cpp.html">Union Find Tree</a>
* :heavy_check_mark: <a href="../../../library/for_include/has_weighted_graph_tag.cpp.html">for_include/has_weighted_graph_tag.cpp</a>
* :heavy_check_mark: <a href="../../../library/graph/Kruskal.cpp.html">graph/Kruskal.cpp</a>
* :heavy_check_mark: <a href="../../../library/template/UnWeightedGraph.cpp.html">template/UnWeightedGraph.cpp</a>
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
template<class Graph, class W = typename Graph::weight_type>
enable_if_t<has_weighted_graph_tag_v<Graph>, W> Kruskal(const Graph& G) {
	using u64 = uint64_t;
	using u32 = uint32_t;
	vector<u64> idx;
	for (size_t i = 0; i < G.size(); i++) {
		for (size_t j = 0; j < G.edge[i].size(); j++) {
			idx.push_back(static_cast<u64>(i) << 32 | j);
		}
	}
	sort(idx.begin(), idx.end(), [&](u64 a, u64 b) {
		return G.weight[a >> 32][a & numeric_limits<u32>::max()] < G.weight[b >> 32][b & numeric_limits<u32>::max()];
	});
	UnionFind u(G.size());
	W res = 0;
	for (u64 i : idx) {
		if (u.unite(i >> 32, G.edge[i >> 32][i & numeric_limits<u32>::max()])) res += G.weight[i >> 32][i & numeric_limits<u32>::max()];
	}
	return res;
}
}
using kruskal_n::Kruskal;#line 1 "test/aoj/../../template/WeightedGraph.cpp"
namespace weighted_graph_n{
#line 1 "test/aoj/../../template/UnWeightedGraph.cpp"
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
}#line 3 "test/aoj/../../template/WeightedGraph.cpp"
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

