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


# :heavy_check_mark: test/aoj/WarshallFloyd.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/WarshallFloyd.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-15 02:26:23+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_C">https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_C</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/for_include/compare_operators.cpp.html">for_include/compare_operators.cpp</a>
* :heavy_check_mark: <a href="../../../library/for_include/vec.cpp.html">for_include/vec.cpp</a>
* :heavy_check_mark: <a href="../../../library/graph/WarshallFloyd.cpp.html">graph/WarshallFloyd.cpp</a>
* :heavy_check_mark: <a href="../../../library/snippet/WeightedEdge.cpp.html">snippet/WeightedEdge.cpp</a>
* :heavy_check_mark: <a href="../../../library/snippet/WeightedGraph.cpp.html">snippet/WeightedGraph.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_C"

#include<bits/stdc++.h>

using namespace std;

#include "../../graph/WarshallFloyd.cpp"

int main() {
	int V, E;
	cin >> V >> E;
	graph<int> W(V);
	for (int i = 0; i < E; i++) {
		int a, b, c; cin >> a >> b >> c;
		W.add_edge(a, b, c);
	}
	if (WarshallFloyd(W)) {
		for (int i = 0; i < V; i++) {
			for (int j = 0; j < V; j++) {
				if (j) cout << " ";
				if (W.valid[i][j]) cout << W.dist[i][j];
				else cout << "INF";
			}
			cout << endl;
		}
	} else {
		cout << "NEGATIVE CYCLE" << endl;
	}
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj/WarshallFloyd.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_C"

#include<bits/stdc++.h>

using namespace std;

#line 1 "test/aoj/../../graph/WarshallFloyd.cpp"
namespace warshall_floyd_n {
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
};#line 3 "test/aoj/../../graph/WarshallFloyd.cpp"
template<class W, class T = W>
struct Graph_W : public Graph<W> {
	vector<vector<T>> dist;
	vector<vector<char>> valid;
	Graph_W(int n) : Graph<W>(n), dist(n, vector<T>(n)), valid(n, vector<char>(n)) {}
};
template<class W, class T>
bool WarshallFloyd(Graph_W<W, T>& G) {
	const T inf = numeric_limits<T>::max();
	const int n = G.size();
	auto& dist = G.dist;
	auto& valid = G.valid;
	auto& e = G.e;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			dist[i][j] = inf;
			valid[i][j] = 0;
		}
		dist[i][i] = 0;
		valid[i][i] = 1;
	}
	for (int i = 0; i < n; i++) {
		for (auto& d : e[i]) {
			dist[i][d.to] = d.w;
			valid[i][d.to] = 1;
		}
	}
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (valid[i][k] && valid[k][j]) {
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
					valid[i][j] = 1;
				}
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (dist[i][i] < 0) valid[i][i] = 0;
	}
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (dist[i][k] != inf && dist[k][j] != inf) valid[i][j] &= valid[i][k] & valid[k][j];
			}
		}
	}
	bool res = true;
	for (int i = 0; i < n; i++) {
		res = res && valid[i][i];
	}
	return res;
}
}
using warshall_floyd_n::WarshallFloyd;
template<class T, class U = T> using graph = warshall_floyd_n::Graph_W<T, U>;#line 8 "test/aoj/WarshallFloyd.test.cpp"

int main() {
	int V, E;
	cin >> V >> E;
	graph<int> W(V);
	for (int i = 0; i < E; i++) {
		int a, b, c; cin >> a >> b >> c;
		W.add_edge(a, b, c);
	}
	if (WarshallFloyd(W)) {
		for (int i = 0; i < V; i++) {
			for (int j = 0; j < V; j++) {
				if (j) cout << " ";
				if (W.valid[i][j]) cout << W.dist[i][j];
				else cout << "INF";
			}
			cout << endl;
		}
	} else {
		cout << "NEGATIVE CYCLE" << endl;
	}
}
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>
