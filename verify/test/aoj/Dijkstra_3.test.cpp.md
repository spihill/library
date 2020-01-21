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


# :heavy_check_mark: test/aoj/Dijkstra_3.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/Dijkstra_3.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-22 01:17:18+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/12/ALDS1_12_C">https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/12/ALDS1_12_C</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/for_include/has_shortest_path_graph_tag.cpp.html">for_include/has_shortest_path_graph_tag.cpp</a>
* :heavy_check_mark: <a href="../../../library/graph/Dijkstra.cpp.html">graph/Dijkstra.cpp</a>
* :heavy_check_mark: <a href="../../../library/template/ShortestPathGraph.cpp.html">template/ShortestPathGraph.cpp</a>
* :heavy_check_mark: <a href="../../../library/template/UnWeightedGraph.cpp.html">template/UnWeightedGraph.cpp</a>
* :heavy_check_mark: <a href="../../../library/template/WeightedGraph.cpp.html">template/WeightedGraph.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/12/ALDS1_12_C"

#include<bits/stdc++.h>

using namespace std;

#include "../../graph/Dijkstra.cpp"
#include "../../template/ShortestPathGraph.cpp"

int main() {
	int n; cin >> n;
	auto G = make_shortest_path_graph(n);
	for (int i = 0; i < n; i++) {
		int v, k; cin >> v >> k;
		while (k--) {
			int u, c; cin >> u >> c;
			G.add_edge(v, u, c);
		}
	}
	Dijkstra(G, 0, INT_MAX);
	for (int i = 0; i < n; i++) {
		cout << i << " " << G.dist[i] << endl;
	}
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj/Dijkstra_3.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/12/ALDS1_12_C"

#include<bits/stdc++.h>

using namespace std;

#line 1 "test/aoj/../../graph/Dijkstra.cpp"
namespace dijkstra_n {
#line 1 "test/aoj/../../graph/../for_include/has_shortest_path_graph_tag.cpp"
template <class T>
class has_shortest_path_graph_tag {
	template <class U, typename O = typename U::shortest_path_graph_tag> static constexpr std::true_type check(int);
	template <class U> static constexpr std::false_type check(long);
public:
	static constexpr bool value = decltype(check<T>(0))::value;
};
template <class T> constexpr bool has_shortest_path_graph_tag_v = has_shortest_path_graph_tag<T>::value;#line 3 "test/aoj/../../graph/Dijkstra.cpp"
template<class Graph, class V, class W = typename Graph::weight_type>
enable_if_t<has_shortest_path_graph_tag_v<Graph>> Dijkstra(Graph& g, V start, W INF_COST) {
	auto& dist = g.dist;
	auto& valid = g.valid;
	auto& e = g.edge;
	auto& w = g.weight;
	int s = Graph::index(start);
	fill(dist.begin(), dist.end(), INF_COST);
	fill(valid.begin(), valid.end(), 0);
	using Q_T = pair<W, int>;
	priority_queue<Q_T, vector<Q_T>, greater<>> q;
	q.emplace(0, s);
	while (!q.empty()) {
		auto a = q.top(); q.pop();
		assert(a.second < (int) g.size());
		valid[a.second] = 1;
		if (a.first >= dist[a.second]) continue;
		dist[a.second] = a.first;
		for (size_t i = 0; i < e[a.second].size(); i++) {
			if (w[a.second][i] == INF_COST) continue;
			if (a.first + w[a.second][i] < dist[e[a.second][i]]) q.emplace(a.first + w[a.second][i], e[a.second][i]);
		}
	}
}
}
using dijkstra_n::Dijkstra;#line 1 "test/aoj/../../template/ShortestPathGraph.cpp"
namespace shortest_path_graph_n {
#line 1 "test/aoj/../../template/WeightedGraph.cpp"
namespace weighted_graph_n{
#line 1 "test/aoj/../../template/UnWeightedGraph.cpp"
template<class VertexType = long long>
struct UnWeightedGraph {
	template<class T> static enable_if_t<is_integral<T>::value, size_t>  index(T x) {return x;}
	template<class T> static enable_if_t<is_integral<T>::value, T>     restore(T x) {return x;}
	template<class T> static enable_if_t<!is_integral<T>::value, size_t> index(T x) {return x.index();}
	template<class T> static enable_if_t<!is_integral<T>::value, T>    restore(T x) {return x.restore();}
	struct graph_tag {};
	vector<vector<size_t>> edge;
	const int n;
	UnWeightedGraph(size_t N) : edge(N), n(N) {}
	template<class T, class U> void add_edge(T from, U to) {
		edge[index(from)].push_back(index(to));
	}
	size_t size() const {
		return n;
	}
	void clear() {
		edge.clear();
	}
	using vertex_type = VertexType;
};
template<class T = long long>
UnWeightedGraph<T> make_unweighted_graph(size_t N) {
	return move(UnWeightedGraph<T>(N));
}#line 3 "test/aoj/../../template/WeightedGraph.cpp"
template<class VertexType = long long, class WeightType = long long>
struct WeightedGraph : UnWeightedGraph<VertexType> {
	using UnWeightedGraph<VertexType>::index;
	using UnWeightedGraph<VertexType>::restore;
	using UnWeightedGraph<VertexType>::size;
	struct weighted_graph_tag {};
	vector<vector<WeightType>> weight;
	WeightedGraph(size_t N) : UnWeightedGraph<VertexType>(N), weight(N) {}
	template<class T, class U> void add_edge(T from, U to, WeightType w) {
		this->edge[index(from)].push_back(index(to));
		weight[index(from)].push_back(w);
	}
	void clear() {
		this->edge.clear();
		weight.clear();
	}
	using weight_type = WeightType;
};
template<class T = long long, class W = long long>
WeightedGraph<T, W> make_weighted_graph(size_t N) {
	return move(WeightedGraph<T, W>(N));
}
} // weighted_graph_n
template<class T, class W> using WeightedGraph = weighted_graph_n::WeightedGraph<T, W>;
using weighted_graph_n::make_weighted_graph;#line 3 "test/aoj/../../template/ShortestPathGraph.cpp"
template<class VertexType = long long, class WeightType = long long>
struct ShortestPathGraph : WeightedGraph<VertexType, WeightType> {
	using WeightedGraph<VertexType, WeightType>::index;
	using WeightedGraph<VertexType, WeightType>::restore;
	using WeightedGraph<VertexType, WeightType>::size;
	struct shortest_path_graph_tag {};
	vector<WeightType> dist;
	vector<char> valid;
	ShortestPathGraph(size_t N) : WeightedGraph<VertexType, WeightType>(N), dist(N), valid(N) {}
};
template<class T = long long, class W = long long>
ShortestPathGraph<T, W> make_shortest_path_graph(size_t N) {
	return move(ShortestPathGraph<T, W>(N));
}
} // shortest_path_graph_n
template<class T, class W> using ShortestPathGraph = shortest_path_graph_n::ShortestPathGraph<T, W>;
using shortest_path_graph_n::make_shortest_path_graph;#line 9 "test/aoj/Dijkstra_3.test.cpp"

int main() {
	int n; cin >> n;
	auto G = make_shortest_path_graph(n);
	for (int i = 0; i < n; i++) {
		int v, k; cin >> v >> k;
		while (k--) {
			int u, c; cin >> u >> c;
			G.add_edge(v, u, c);
		}
	}
	Dijkstra(G, 0, INT_MAX);
	for (int i = 0; i < n; i++) {
		cout << i << " " << G.dist[i] << endl;
	}
}
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

