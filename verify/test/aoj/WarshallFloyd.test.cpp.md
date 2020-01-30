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
    - Last commit date: 2020-01-27 18:45:58+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_C">https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_C</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/for_include/has_all_shortest_path_graph_tag.cpp.html">for_include/has_all_shortest_path_graph_tag.cpp</a>
* :heavy_check_mark: <a href="../../../library/graph/WarshallFloyd.cpp.html">graph/WarshallFloyd.cpp</a>
* :heavy_check_mark: <a href="../../../library/template/AllShortestPathGraph.cpp.html">template/AllShortestPathGraph.cpp</a>
* :heavy_check_mark: <a href="../../../library/template/Graph.cpp.html">template/Graph.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_C"

#include<bits/stdc++.h>

using namespace std;

#include "../../graph/WarshallFloyd.cpp"
#include "../../template/AllShortestPathGraph.cpp"

int main() {
	int V, E;
	cin >> V >> E;
	auto W = make_all_shortest_path_graph(V);
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
#line 1 "test/aoj/../../graph/../template/AllShortestPathGraph.cpp"
namespace all_shortest_path_graph_n {
#line 1 "test/aoj/../../graph/../template/Graph.cpp"
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
};
#line 3 "test/aoj/../../graph/../template/AllShortestPathGraph.cpp"
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
struct AllShortestPathGraph : Graph<Edge<WEIGHT>, Vertex> {
	struct all_shortest_path_graph_tag {};
	vector<vector<WEIGHT>> dist;
	vector<vector<bool>> valid;
	AllShortestPathGraph(u32 N) : Graph<Edge<WEIGHT>, Vertex>(N), dist(N, vector<WEIGHT>(N)), valid(N, vector<bool>(N)) {}
	using WEIGHT_TYPE = WEIGHT;
};
template<class WEIGHT = long long>
AllShortestPathGraph<WEIGHT> make_all_shortest_path_graph(u32 N) {
	return move(AllShortestPathGraph<WEIGHT>(N));
}
} // all_shortest_path_graph_n
using all_shortest_path_graph_n::AllShortestPathGraph;
using all_shortest_path_graph_n::make_all_shortest_path_graph;
#line 1 "test/aoj/../../graph/../for_include/has_all_shortest_path_graph_tag.cpp"
template <class T>
class has_all_shortest_path_graph_tag {
	template <class U> static constexpr std::true_type check(typename U::all_shortest_path_graph_tag*);
	template <class U> static constexpr std::false_type check(...);
public:
	static constexpr bool value = decltype(check<T>(nullptr))::value;
};
template <class T> constexpr bool has_all_shortest_path_graph_tag_v = has_all_shortest_path_graph_tag<T>::value;
#line 4 "test/aoj/../../graph/WarshallFloyd.cpp"
template<class Graph, class WEIGHT = typename Graph::WEIGHT_TYPE>
enable_if_t<has_all_shortest_path_graph_tag_v<Graph>, bool> WarshallFloyd(Graph& G) {
	const WEIGHT inf = numeric_limits<WEIGHT>::max();
	const int n = G.size();
	auto& dist = G.dist;
	auto& valid = G.valid;
	auto& e = G.e;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			dist[i][j] = inf;
			valid[i][j] = false;
		}
		dist[i][i] = 0;
		valid[i][i] = true;
	}
	for (int i = 0; i < n; i++) {
		for (auto& d : e[i]) {
			dist[i][d.to] = d.weight;
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
				if (dist[i][k] != inf && dist[k][j] != inf) valid[i][j] = valid[i][j] && valid[i][k] && valid[k][j];
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
#line 1 "test/aoj/../../template/AllShortestPathGraph.cpp"
namespace all_shortest_path_graph_n {
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
};
#line 3 "test/aoj/../../template/AllShortestPathGraph.cpp"
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
struct AllShortestPathGraph : Graph<Edge<WEIGHT>, Vertex> {
	struct all_shortest_path_graph_tag {};
	vector<vector<WEIGHT>> dist;
	vector<vector<bool>> valid;
	AllShortestPathGraph(u32 N) : Graph<Edge<WEIGHT>, Vertex>(N), dist(N, vector<WEIGHT>(N)), valid(N, vector<bool>(N)) {}
	using WEIGHT_TYPE = WEIGHT;
};
template<class WEIGHT = long long>
AllShortestPathGraph<WEIGHT> make_all_shortest_path_graph(u32 N) {
	return move(AllShortestPathGraph<WEIGHT>(N));
}
} // all_shortest_path_graph_n
using all_shortest_path_graph_n::AllShortestPathGraph;
using all_shortest_path_graph_n::make_all_shortest_path_graph;
#line 9 "test/aoj/WarshallFloyd.test.cpp"

int main() {
	int V, E;
	cin >> V >> E;
	auto W = make_all_shortest_path_graph(V);
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

