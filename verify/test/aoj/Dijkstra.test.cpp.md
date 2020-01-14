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


# :heavy_check_mark: test/aoj/Dijkstra.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/Dijkstra.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-15 01:52:18+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/for_include/compare_operators.cpp.html">for_include/compare_operators.cpp</a>
* :heavy_check_mark: <a href="../../../library/for_include/vec.cpp.html">for_include/vec.cpp</a>
* :heavy_check_mark: <a href="../../../library/graph/Dijkstra.cpp.html">graph/Dijkstra.cpp</a>
* :heavy_check_mark: <a href="../../../library/snippet/WeightedEdge.cpp.html">snippet/WeightedEdge.cpp</a>
* :heavy_check_mark: <a href="../../../library/snippet/WeightedGraph.cpp.html">snippet/WeightedGraph.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#include "../../graph/Dijkstra.cpp"

int main() {
	int V, E, S;
	cin >> V >> E >> S;
	graph<int> D(V);
	for (int i = 0; i < E; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		D.add_edge(a, b, c);
	}
	Dijkstra(D, S, INT_MAX);
	for (int i = 0; i < V; i++) {
		if (D.dist[i] == INT_MAX) cout << "INF" << endl;
		else cout << D.dist[i] << endl;
	}
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj/Dijkstra.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#line 1 "test/aoj/../../graph/Dijkstra.cpp"
namespace dijkstra_n {
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
};#line 2 "test/aoj/../../graph/../snippet/WeightedGraph.cpp"
template<class W>
struct Graph {
	const int sz;
	Edges<W> e;
	Graph(int n) : sz(n), e(sz) {}
	template<class... Args> void add_edge(int u, int v, Args... args) {
		e.add_edge(u, v, args...);
	}
	int size() {
		return sz;
	}
};#line 3 "test/aoj/../../graph/Dijkstra.cpp"
template<class W, class T = W>
struct Graph_D : public Graph<W> {
	vector<T> dist;
	Graph_D(int n) : Graph<W>(n), dist(n) {}
};
template<class W, class T>
void Dijkstra(Graph_D<W, T>& g, int start, T INF_COST) {
	auto& dist = g.dist;
	auto& e = g.e;
	for (auto& ww : dist) ww = INF_COST;
	using Q_T = pair<T, int>;
	priority_queue<Q_T, vector<Q_T>, greater<>> q;
	q.emplace(0, start);
	while (!q.empty()) {
		auto a = q.top();
		q.pop();
		if (a.first >= dist[a.second]) continue;
		dist[a.second] = a.first;
	for (auto& p : e[a.second]) {
			if (p.w == INF_COST) continue;
			if (a.first + p.w < dist[p.to]) q.emplace(a.first + p.w, p.to);
		}
	}
}
}
using dijkstra_n::Dijkstra;
template<class T, class U = T> using graph = dijkstra_n::Graph_D<T, U>;#line 8 "test/aoj/Dijkstra.test.cpp"

int main() {
	int V, E, S;
	cin >> V >> E >> S;
	graph<int> D(V);
	for (int i = 0; i < E; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		D.add_edge(a, b, c);
	}
	Dijkstra(D, S, INT_MAX);
	for (int i = 0; i < V; i++) {
		if (D.dist[i] == INT_MAX) cout << "INF" << endl;
		else cout << D.dist[i] << endl;
	}
}
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

