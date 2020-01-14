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


# :heavy_check_mark: test/aoj/LCA.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/LCA.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-15 01:52:18+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C&lang=ja">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C&lang=ja</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/for_include/vec.cpp.html">for_include/vec.cpp</a>
* :heavy_check_mark: <a href="../../../library/graph_tree/LCA.cpp.html">graph_tree/LCA.cpp</a>
* :heavy_check_mark: <a href="../../../library/snippet/Edge.cpp.html">snippet/Edge.cpp</a>
* :heavy_check_mark: <a href="../../../library/snippet/Graph.cpp.html">snippet/Graph.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#include "../../graph_tree/LCA.cpp"

int main() {
	int V;
	cin >> V;
	graph L(V);
	for (int i = 0; i < V; i++) {
		int k;
		cin >> k;
		for (int j = 0; j < k; j++) {
			int v;
			cin >> v;
			L.add_edge(i, v);
			L.add_edge(v, i);
		}
	}
	L.build(0);
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		int u, v;
		cin >> u >> v;
		cout << L.lca(u, v) << endl;
	}
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj/LCA.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#line 1 "test/aoj/../../graph_tree/LCA.cpp"
namespace lca_n {
#line 1 "test/aoj/../../graph_tree/../snippet/Edge.cpp"
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
#line 1 "test/aoj/../../graph_tree/../snippet/../for_include/vec.cpp"
	using type::begin; using type::end; using type::rbegin; using type::rend;
	using type::cbegin; using type::cend; using type::crbegin; using type::crend;
	using type::size; using type::operator[]; using type::at; using type::back; using type::front;
	using type::reserve; using type::resize; using type::assign; using type::shrink_to_fit;
	using type::clear; using type::erase; using type::insert; using type::swap; 
	using type::push_back; using type::pop_back; using type::emplace_back; using type::empty;
	using typename vector<typename type::value_type, allocator<typename type::value_type>>::iterator;#line 12 "test/aoj/../../graph_tree/../snippet/Edge.cpp"
};#line 2 "test/aoj/../../graph_tree/../snippet/Graph.cpp"
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
};#line 3 "test/aoj/../../graph_tree/LCA.cpp"
struct LCA : public Graph {
	vector<vector<int>> dp;
	vector<int> depth;
	int log2_n;
	LCA(int n) : Graph(n), depth(sz, -100000) {}
	void build(int root) {
		log2_n = 0;
		for (int t = sz; t; t /= 2, log2_n++);
		dp.resize(log2_n, vector<int>(sz, -1));
		dfs(root);
		for (int i = 1; i < log2_n; i++) {
			for (int j = 0; j < sz; j++) {
				if (dp[i-1][j] == -1) dp[i][j] = -1;
				else dp[i][j] = dp[i-1][dp[i-1][j]];
			}
		}
	}
	void dfs(int root) {
		stack<tuple<int, int, int>> s;
		s.emplace(root, -1, 0);
		while (!s.empty()) {
			int now, par, d;
			tie(now, par, d) = s.top(); s.pop();
			dp[0][now] = par;
			depth[now] = d;
			for (auto& x: e[now]) {
				if (x.to != par) s.emplace(x.to, now, d+1);
			}
		}
	}
	int lca(int a, int b) {
		if (depth[a] > depth[b]) swap(a, b);
		for (int i = log2_n - 1; i >= 0 ; i--) {
			if (((depth[b] - depth[a]) >> i) & 1) b = dp[i][b];
		}
		if (a == b) return a;
		for (int i = log2_n - 1; i >= 0; i--) {
			if (dp[i][a] != dp[i][b]) {
				a = dp[i][a];
				b = dp[i][b];
			}
		}
		return dp[0][a];
	}
	int distance(int a, int b) {
		return depth[a] + depth[b] - 2 * depth[lca(a, b)];
	}
};
}
using graph = lca_n::LCA;#line 8 "test/aoj/LCA.test.cpp"

int main() {
	int V;
	cin >> V;
	graph L(V);
	for (int i = 0; i < V; i++) {
		int k;
		cin >> k;
		for (int j = 0; j < k; j++) {
			int v;
			cin >> v;
			L.add_edge(i, v);
			L.add_edge(v, i);
		}
	}
	L.build(0);
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		int u, v;
		cin >> u >> v;
		cout << L.lca(u, v) << endl;
	}
}
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

