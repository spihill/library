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


# :heavy_check_mark: test/aoj/Diameter.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/Diameter.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-15 02:55:42+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_A">https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_A</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/for_include/compare_operators.cpp.html">for_include/compare_operators.cpp</a>
* :heavy_check_mark: <a href="../../../library/for_include/vec.cpp.html">for_include/vec.cpp</a>
* :heavy_check_mark: <a href="../../../library/graph_tree/Diameter.cpp.html">graph_tree/Diameter.cpp</a>
* :heavy_check_mark: <a href="../../../library/snippet/WeightedEdge.cpp.html">snippet/WeightedEdge.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_A"

#include<bits/stdc++.h>

using namespace std;

#include "../../graph_tree/Diameter.cpp"

int main() {
	int n;
	cin >> n;
	graph<long long> G(n);
	for (int i = 0; i < n - 1; i++) {
		int s, t, w;
		cin >> s >> t >> w;
		G.add_edge(s, t, w);
		G.add_edge(t, s, w);
	}
	cout << Diameter(G) << endl;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj/Diameter.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_A"

#include<bits/stdc++.h>

using namespace std;

#line 1 "test/aoj/../../graph_tree/Diameter.cpp"
namespace diameter_n {
#line 1 "test/aoj/../../graph_tree/../snippet/WeightedEdge.cpp"
template<class W>
struct Edge {
	using type = Edge<W>;
	int to;
	W w;
	template<class... Args> Edge(int t, Args... args) : to(t), w(args...) {}
	inline bool operator<(const Edge& rhs) const { return w < rhs.w; }
#line 1 "test/aoj/../../graph_tree/../snippet/../for_include/compare_operators.cpp"
	inline bool operator>(const type& rhs) const { return rhs < *this; }
	inline bool operator>=(const type& rhs) const { return !(*this < rhs); }
	inline bool operator<=(const type& rhs) const { return !(rhs < *this); }
	inline bool operator==(const type& rhs) const { return !(*this < rhs) && !(rhs < *this); }
	inline bool operator!=(const type& rhs) const { return (*this < rhs) || (rhs < *this); }#line 9 "test/aoj/../../graph_tree/../snippet/WeightedEdge.cpp"
};
template<class W>
struct Edges : private vector<vector<Edge<W>>> {
	using type = vector<vector<Edge<W>>>;
	template<class... Args> Edges(Args... args) : type(args...) {}
	template<class... Args> void add_edge(int u, int v, Args... args) {
		(*this)[u].emplace_back(v, args...);
	}
#line 1 "test/aoj/../../graph_tree/../snippet/../for_include/vec.cpp"
	using type::begin; using type::end; using type::rbegin; using type::rend;
	using type::cbegin; using type::cend; using type::crbegin; using type::crend;
	using type::size; using type::operator[]; using type::at; using type::back; using type::front;
	using type::reserve; using type::resize; using type::assign; using type::shrink_to_fit;
	using type::clear; using type::erase; using type::insert; using type::swap; 
	using type::push_back; using type::pop_back; using type::emplace_back; using type::empty;
	using typename vector<typename type::value_type, allocator<typename type::value_type>>::iterator;#line 18 "test/aoj/../../graph_tree/../snippet/WeightedEdge.cpp"
};#line 3 "test/aoj/../../graph_tree/Diameter.cpp"
template<class W>
int Diameter(Edges<W>& e) {
	auto dfs = [&](auto f, int start, int& goal, int par = -1) -> W {
		goal = start;
		W res = 0;
		for (auto& i: e[start]) {
			if (i.to == par) continue;
			int t;
			W r = f(f, i.to, t, start);
			r += i.w;
			if (r > res) {
				res = r;
				goal = t;
			}
		}
		return res;
	};
	int g;
	dfs(dfs, 0, g);
	return dfs(dfs, g, g);
}
}
template<class W> using graph = diameter_n::Edges<W>;
using diameter_n::Diameter;#line 8 "test/aoj/Diameter.test.cpp"

int main() {
	int n;
	cin >> n;
	graph<long long> G(n);
	for (int i = 0; i < n - 1; i++) {
		int s, t, w;
		cin >> s >> t >> w;
		G.add_edge(s, t, w);
		G.add_edge(t, s, w);
	}
	cout << Diameter(G) << endl;
}
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

