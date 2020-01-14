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


# :heavy_check_mark: test/aoj/Bellmanford.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/Bellmanford.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-15 01:52:18+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B&lang=ja">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B&lang=ja</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/for_include/compare_operators.cpp.html">for_include/compare_operators.cpp</a>
* :heavy_check_mark: <a href="../../../library/for_include/vec.cpp.html">for_include/vec.cpp</a>
* :heavy_check_mark: <a href="../../../library/graph/Bellmanford.cpp.html">graph/Bellmanford.cpp</a>
* :heavy_check_mark: <a href="../../../library/snippet/Weighted12DGraph.cpp.html">snippet/Weighted12DGraph.cpp</a>
* :heavy_check_mark: <a href="../../../library/snippet/Weighted1DEdge.cpp.html">snippet/Weighted1DEdge.cpp</a>
* :heavy_check_mark: <a href="../../../library/snippet/WeightedEdge.cpp.html">snippet/WeightedEdge.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#include "../../graph/Bellmanford.cpp"

int main() {
	int V, E, S;
	cin >> V >> E >> S;
	graph<int> B(V);
	for (int i = 0; i < E; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		B.add_edge(a, b, c);
	}
	Bellmanford(B, S, INT_MAX);
	for (int i = 0; i < V; i++) {
		if (!B.valid[i] && B.dist[i] != INT_MAX) {
			cout << "NEGATIVE CYCLE" << endl;
			return 0;
		}
	}
	for (int i = 0; i < V; i++) {
		if (!B.valid[i]) cout << "INF" << endl;
		else cout << B.dist[i] << endl;
	}
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj/Bellmanford.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#line 1 "test/aoj/../../graph/Bellmanford.cpp"
namespace bellman_n {
#line 1 "test/aoj/../../graph/../snippet/Weighted12DGraph.cpp"
namespace edge_2d_n {
#line 1 "test/aoj/../../graph/../snippet/WeightedEdge.cpp"
template<class W>
struct Edge {
	using type = Edge<W>;
	int to;
	W w;
	template<class... Args> Edge(int t, Args... args) : to(t), w(args...) {}
	inline bool operator<(const Edge& rhs) const { return w < rhs.w; }
#line 1 "test/aoj/../../graph/../snippet/../for_include/compare_operators.cpp"
	inline bool operator>(const type& rhs) const { return rhs < *this; }
	inline bool operator>=(const type& rhs) const { return !(*this < rhs); }
	inline bool operator<=(const type& rhs) const { return !(rhs < *this); }
	inline bool operator==(const type& rhs) const { return !(*this < rhs) && !(rhs < *this); }
	inline bool operator!=(const type& rhs) const { return (*this < rhs) || (rhs < *this); }#line 9 "test/aoj/../../graph/../snippet/WeightedEdge.cpp"
};
template<class W>
struct Edges : private vector<vector<Edge<W>>> {
	using type = vector<vector<Edge<W>>>;
	template<class... Args> Edges(Args... args) : type(args...) {}
	template<class... Args> void add_edge(int u, int v, Args... args) {
		(*this)[u].emplace_back(v, args...);
	}
#line 1 "test/aoj/../../graph/../snippet/../for_include/vec.cpp"
	using type::begin; using type::end; using type::rbegin; using type::rend;
	using type::cbegin; using type::cend; using type::crbegin; using type::crend;
	using type::size; using type::operator[]; using type::at; using type::back; using type::front;
	using type::reserve; using type::resize; using type::assign; using type::shrink_to_fit;
	using type::clear; using type::erase; using type::insert; using type::swap; 
	using type::push_back; using type::pop_back; using type::emplace_back; using type::empty;
	using typename vector<typename type::value_type, allocator<typename type::value_type>>::iterator;#line 18 "test/aoj/../../graph/../snippet/WeightedEdge.cpp"
};#line 3 "test/aoj/../../graph/../snippet/Weighted12DGraph.cpp"
}
namespace edge_1d_n {
#line 1 "test/aoj/../../graph/../snippet/Weighted1DEdge.cpp"
template<class W>
struct Edge {
	using type = Edge<W>;
	int from;
	int to;
	W w;
	template<class... Args> Edge(int f, int t, Args... args) : from(f), to(t), w(args...) {}
	inline bool operator<(const Edge& rhs) const { return w < rhs.w; }
#line 1 "test/aoj/../../graph/../snippet/../for_include/compare_operators.cpp"
	inline bool operator>(const type& rhs) const { return rhs < *this; }
	inline bool operator>=(const type& rhs) const { return !(*this < rhs); }
	inline bool operator<=(const type& rhs) const { return !(rhs < *this); }
	inline bool operator==(const type& rhs) const { return !(*this < rhs) && !(rhs < *this); }
	inline bool operator!=(const type& rhs) const { return (*this < rhs) || (rhs < *this); }#line 10 "test/aoj/../../graph/../snippet/Weighted1DEdge.cpp"
};
template<class W>
struct Edges : private vector<Edge<W>> {
	using type = vector<Edge<W>>;
	Edges() : type() {}
	Edges(int n) : type() {assert(0 && "Constructor must be empty");}
	template<class... Args> void add_edge(int u, int v, Args... args) {
		(*this).emplace_back(u, v, args...);
	}
#line 1 "test/aoj/../../graph/../snippet/../for_include/vec.cpp"
	using type::begin; using type::end; using type::rbegin; using type::rend;
	using type::cbegin; using type::cend; using type::crbegin; using type::crend;
	using type::size; using type::operator[]; using type::at; using type::back; using type::front;
	using type::reserve; using type::resize; using type::assign; using type::shrink_to_fit;
	using type::clear; using type::erase; using type::insert; using type::swap; 
	using type::push_back; using type::pop_back; using type::emplace_back; using type::empty;
	using typename vector<typename type::value_type, allocator<typename type::value_type>>::iterator;#line 20 "test/aoj/../../graph/../snippet/Weighted1DEdge.cpp"
};#line 6 "test/aoj/../../graph/../snippet/Weighted12DGraph.cpp"
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
};#line 3 "test/aoj/../../graph/Bellmanford.cpp"
template<class W, class T = W>
struct Graph_B : public Graph<W> {
	vector<T> dist;
	vector<char> valid;
	Graph_B(int n) : Graph<W>(n), dist(n), valid(n) {}
};
template<class W, class T = W>
void Bellmanford(Graph_B<W, T>& G, int s, T INF_COST) {
	auto& dist = G.dist;
	auto& valid = G.valid;
	auto& e = G.e;
	auto& edges = G.edges;
	for (auto& d : dist) d = INF_COST;
	for (auto& v: valid) v = 0;
	dist[s] = 0, valid[s] = 1;
	for (int i = 0; i + 1 < G.size(); i++) {
		for (auto& x: edges) {
			if (dist[x.from] == INF_COST) continue;
			dist[x.to] = min(dist[x.to], dist[x.from] + x.w);
			valid[x.to] = true;
		}
	}
	auto valid_check = [&](auto f, int pos) {
		if (!valid[pos]) return;
		valid[pos] = false;
		for (auto& y: e[pos]) {
			f(f, y.to);
		}
	};
	for (int i = 0; i < G.size(); i++) {
		for (auto& x: e[i]) {
			if (dist[i] == INF_COST) continue;
			if (dist[x.to] > dist[i] + x.w) {
				valid_check(valid_check, x.to);
			}
		}
	}
}
}
using bellman_n::Bellmanford;
template<class T, class U = T> using graph = bellman_n::Graph_B<T, U>;#line 8 "test/aoj/Bellmanford.test.cpp"

int main() {
	int V, E, S;
	cin >> V >> E >> S;
	graph<int> B(V);
	for (int i = 0; i < E; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		B.add_edge(a, b, c);
	}
	Bellmanford(B, S, INT_MAX);
	for (int i = 0; i < V; i++) {
		if (!B.valid[i] && B.dist[i] != INT_MAX) {
			cout << "NEGATIVE CYCLE" << endl;
			return 0;
		}
	}
	for (int i = 0; i < V; i++) {
		if (!B.valid[i]) cout << "INF" << endl;
		else cout << B.dist[i] << endl;
	}
}
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

