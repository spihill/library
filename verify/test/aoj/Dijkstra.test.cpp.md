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

* category: <a href="../../../index.html#0d0c91c0cca30af9c1c9faef0cf04aa9">test/aoj</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/Dijkstra.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-27 18:45:58+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/for_include/has_shortest_path_graph_tag.cpp.html">for_include/has_shortest_path_graph_tag.cpp</a>
* :heavy_check_mark: <a href="../../../library/graph/Dijkstra.cpp.html">graph/Dijkstra.cpp</a>
* :heavy_check_mark: <a href="../../../library/template/Graph.cpp.html">template/Graph.cpp</a>
* :heavy_check_mark: <a href="../../../library/template/ShortestPathGraph.cpp.html">template/ShortestPathGraph.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#include "../../graph/Dijkstra.cpp"
#include "../../template/ShortestPathGraph.cpp"


int main() {
	int V, E, S;
	cin >> V >> E >> S;
	auto G = make_shortest_path_graph(V);
	for (int i = 0; i < E; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		G.add_edge(a, b, c);
	}
	Dijkstra(G, S, INT_MAX);
	for (int i = 0; i < V; i++) {
		if (G.dist(i) == INT_MAX) {
			cout << "INF" << endl;
			assert(!G.valid(i));
		}
		else {
			cout << G.dist(i) << endl;
			assert(G.valid(i));
		}
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
using u32 = uint_fast32_t;
#line 1 "test/aoj/../../graph/../for_include/has_shortest_path_graph_tag.cpp"
template <class T>
class has_shortest_path_graph_tag {
	template <class U> static constexpr std::true_type check(typename U::shortest_path_graph_tag*);
	template <class U> static constexpr std::false_type check(...);
public:
	static constexpr bool value = decltype(check<T>(nullptr))::value;
};
template <class T> constexpr bool has_shortest_path_graph_tag_v = has_shortest_path_graph_tag<T>::value;
#line 4 "test/aoj/../../graph/Dijkstra.cpp"
template<class Graph, class WEIGHT = typename Graph::WEIGHT_TYPE>
enable_if_t<has_shortest_path_graph_tag_v<Graph>> Dijkstra(Graph& G, u32 start, WEIGHT INF_COST) {
	auto& e = G.e;
	for (u32 i = 0; i < G.size(); i++) {
		G.dist(i) = INF_COST;
		G.valid(i) = false;
	}
	using Q_T = pair<WEIGHT, int>;
	priority_queue<Q_T, vector<Q_T>, greater<>> q;
	q.emplace(WEIGHT(0), start);
	while (!q.empty()) {
		auto a = q.top(); q.pop();
		G.valid(a.second) = 1;
		if (a.first >= G.dist(a.second)) continue;
		G.dist(a.second) = a.first;
		for (auto& x : e[a.second]) {
			if (x.weight == INF_COST) continue;
			if (a.first + x.weight < G.dist(x.to)) q.emplace(a.first + x.weight, x.to);
		}
	}
}
}
using dijkstra_n::Dijkstra;
#line 1 "test/aoj/../../template/ShortestPathGraph.cpp"
namespace shortest_path_graph_n {
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
#line 3 "test/aoj/../../template/ShortestPathGraph.cpp"
using u32 = uint_fast32_t;
using i64 = int_fast64_t;
template<class WEIGHT>
struct Vertex {
	WEIGHT dist;
	bool valid;
};
template<class WEIGHT>
struct Edge {
	u32 to;
	WEIGHT weight;
	Edge(u32 x, WEIGHT w) : to(x), weight(w) {}
};
template<class WEIGHT>
struct ShortestPathGraph : Graph<Edge<WEIGHT>, Vertex<WEIGHT>> {
	struct shortest_path_graph_tag {};
	ShortestPathGraph(u32 N) : Graph<Edge<WEIGHT>, Vertex<WEIGHT>>(N) {}
	WEIGHT& dist(u32 i) {return this->v[i].dist;}
	bool& valid(u32 i) {return this->v[i].valid;}
	using WEIGHT_TYPE = WEIGHT;
};
template<class WEIGHT = long long>
ShortestPathGraph<WEIGHT> make_shortest_path_graph(u32 N) {
	return move(ShortestPathGraph<WEIGHT>(N));
}
} // shortest_path_graph_n
using shortest_path_graph_n::ShortestPathGraph;
using shortest_path_graph_n::make_shortest_path_graph;
#line 9 "test/aoj/Dijkstra.test.cpp"


int main() {
	int V, E, S;
	cin >> V >> E >> S;
	auto G = make_shortest_path_graph(V);
	for (int i = 0; i < E; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		G.add_edge(a, b, c);
	}
	Dijkstra(G, S, INT_MAX);
	for (int i = 0; i < V; i++) {
		if (G.dist(i) == INT_MAX) {
			cout << "INF" << endl;
			assert(!G.valid(i));
		}
		else {
			cout << G.dist(i) << endl;
			assert(G.valid(i));
		}
	}
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

