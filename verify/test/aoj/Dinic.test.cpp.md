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
    - Last commit date: 2020-01-15 01:52:18+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A&lang=ja">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A&lang=ja</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/for_include/vec.cpp.html">for_include/vec.cpp</a>
* :heavy_check_mark: <a href="../../../library/graph/Dinic.cpp.html">graph/Dinic.cpp</a>
* :heavy_check_mark: <a href="../../../library/snippet/FlowEdge.cpp.html">snippet/FlowEdge.cpp</a>
* :heavy_check_mark: <a href="../../../library/snippet/FlowGraph.cpp.html">snippet/FlowGraph.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#include "../../graph/Dinic.cpp"

int main() {
	int n, m;
	cin >> n >> m;
	dinic<int> D(n);
	for (int i = 0; i < m; i++) {
		int u, v, c;
		cin >> u >> v >> c;
		D.add_edge(u, v, c);
	}
	cout << D.solve(0, n-1) << endl;
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

#line 1 "test/aoj/../../graph/Dinic.cpp"
namespace dinic_n {
#line 1 "test/aoj/../../graph/../snippet/FlowEdge.cpp"
template<class F>
struct Edge {
	int to;
	F cap;
	int rev;
	Edge(int x, F y, int z) : to(x), cap(y), rev(z) {}
};
template<class F>
struct Edges : private vector<vector<Edge<F>>> {
	using type = vector<vector<Edge<F>>>;
	template<class... Args> Edges(Args... args) : type(args...) {}
	template<class... Args> void add_edge(int u, int v, Args... args) {
		(*this)[u].emplace_back(v, args...);
	}
#line 1 "test/aoj/../../graph/../snippet/../for_include/vec.cpp"
	using type::begin; using type::end; using type::rbegin; using type::rend;
	using type::cbegin; using type::cend; using type::crbegin; using type::crend;
	using type::size; using type::operator[]; using type::at; using type::back; using type::front;
	using type::reserve; using type::resize; using type::assign; using type::shrink_to_fit;
	using type::clear; using type::erase; using type::insert; using type::swap; 
	using type::push_back; using type::pop_back; using type::emplace_back; using type::empty;
	using typename vector<typename type::value_type, allocator<typename type::value_type>>::iterator;#line 16 "test/aoj/../../graph/../snippet/FlowEdge.cpp"
};#line 2 "test/aoj/../../graph/../snippet/FlowGraph.cpp"
template<class F>
struct Graph {
	const int sz;
	Edges<F> e;
	Graph(int n) : sz(n), e(sz) {}
	// add_edge(from, to, cap)
	template<class... Args> void add_edge(int from, int to, F cap) {
		e.add_edge(from, to, cap, e[to].size());
		e.add_edge(to, from, 0, e[from].size()-1);
	}
	int size() {
		return sz;
	}
};#line 3 "test/aoj/../../graph/Dinic.cpp"
template<class F>
struct Dinic : public Graph<F> {
	const F FLOW_INF = numeric_limits<F>::max();
	vector<int> level;
	vector<int> iter;
	using Graph<F>::e;
// a:Vertex(|V|)
	Dinic(int n) : Graph<F>(n), level(n), iter(n) {}
	F dfs(int s, int t, F f) {
		if (s == t) return f;
		for (int& i = iter[s]; i < (int) e[s].size(); i++) {
			auto& x = e[s][i];
			if (x.cap == 0 || level[s] >= level[x.to]) continue;
			F d;
			if ((d = dfs(x.to, t, min(f, x.cap))) > 0) {
				x.cap -= d;
				e[x.to][x.rev].cap += d;
				return d;
			}
		}
		return 0;
	}
	void bfs(int s) {
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
			for (auto y : e[a]) {
				if (y.cap > 0) q.push(make_pair(y.to, b+1));
			}
		}
	}
	F solve(int s, int t) {
		F res = 0;
		while (true) {
			bfs(s);
			if (level[t] < 0) return res;
			fill(iter.begin(), iter.end(), 0);
			for (F r = 1; r;) {
				r = dfs(s, t, FLOW_INF);
				res += r;
			}
		}
	}
};
}
template<class F> using dinic = dinic_n::Dinic<F>;#line 8 "test/aoj/Dinic.test.cpp"

int main() {
	int n, m;
	cin >> n >> m;
	dinic<int> D(n);
	for (int i = 0; i < m; i++) {
		int u, v, c;
		cin >> u >> v >> c;
		D.add_edge(u, v, c);
	}
	cout << D.solve(0, n-1) << endl;
}
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

