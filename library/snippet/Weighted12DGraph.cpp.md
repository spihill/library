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


# :heavy_check_mark: snippet/Weighted12DGraph.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#54de4c5e0ecfc39083b31b56ee36cb19">snippet</a>
* <a href="{{ site.github.repository_url }}/blob/master/snippet/Weighted12DGraph.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-15 01:52:18+09:00




## Depends on

* :heavy_check_mark: <a href="../for_include/compare_operators.cpp.html">for_include/compare_operators.cpp</a>
* :heavy_check_mark: <a href="../for_include/vec.cpp.html">for_include/vec.cpp</a>
* :heavy_check_mark: <a href="Weighted1DEdge.cpp.html">snippet/Weighted1DEdge.cpp</a>
* :heavy_check_mark: <a href="WeightedEdge.cpp.html">snippet/WeightedEdge.cpp</a>


## Required by

* :heavy_check_mark: <a href="../graph/Bellmanford.cpp.html">graph/Bellmanford.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/Bellmanford.test.cpp.html">test/aoj/Bellmanford.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
namespace edge_2d_n {
#include "WeightedEdge.cpp"
}
namespace edge_1d_n {
#include "Weighted1DEdge.cpp"
}
template<class W>
struct Graph {
	const int sz;
	edge_2d_n::Edges<W> e;
	edge_1d_n::Edges<W> edges;
	Graph(int n) : sz(n), e(sz), edges() {}
	template<class... Args> void add_edge(int u, int v, Args... args) {
		e.add_edge(u, v, args...);
		edges.add_edge(u, v, args...);
	}
	int size() {
		return sz;
	}
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "snippet/Weighted12DGraph.cpp"
namespace edge_2d_n {
#line 1 "snippet/WeightedEdge.cpp"
template<class W>
struct Edge {
	using type = Edge<W>;
	int to;
	W w;
	template<class... Args> Edge(int t, Args... args) : to(t), w(args...) {}
	inline bool operator<(const Edge& rhs) const { return w < rhs.w; }
#line 1 "snippet/../for_include/compare_operators.cpp"
	inline bool operator>(const type& rhs) const { return rhs < *this; }
	inline bool operator>=(const type& rhs) const { return !(*this < rhs); }
	inline bool operator<=(const type& rhs) const { return !(rhs < *this); }
	inline bool operator==(const type& rhs) const { return !(*this < rhs) && !(rhs < *this); }
	inline bool operator!=(const type& rhs) const { return (*this < rhs) || (rhs < *this); }#line 9 "snippet/WeightedEdge.cpp"
};
template<class W>
struct Edges : private vector<vector<Edge<W>>> {
	using type = vector<vector<Edge<W>>>;
	template<class... Args> Edges(Args... args) : type(args...) {}
	template<class... Args> void add_edge(int u, int v, Args... args) {
		(*this)[u].emplace_back(v, args...);
	}
#line 1 "snippet/../for_include/vec.cpp"
	using type::begin; using type::end; using type::rbegin; using type::rend;
	using type::cbegin; using type::cend; using type::crbegin; using type::crend;
	using type::size; using type::operator[]; using type::at; using type::back; using type::front;
	using type::reserve; using type::resize; using type::assign; using type::shrink_to_fit;
	using type::clear; using type::erase; using type::insert; using type::swap; 
	using type::push_back; using type::pop_back; using type::emplace_back; using type::empty;
	using typename vector<typename type::value_type, allocator<typename type::value_type>>::iterator;#line 18 "snippet/WeightedEdge.cpp"
};#line 3 "snippet/Weighted12DGraph.cpp"
}
namespace edge_1d_n {
#line 1 "snippet/Weighted1DEdge.cpp"
template<class W>
struct Edge {
	using type = Edge<W>;
	int from;
	int to;
	W w;
	template<class... Args> Edge(int f, int t, Args... args) : from(f), to(t), w(args...) {}
	inline bool operator<(const Edge& rhs) const { return w < rhs.w; }
#line 1 "snippet/../for_include/compare_operators.cpp"
	inline bool operator>(const type& rhs) const { return rhs < *this; }
	inline bool operator>=(const type& rhs) const { return !(*this < rhs); }
	inline bool operator<=(const type& rhs) const { return !(rhs < *this); }
	inline bool operator==(const type& rhs) const { return !(*this < rhs) && !(rhs < *this); }
	inline bool operator!=(const type& rhs) const { return (*this < rhs) || (rhs < *this); }#line 10 "snippet/Weighted1DEdge.cpp"
};
template<class W>
struct Edges : private vector<Edge<W>> {
	using type = vector<Edge<W>>;
	Edges() : type() {}
	Edges(int n) : type() {assert(0 && "Constructor must be empty");}
	template<class... Args> void add_edge(int u, int v, Args... args) {
		(*this).emplace_back(u, v, args...);
	}
#line 1 "snippet/../for_include/vec.cpp"
	using type::begin; using type::end; using type::rbegin; using type::rend;
	using type::cbegin; using type::cend; using type::crbegin; using type::crend;
	using type::size; using type::operator[]; using type::at; using type::back; using type::front;
	using type::reserve; using type::resize; using type::assign; using type::shrink_to_fit;
	using type::clear; using type::erase; using type::insert; using type::swap; 
	using type::push_back; using type::pop_back; using type::emplace_back; using type::empty;
	using typename vector<typename type::value_type, allocator<typename type::value_type>>::iterator;#line 20 "snippet/Weighted1DEdge.cpp"
};#line 6 "snippet/Weighted12DGraph.cpp"
}
template<class W>
struct Graph {
	const int sz;
	edge_2d_n::Edges<W> e;
	edge_1d_n::Edges<W> edges;
	Graph(int n) : sz(n), e(sz), edges() {}
	template<class... Args> void add_edge(int u, int v, Args... args) {
		e.add_edge(u, v, args...);
		edges.add_edge(u, v, args...);
	}
	int size() {
		return sz;
	}
};
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

