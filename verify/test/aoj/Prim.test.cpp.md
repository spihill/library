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


# :heavy_check_mark: test/aoj/Prim.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#0d0c91c0cca30af9c1c9faef0cf04aa9">test/aoj</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/Prim.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-27 18:45:58+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A&lang=jp">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A&lang=jp</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/for_include/has_weighted_graph_tag.cpp.html">for_include/has_weighted_graph_tag.cpp</a>
* :heavy_check_mark: <a href="../../../library/graph/Prim.cpp.html">graph/Prim.cpp</a>
* :heavy_check_mark: <a href="../../../library/template/Graph.cpp.html">template/Graph.cpp</a>
* :heavy_check_mark: <a href="../../../library/template/WeightedGraph.cpp.html">template/WeightedGraph.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A&lang=jp"

#include<bits/stdc++.h>

using namespace std;

#include "../../graph/Prim.cpp"
#include "../../template/WeightedGraph.cpp"


int main() {
	int V, E;
	cin >> V >> E;
	auto P = make_weighted_graph(V);
	for (int i = 0; i < E; i++) {
		int s, t, w;
		cin >> s >> t >> w;
		P.add_edge(s, t, w);
		P.add_edge(t, s, w);
	}
	cout << Prim(P) << endl;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj/Prim.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A&lang=jp"

#include<bits/stdc++.h>

using namespace std;

#line 1 "test/aoj/../../graph/Prim.cpp"
namespace prim_n {
#line 1 "test/aoj/../../graph/../for_include/has_weighted_graph_tag.cpp"
template <class T>
class has_weighted_graph_tag {
	template <class U> static constexpr std::true_type check(typename U::weighted_graph_tag*);
	template <class U> static constexpr std::false_type check(...);
public:
	static constexpr bool value = decltype(check<T>(nullptr))::value;
};
template <class T> constexpr bool has_weighted_graph_tag_v = has_weighted_graph_tag<T>::value;
#line 3 "test/aoj/../../graph/Prim.cpp"
template<class Graph, class WEIGHT = typename Graph::WEIGHT_TYPE>
enable_if_t<has_weighted_graph_tag_v<Graph>, WEIGHT> Prim(Graph& G) {
	WEIGHT res = 0;
	vector<char> used(G.size(), 0);
	priority_queue<pair<WEIGHT, int>, vector<pair<WEIGHT, int>>, greater<>> q;
	q.emplace(0, 0);
	while (!q.empty()) {
		auto p = q.top(); q.pop();
		if (used[p.second] != 0) continue;
		used[p.second] = 1;
		res += p.first;
		for (auto& x : G.e[p.second]) {
			q.emplace(x.weight, x.to);
		}
	}
	return res;
}
}
using prim_n::Prim;
#line 1 "test/aoj/../../template/WeightedGraph.cpp"
namespace weighted_graph_n{
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
#line 3 "test/aoj/../../template/WeightedGraph.cpp"
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
struct WeightedGraph : public Graph<Edge<WEIGHT>, Vertex> {
	struct weighted_graph_tag {};
	WeightedGraph(u32 N) : Graph<Edge<WEIGHT>, Vertex>(N) {}
	using WEIGHT_TYPE = WEIGHT;
};
template<class WEIGHT = i64>
WeightedGraph<WEIGHT> make_weighted_graph(u32 N) {
	return WeightedGraph<WEIGHT>(N);
}
} // weighted_graph_n
using weighted_graph_n::WeightedGraph;
using weighted_graph_n::make_weighted_graph;
#line 9 "test/aoj/Prim.test.cpp"


int main() {
	int V, E;
	cin >> V >> E;
	auto P = make_weighted_graph(V);
	for (int i = 0; i < E; i++) {
		int s, t, w;
		cin >> s >> t >> w;
		P.add_edge(s, t, w);
		P.add_edge(t, s, w);
	}
	cout << Prim(P) << endl;
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

