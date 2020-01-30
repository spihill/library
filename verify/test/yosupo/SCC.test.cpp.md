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


# :x: test/yosupo/SCC.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/yosupo/SCC.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-27 18:45:58+09:00


* see: <a href="https://judge.yosupo.jp/problem/scc">https://judge.yosupo.jp/problem/scc</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/for_include/has_graph_tag.cpp.html">for_include/has_graph_tag.cpp</a>
* :x: <a href="../../../library/graph/SCC.cpp.html">graph/SCC.cpp</a>
* :x: <a href="../../../library/template/RevEdgeGraph.cpp.html">template/RevEdgeGraph.cpp</a>
* :x: <a href="../../../library/template/UnWeightedRevEdgeGraph.cpp.html">template/UnWeightedRevEdgeGraph.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/scc"
#include<bits/stdc++.h>
using namespace std;

#include "../../graph/SCC.cpp"

int main() {
	int N, M; cin >> N >> M;
	auto scc = make_scc(N);
	for (int i = 0; i < M; i++) {
		int a, b; cin >> a >> b;
		scc.add_edge(a, b);
	}
	auto res = scc.build();
	cout << res.size() << endl;
	vector<vector<int>> v(res.size());
	for (int i = 0; i < N; i++) {
		v[scc[i]].push_back(i);
	}
	for (size_t i = 0; i < v.size(); i++) {
		cout << v[i].size();
		for (auto x : v[i]) cout << ' ' << x;
		cout << endl;
	}
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yosupo/SCC.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/scc"
#include<bits/stdc++.h>
using namespace std;

#line 1 "test/yosupo/../../graph/SCC.cpp"
namespace scc_n{
using u32 = uint_fast32_t;
#line 1 "test/yosupo/../../graph/../template/UnWeightedRevEdgeGraph.cpp"
namespace unweighted_revedge_graph_n {
#line 1 "test/yosupo/../../graph/../template/RevEdgeGraph.cpp"
template<class EDGE, class VERTEX>
struct RevEdgeGraph {
	using u32 = uint_fast32_t;
	using u64 = uint_fast64_t;
	struct graph_tag {};
	struct revedge_graph_tag {};
	const u32 n;
	vector<vector<EDGE>> e;
	vector<vector<EDGE>> re;
	vector<VERTEX> v;
	vector<u64> idx;
	vector<u64> ridx;
	RevEdgeGraph(u32 N) : n(N), e(n), re(n), v(n) {}
	template<class...  Args> void add_edge(u32 from, u32 to, Args... args) {
		idx.push_back((static_cast<u64>(from) << 32) | e[from].size());
		e[from].emplace_back(to, args...);
		idx.push_back((static_cast<u64>(from) << 32) | re[to].size());
		re[to].emplace_back(from, args...);
	}
	u32 size() const {return n;}
	using EDGE_TYPE = EDGE;
	using VERTEX_TYPE = VERTEX;
};
#line 3 "test/yosupo/../../graph/../template/UnWeightedRevEdgeGraph.cpp"
using u32 = uint_fast32_t;
struct Vertex {};
struct Edge {
	u32 to;
	Edge(u32 x) : to(x) {}
};
using UnWeightedRevEdgeGraph = RevEdgeGraph<Edge, Vertex>;
UnWeightedRevEdgeGraph make_unweighted_graph(u32 N) {
	return UnWeightedRevEdgeGraph(N);
}
}
using unweighted_revedge_graph_n::UnWeightedRevEdgeGraph;
using unweighted_revedge_graph_n::make_unweighted_graph;
#line 1 "test/yosupo/../../graph/../for_include/has_graph_tag.cpp"
template <class T>
class has_graph_tag {
	template <class U> static constexpr std::true_type check(typename U::graph_tag*);
	template <class U> static constexpr std::false_type check(...);
public:
	static constexpr bool value = decltype(check<T>(nullptr))::value;
};
template <class T> constexpr bool has_graph_tag_v = has_graph_tag<T>::value;
#line 5 "test/yosupo/../../graph/SCC.cpp"
using super_graph = UnWeightedRevEdgeGraph;
struct SCC : super_graph {
	using EDGE = typename super_graph::EDGE_TYPE;
	using VERTEX = typename super_graph::VERTEX_TYPE;
	using graph = super_graph;
	vector<int> comp;
	SCC(u32 N) : super_graph(N), comp(N) {}
	template<class Graph>
	SCC(Graph& g_) : SCC(g_.size()) {
		static_assert(has_graph_tag_v<Graph>, "");
		construct_graph(g_);
	}
	const int& operator[](int i) { return comp[i];}
	void dfs(int n, vector<char>& used, stack<int>& order) {
		if (used[n]) return;
		used[n] = true;
		for (auto& x : this->e[n]) {
			dfs(x.to, used, order);
		}
		order.emplace(n);
	}
	void rdfs(int n, vector<int>& comp, int group) {
		if (comp[n] != -1) return;
		comp[n] = group;
		for (auto& x : this->re[n]) rdfs(x.to, comp, group);
	}
	graph build() {
		const u32 n = this->size();
		stack<int> order;
		vector<char> used(n, 0);
		for (u32 i = 0; i < n; i++) dfs(i, used, order);

		comp = vector<int>(n, -1);
		int group = 0;
		while (order.size()) {
			int i = order.top(); order.pop();
			if (comp[i] == -1) rdfs(i, comp, group++);
		}

		graph res(group);
		for (u32 i = 0; i < n; i++) {
			for (auto& x : this->e[i]) {
				int s = comp[i], t = comp[x.to];
				if (s == t) continue;
				res.add_edge(s, t);
			}
		}
		return res;
	}
private:
	template<class Graph>
	void construct_graph(const Graph& G) {
		for (u32 i = 0; i < G.size(); i++) {
			for (auto& x : G.e[i]) {
				this->e[i].push_back(x.to);
				this->re[x.to].push_back(i);
			}
		}
	}
};
SCC make_scc(u32 N) {
	return SCC(N);
}
} // scc_n
using scc_n::make_scc;
using scc_n::SCC;
#line 6 "test/yosupo/SCC.test.cpp"

int main() {
	int N, M; cin >> N >> M;
	auto scc = make_scc(N);
	for (int i = 0; i < M; i++) {
		int a, b; cin >> a >> b;
		scc.add_edge(a, b);
	}
	auto res = scc.build();
	cout << res.size() << endl;
	vector<vector<int>> v(res.size());
	for (int i = 0; i < N; i++) {
		v[scc[i]].push_back(i);
	}
	for (size_t i = 0; i < v.size(); i++) {
		cout << v[i].size();
		for (auto x : v[i]) cout << ' ' << x;
		cout << endl;
	}
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

