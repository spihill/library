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
    - Last commit date: 2020-01-15 01:52:18+09:00




## Depends on

* :heavy_check_mark: <a href="../datastructure/UnionFind.cpp.html">datastructure/UnionFind.cpp</a>
* :heavy_check_mark: <a href="../for_include/compare_operators.cpp.html">for_include/compare_operators.cpp</a>
* :heavy_check_mark: <a href="../for_include/vec.cpp.html">for_include/vec.cpp</a>
* :heavy_check_mark: <a href="../snippet/Weighted1DEdge.cpp.html">snippet/Weighted1DEdge.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/Kruskal.test.cpp.html">test/aoj/Kruskal.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/Kruskal_2.test.cpp.html">test/aoj/Kruskal_2.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
namespace kruskal_n {
#include "../datastructure/UnionFind.cpp"
#include "../snippet/Weighted1DEdge.cpp"
template<class T>
T Kruskal(Edges<T>& e) {
	sort(e.begin(), e.end());
	UnionFind u(e.size());
	T res = 0;
	for (auto &x : e) {
		if (u.unite(x.from, x.to)) res += x.w;
	}
	return res;
}
}
using kruskal_n::Kruskal;
template<class T> using graph = kruskal_n::Edges<T>;
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/Kruskal.cpp"
namespace kruskal_n {
#line 1 "graph/../datastructure/UnionFind.cpp"
struct UnionFind {
	int sz;
	vector<int> par;
	UnionFind(int a) : sz(a), par(sz, -1) {}
	int root(int x) { return par[x] < 0 ? x : par[x] = root(par[x]);}
	bool same(int x, int y) { return root(x) == root(y);}
	bool unite(int x, int y) {
		x = root(x);
		y = root(y);
		if (x == y) return false;
		if (size(x) < size(y)) swap(x, y);
		par[x] += par[y];
		par[y] = x;
		return true;
	}
	int size(int x) { return -par[root(x)];}
	int size() { return sz;}
};
#line 1 "graph/../snippet/Weighted1DEdge.cpp"
template<class W>
struct Edge {
	using type = Edge<W>;
	int from;
	int to;
	W w;
	template<class... Args> Edge(int f, int t, Args... args) : from(f), to(t), w(args...) {}
	inline bool operator<(const Edge& rhs) const { return w < rhs.w; }
#line 1 "graph/../snippet/../for_include/compare_operators.cpp"
	inline bool operator>(const type& rhs) const { return rhs < *this; }
	inline bool operator>=(const type& rhs) const { return !(*this < rhs); }
	inline bool operator<=(const type& rhs) const { return !(rhs < *this); }
	inline bool operator==(const type& rhs) const { return !(*this < rhs) && !(rhs < *this); }
	inline bool operator!=(const type& rhs) const { return (*this < rhs) || (rhs < *this); }#line 10 "graph/../snippet/Weighted1DEdge.cpp"
};
template<class W>
struct Edges : private vector<Edge<W>> {
	using type = vector<Edge<W>>;
	Edges() : type() {}
	Edges(int n) : type() {assert(0 && "Constructor must be empty");}
	template<class... Args> void add_edge(int u, int v, Args... args) {
		(*this).emplace_back(u, v, args...);
	}
#line 1 "graph/../snippet/../for_include/vec.cpp"
	using type::begin; using type::end; using type::rbegin; using type::rend;
	using type::cbegin; using type::cend; using type::crbegin; using type::crend;
	using type::size; using type::operator[]; using type::at; using type::back; using type::front;
	using type::reserve; using type::resize; using type::assign; using type::shrink_to_fit;
	using type::clear; using type::erase; using type::insert; using type::swap; 
	using type::push_back; using type::pop_back; using type::emplace_back; using type::empty;
	using typename vector<typename type::value_type, allocator<typename type::value_type>>::iterator;#line 20 "graph/../snippet/Weighted1DEdge.cpp"
};#line 4 "graph/Kruskal.cpp"
template<class T>
T Kruskal(Edges<T>& e) {
	sort(e.begin(), e.end());
	UnionFind u(e.size());
	T res = 0;
	for (auto &x : e) {
		if (u.unite(x.from, x.to)) res += x.w;
	}
	return res;
}
}
using kruskal_n::Kruskal;
template<class T> using graph = kruskal_n::Edges<T>;
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

