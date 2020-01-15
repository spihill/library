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


# :heavy_check_mark: test/yosupo/SCC.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/yosupo/SCC.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-15 22:02:36+09:00


* see: <a href="https://judge.yosupo.jp/problem/scc">https://judge.yosupo.jp/problem/scc</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/for_include/vec.cpp.html">for_include/vec.cpp</a>
* :heavy_check_mark: <a href="../../../library/graph/SCC.cpp.html">graph/SCC.cpp</a>
* :heavy_check_mark: <a href="../../../library/snippet/Edge.cpp.html">snippet/Edge.cpp</a>
* :heavy_check_mark: <a href="../../../library/snippet/Graph.cpp.html">snippet/Graph.cpp</a>


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
	graph G(N);
	for (int i = 0; i < M; i++) {
		int a, b; cin >> a >> b;
		G.add_edge(a, b);
	}
	SCC<graph> scc(G);
	graph res = scc.build();
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
#line 1 "test/yosupo/../../graph/../snippet/Edge.cpp"
struct Edge {
	int to;
	Edge(int t) : to(t) {}
};
struct Edges : private vector<vector<Edge>> {
	using type = vector<vector<Edge>>;
	void add_edge(int u, int v) {
		(*this)[u].emplace_back(v);
	}
	template<class... Args> Edges(Args... args) : vector<vector<Edge>>(args...) {}
#line 1 "test/yosupo/../../graph/../snippet/../for_include/vec.cpp"
	using type::begin; using type::end; using type::rbegin; using type::rend;
	using type::cbegin; using type::cend; using type::crbegin; using type::crend;
	using type::size; using type::operator[]; using type::at; using type::back; using type::front;
	using type::reserve; using type::resize; using type::assign; using type::shrink_to_fit;
	using type::clear; using type::erase; using type::insert; using type::swap; 
	using type::push_back; using type::pop_back; using type::emplace_back; using type::empty;
	using typename vector<typename type::value_type, allocator<typename type::value_type>>::iterator;#line 12 "test/yosupo/../../graph/../snippet/Edge.cpp"
};#line 2 "test/yosupo/../../graph/../snippet/Graph.cpp"
struct Graph {
	int sz;
	vector<vector<Edge>> e;
	Graph(int n) : sz(n), e(n) {}
	template<class... Args>
	inline void add_edge(int pos, Args... args) {
		e[pos].emplace_back(args...);
	}
	inline int size() {
		return sz;
	}
};#line 3 "test/yosupo/../../graph/SCC.cpp"
template<class G>
struct SCC {
	Graph g, rg;
	vector<int> comp;
	SCC(G& g_) : g(g_.size()), rg(g_.size()), comp(g_.size()) {
		for (int i = 0; i < g_.size(); i++) {
			for (auto& x : g_.e[i]) {
				g.add_edge(i, x.to);
				rg.add_edge(x.to, i);
			}
		}
	}
	const int& operator[](int i) { return comp[i];}
	void dfs(int n, vector<char>& used, stack<int>& order) {
		if (used[n]) return;
		used[n] = true;
		for (auto x : g.e[n]) {
			dfs(x.to, used, order);
		}
		order.emplace(n);
	}
	void rdfs(int n, vector<int>& comp, int group) {
		if (comp[n] != -1) return;
		comp[n] = group;
		for (auto x : rg.e[n]) rdfs(x.to, comp, group);
	}
	Graph build() {
		const size_t n = g.size();
		stack<int> order;
		vector<char> used(n, 0);
		for (size_t i = 0; i < n; i++) dfs(i, used, order);

		comp = vector<int>(n, -1);
		int group = 0;
		while (order.size()) {
			int i = order.top(); order.pop();
			if (comp[i] == -1) rdfs(i, comp, group++);
		}

		Graph res(group);
		for (size_t i = 0; i < n; i++) {
			for (auto& x : g.e[i]) {
				int s = comp[i], t = comp[x.to];
				if (s == t) continue;
				res.add_edge(s, t);
			}
		}
		return res;
	}
};
} // scc_n
using graph = scc_n::Graph;
template<class G>
using SCC = scc_n::SCC<G>;#line 6 "test/yosupo/SCC.test.cpp"

int main() {
	int N, M; cin >> N >> M;
	graph G(N);
	for (int i = 0; i < M; i++) {
		int a, b; cin >> a >> b;
		G.add_edge(a, b);
	}
	SCC<graph> scc(G);
	graph res = scc.build();
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

