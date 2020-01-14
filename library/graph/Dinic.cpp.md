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


# :heavy_check_mark: graph/Dinic.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/Dinic.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-15 01:52:18+09:00




## Depends on

* :heavy_check_mark: <a href="../for_include/vec.cpp.html">for_include/vec.cpp</a>
* :heavy_check_mark: <a href="../snippet/FlowEdge.cpp.html">snippet/FlowEdge.cpp</a>
* :heavy_check_mark: <a href="../snippet/FlowGraph.cpp.html">snippet/FlowGraph.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/Dinic.test.cpp.html">test/aoj/Dinic.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
namespace dinic_n {
#include "../snippet/FlowGraph.cpp"
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
template<class F> using dinic = dinic_n::Dinic<F>;
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/Dinic.cpp"
namespace dinic_n {
#line 1 "graph/../snippet/FlowEdge.cpp"
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
#line 1 "graph/../snippet/../for_include/vec.cpp"
	using type::begin; using type::end; using type::rbegin; using type::rend;
	using type::cbegin; using type::cend; using type::crbegin; using type::crend;
	using type::size; using type::operator[]; using type::at; using type::back; using type::front;
	using type::reserve; using type::resize; using type::assign; using type::shrink_to_fit;
	using type::clear; using type::erase; using type::insert; using type::swap; 
	using type::push_back; using type::pop_back; using type::emplace_back; using type::empty;
	using typename vector<typename type::value_type, allocator<typename type::value_type>>::iterator;#line 16 "graph/../snippet/FlowEdge.cpp"
};#line 2 "graph/../snippet/FlowGraph.cpp"
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
};#line 3 "graph/Dinic.cpp"
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
template<class F> using dinic = dinic_n::Dinic<F>;
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

