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
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: 最大流 (Ford-Fulkerson)

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/FordFulkerson.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-27 18:45:58+09:00


* 最大流を求める $O(Ef)$


## Depends on

* :heavy_check_mark: <a href="../for_include/has_flow_graph_tag.cpp.html">for_include/has_flow_graph_tag.cpp</a>
* :heavy_check_mark: <a href="../template/FlowGraph.cpp.html">template/FlowGraph.cpp</a>
* :heavy_check_mark: <a href="../template/RevGraph.cpp.html">template/RevGraph.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/FordFulkerson.test.cpp.html">test/aoj/FordFulkerson.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * @title 最大流 (Ford-Fulkerson)
 * @brief 最大流を求める $O(Ef)$
 */
namespace fordfulkerson_n {
#include "../template/FlowGraph.cpp"
#include "../for_include/has_flow_graph_tag.cpp"
using u32 = uint_fast32_t;
template<class Graph, class CAPACITY = typename Graph::CAPACITY_TYPE>
enable_if_t<has_flow_graph_tag_v<Graph>, CAPACITY> FordFulkerson(Graph& G, u32 start, u32 goal) {
	constexpr CAPACITY FLOW_INF = numeric_limits<CAPACITY>::max();
	vector<char> used(G.size(), 0);
	auto dfs = [&](auto&& f, u32 s, u32 t, CAPACITY c) -> CAPACITY {
		if (used[s]) return 0;
		used[s] = true;
		if (s == t) return c;
		for (auto& x : G.e[s]) {
			if (x.capacity == 0) continue;
			CAPACITY res = f(f, x.to, t, min(c, x.capacity));
			if (res > 0) {
				x.capacity -= res;
				G.e[x.to][x.rev].capacity += res;
				return res;
			}
		}
		return 0;
	};
	CAPACITY res = 0;
	for (;;) {
		fill(used.begin(), used.end(), 0);
		CAPACITY r = dfs(dfs, start, goal, FLOW_INF);
		if (r == 0) break;
		res += r;
	}
	return res;
}
} // fordfulkerson_n
using fordfulkerson_n::FordFulkerson;
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/FordFulkerson.cpp"
/**
 * @title 最大流 (Ford-Fulkerson)
 * @brief 最大流を求める $O(Ef)$
 */
namespace fordfulkerson_n {
#line 1 "graph/../template/FlowGraph.cpp"
namespace flow_graph_n{
#line 1 "graph/../template/RevGraph.cpp"
template<class EDGE, class VERTEX>
struct RevGraph {
	using u32 = uint_fast32_t;
	using u64 = uint_fast64_t;
	struct graph_tag {};
	struct rev_graph_tag {};
	const u32 n;
	vector<vector<EDGE>> e;
	vector<VERTEX> v;
	vector<u64> idx;
	RevGraph(u32 N) : n(N), e(n), v(n) {}
	template<class...  Args> void add_edge(u32 from, u32 to, Args... args) {
		idx.push_back((static_cast<u64>(from) << 32) | e[from].size());
		e[from].emplace_back(to, e[to].size(), args...);
		idx.push_back((static_cast<u64>(to) << 32) | e[to].size());
		e[to].emplace_back(from, e[from].size()-1, args..., 0);
	}
	u32 size() const {return n;}
	using EDGE_TYPE = EDGE;
	using VERTEX_TYPE = VERTEX;
};#line 3 "graph/../template/FlowGraph.cpp"
using u32 = uint_fast32_t;
using i64 = int_fast64_t;
struct Vertex {};
template<class CAPACITY>
struct Edge {
	u32 to;
	u32 rev;
	CAPACITY capacity;
	Edge(u32 x, u32 y, CAPACITY c) : to(x), rev(y), capacity(c) {}
	Edge(u32 x, u32 y, CAPACITY c, int) : to(x), rev(y), capacity(0) {}
};
template<class CAPACITY = i64>
struct FlowGraph : RevGraph<Edge<CAPACITY>, Vertex> {
	struct flow_graph_tag {};
	FlowGraph(u32 N) : RevGraph<Edge<CAPACITY>, Vertex>(N) {}
	using CAPACITY_TYPE = CAPACITY;
};
template<class CAPACITY = i64>
FlowGraph<CAPACITY> make_flow_graph(u32 N) {
	return FlowGraph<CAPACITY>(N);
}
} // flow_graph_n
using flow_graph_n::FlowGraph;
using flow_graph_n::make_flow_graph;#line 1 "graph/../for_include/has_flow_graph_tag.cpp"
template <class T>
class has_flow_graph_tag {
	template <class U> static constexpr std::true_type check(typename U::flow_graph_tag*);
	template <class U> static constexpr std::false_type check(...);
public:
	static constexpr bool value = decltype(check<T>(nullptr))::value;
};
template <class T> constexpr bool has_flow_graph_tag_v = has_flow_graph_tag<T>::value;#line 8 "graph/FordFulkerson.cpp"
using u32 = uint_fast32_t;
template<class Graph, class CAPACITY = typename Graph::CAPACITY_TYPE>
enable_if_t<has_flow_graph_tag_v<Graph>, CAPACITY> FordFulkerson(Graph& G, u32 start, u32 goal) {
	constexpr CAPACITY FLOW_INF = numeric_limits<CAPACITY>::max();
	vector<char> used(G.size(), 0);
	auto dfs = [&](auto&& f, u32 s, u32 t, CAPACITY c) -> CAPACITY {
		if (used[s]) return 0;
		used[s] = true;
		if (s == t) return c;
		for (auto& x : G.e[s]) {
			if (x.capacity == 0) continue;
			CAPACITY res = f(f, x.to, t, min(c, x.capacity));
			if (res > 0) {
				x.capacity -= res;
				G.e[x.to][x.rev].capacity += res;
				return res;
			}
		}
		return 0;
	};
	CAPACITY res = 0;
	for (;;) {
		fill(used.begin(), used.end(), 0);
		CAPACITY r = dfs(dfs, start, goal, FLOW_INF);
		if (r == 0) break;
		res += r;
	}
	return res;
}
} // fordfulkerson_n
using fordfulkerson_n::FordFulkerson;
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

