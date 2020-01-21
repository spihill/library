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


# :heavy_check_mark: test/aoj/Dinic.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/Dinic.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-22 00:29:08+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A&lang=ja">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A&lang=ja</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/for_include/has_flow_graph_tag.cpp.html">for_include/has_flow_graph_tag.cpp</a>
* :heavy_check_mark: <a href="../../../library/graph/Dinic.cpp.html">最大流 (Dinic)</a>
* :heavy_check_mark: <a href="../../../library/template/FlowGraph.cpp.html">template/FlowGraph.cpp</a>
* :heavy_check_mark: <a href="../../../library/template/UnWeightedGraph.cpp.html">template/UnWeightedGraph.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#include "../../template/FlowGraph.cpp"
#include "../../graph/Dinic.cpp"

int main() {
	int n, m;
	cin >> n >> m;
	auto G = make_flow_graph(n);
	for (int i = 0; i < m; i++) {
		int u, v, c;
		cin >> u >> v >> c;
		G.add_edge(u, v, c);
	}
	cout << Dinic(G, 0, n-1) << endl;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj/Dinic.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#line 1 "test/aoj/../../template/FlowGraph.cpp"
namespace flow_graph_n{
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
}#line 3 "test/aoj/../../template/FlowGraph.cpp"
template<class VertexType = long long, class CapacityType = long long>
struct FlowGraph : UnWeightedGraph<VertexType> {
	using UnWeightedGraph<VertexType>::index;
	using UnWeightedGraph<VertexType>::restore;
	using UnWeightedGraph<VertexType>::size;
	struct flow_graph_tag {};
	vector<vector<CapacityType>> capacity;
	vector<vector<size_t>> revedge;
	FlowGraph(size_t N) : UnWeightedGraph<VertexType>(N), capacity(N), revedge(N) {}
	template<class T, class U> void add_edge(T from, U to, CapacityType c) {
		this->edge[index(from)].push_back(index(to));
		capacity[index(from)].push_back(c);
		revedge[index(from)].push_back(this->edge[index(to)].size());

		this->edge[index(to)].push_back(index(from));
		capacity[index(to)].push_back(CapacityType());
		revedge[index(to)].push_back(this->edge[index(from)].size()-1);
	}
	void clear() {
		this->edge.clear();
		capacity.clear();
		revedge.clear();
	}
	using capacity_type = CapacityType;
};
template<class V = long long, class C = long long>
FlowGraph<V, C> make_flow_graph(size_t N) {
	return move(FlowGraph<V, C>(N));
}
} // weighted_graph_n
template<class V, class C> using FlowGraph = flow_graph_n::FlowGraph<V, C>;
using flow_graph_n::make_flow_graph;#line 1 "test/aoj/../../graph/Dinic.cpp"
/**
 * @title 最大流 (Dinic)
 * @brief 最大流を求める $O(V^2E)$
 */
namespace dinic_n {
#line 1 "test/aoj/../../graph/../template/FlowGraph.cpp"
namespace flow_graph_n{
#line 1 "test/aoj/../../graph/../template/UnWeightedGraph.cpp"
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
}#line 3 "test/aoj/../../graph/../template/FlowGraph.cpp"
template<class VertexType = long long, class CapacityType = long long>
struct FlowGraph : UnWeightedGraph<VertexType> {
	using UnWeightedGraph<VertexType>::index;
	using UnWeightedGraph<VertexType>::restore;
	using UnWeightedGraph<VertexType>::size;
	struct flow_graph_tag {};
	vector<vector<CapacityType>> capacity;
	vector<vector<size_t>> revedge;
	FlowGraph(size_t N) : UnWeightedGraph<VertexType>(N), capacity(N), revedge(N) {}
	template<class T, class U> void add_edge(T from, U to, CapacityType c) {
		this->edge[index(from)].push_back(index(to));
		capacity[index(from)].push_back(c);
		revedge[index(from)].push_back(this->edge[index(to)].size());

		this->edge[index(to)].push_back(index(from));
		capacity[index(to)].push_back(CapacityType());
		revedge[index(to)].push_back(this->edge[index(from)].size()-1);
	}
	void clear() {
		this->edge.clear();
		capacity.clear();
		revedge.clear();
	}
	using capacity_type = CapacityType;
};
template<class V = long long, class C = long long>
FlowGraph<V, C> make_flow_graph(size_t N) {
	return move(FlowGraph<V, C>(N));
}
} // weighted_graph_n
template<class V, class C> using FlowGraph = flow_graph_n::FlowGraph<V, C>;
using flow_graph_n::make_flow_graph;#line 1 "test/aoj/../../graph/../for_include/has_flow_graph_tag.cpp"
template <class T>
class has_flow_graph_tag {
	template <class U, typename O = typename U::flow_graph_tag> static constexpr std::true_type check(int);
	template <class U> static constexpr std::false_type check(long);
public:
	static constexpr bool value = decltype(check<T>(0))::value;
};
template <class T> constexpr bool has_flow_graph_tag_v = has_flow_graph_tag<T>::value;#line 8 "test/aoj/../../graph/Dinic.cpp"
template<class Graph, class T, class U, class C = typename Graph::capacity_type>
enable_if_t<has_flow_graph_tag_v<Graph>, C> Dinic(Graph& G, T Start, U Goal) {
	constexpr C FLOW_INF = numeric_limits<C>::max();
	size_t start = Graph::index(Start);
	size_t goal = Graph::index(Goal);
	vector<int> level(G.size());
	vector<size_t> iter(G.size());
	auto dfs = [&](auto&& f, size_t s, size_t g, C flow) -> C {
		if (s == g) return flow;
		for (size_t& i = iter[s]; i < G.edge[s].size(); i++) {
			auto& to = G.edge[s][i];
			auto& cap = G.capacity[s][i];
			auto& rev = G.revedge[s][i];
			if (cap == 0 || level[s] >= level[to]) continue;
			C d;
			if ((d = f(f, to, g, min(flow, cap))) > 0) {
				cap -= d;
				G.capacity[to][rev] += d;
				return d;
			}
		}
		return 0;
	};
	auto bfs = [&] (int s) -> void {
		fill(level.begin(), level.end(), -1);
		queue<pair<int, int>> q;
		q.push(make_pair(s, 0));
		while (!q.empty()) {
			auto x = q.front();
			q.pop();
			int a = x.first;
			int b = x.second;
			if (level[a] != -1) continue;
			level[a] = b;
			for (size_t i = 0; i < G.edge[a].size(); i++) {
				if (G.capacity[a][i] > 0) q.push(make_pair(G.edge[a][i], b+1));
			}
		}
	};
	C res = 0;
	for (;;) {
		bfs(start);
		if (level[goal] < 0) return res;
		fill(iter.begin(), iter.end(), 0);
		for (C r = 1; r;) {
			r = dfs(dfs, start, goal, FLOW_INF);
			res += r;
		}
	}
}
}
using dinic_n::Dinic;#line 9 "test/aoj/Dinic.test.cpp"

int main() {
	int n, m;
	cin >> n >> m;
	auto G = make_flow_graph(n);
	for (int i = 0; i < m; i++) {
		int u, v, c;
		cin >> u >> v >> c;
		G.add_edge(u, v, c);
	}
	cout << Dinic(G, 0, n-1) << endl;
}
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

