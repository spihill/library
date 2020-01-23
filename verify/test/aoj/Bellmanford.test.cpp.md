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
    - Last commit date: 2020-01-24 01:30:44+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B&lang=ja">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B&lang=ja</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/for_include/has_shortest_path_graph_tag.cpp.html">for_include/has_shortest_path_graph_tag.cpp</a>
* :heavy_check_mark: <a href="../../../library/graph/Bellmanford.cpp.html">graph/Bellmanford.cpp</a>
* :heavy_check_mark: <a href="../../../library/template/Graph.cpp.html">template/Graph.cpp</a>
* :heavy_check_mark: <a href="../../../library/template/ShortestPathGraph.cpp.html">template/ShortestPathGraph.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#include "../../graph/Bellmanford.cpp"
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
	Bellmanford(G, S, INT_MAX);
	for (int i = 0; i < V; i++) {
		if (!G.valid(i) && G.dist(i) != INT_MAX) {
			cout << "NEGATIVE CYCLE" << endl;
			return 0;
		}
	}
	for (int i = 0; i < V; i++) {
		if (!G.valid(i)) cout << "INF" << endl;
		else cout << G.dist(i) << endl;
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
using u32 = uint_fast32_t;
#line 1 "test/aoj/../../graph/../for_include/has_shortest_path_graph_tag.cpp"
template <class T>
class has_shortest_path_graph_tag {
	template <class U, typename O = typename U::shortest_path_graph_tag> static constexpr std::true_type check(int);
	template <class U> static constexpr std::false_type check(long);
public:
	static constexpr bool value = decltype(check<T>(0))::value;
};
template <class T> constexpr bool has_shortest_path_graph_tag_v = has_shortest_path_graph_tag<T>::value;#line 4 "test/aoj/../../graph/Bellmanford.cpp"
template<class Graph, class WEIGHT = typename Graph::WEIGHT_TYPE>
enable_if_t<has_shortest_path_graph_tag_v<Graph>> Bellmanford(Graph& G, u32 start, WEIGHT INF_COST) {
	for (u32 i = 0; i < G.size(); i++) {
		G.dist(i) = INF_COST;
		G.valid(i) = false;
	}
	auto& e = G.e;
	G.dist(start) = 0, G.valid(start) = 1;
	for (u32 i = 0; i + 1 < G.size(); i++) {
		for (u32 j = 0; j < G.size(); j++) {
			for (auto& x : e[j]) {
				if (G.dist(j) == INF_COST) continue;
				G.dist(x.to) = min(G.dist(x.to), G.dist(j) + x.weight);
				G.valid(x.to) = true;
			}
		}
	}
	auto valid_check = [&](auto&& f, int pos) {
		if (!G.valid(pos)) return;
		G.valid(pos) = false;
		for (auto& x: e[pos]) {
			f(f, x.to);
		}
	};
	for (u32 i = 0; i < G.size(); i++) {
		for (auto& x : e[i]) {
			if (G.dist(i) == INF_COST) continue;
			if (G.dist(x.to) > G.dist(i) + x.weight) {
				valid_check(valid_check, x.to);
			}
		}
	}
}
}
using bellman_n::Bellmanford;#line 1 "test/aoj/../../template/ShortestPathGraph.cpp"
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
};#line 3 "test/aoj/../../template/ShortestPathGraph.cpp"
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
#line 9 "test/aoj/Bellmanford.test.cpp"

int main() {
	int V, E, S;
	cin >> V >> E >> S;
	auto G = make_shortest_path_graph(V);
	for (int i = 0; i < E; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		G.add_edge(a, b, c);
	}
	Bellmanford(G, S, INT_MAX);
	for (int i = 0; i < V; i++) {
		if (!G.valid(i) && G.dist(i) != INT_MAX) {
			cout << "NEGATIVE CYCLE" << endl;
			return 0;
		}
	}
	for (int i = 0; i < V; i++) {
		if (!G.valid(i)) cout << "INF" << endl;
		else cout << G.dist(i) << endl;
	}
}
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

