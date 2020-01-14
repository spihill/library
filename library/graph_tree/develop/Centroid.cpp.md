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


# :warning: graph_tree/develop/Centroid.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#2ce58b44113eaf8f045cee2f9f04f29c">graph_tree/develop</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph_tree/develop/Centroid.cpp">View this file on GitHub</a>
    - Last commit date: 2019-09-15 23:24:33+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct Graph {
	struct Vertex{};
	struct Edge {
		int to;
		Edge(int t) : to(t) {}
		Edge() {}
	};
	int sz;
	vector<Vertex> v;
	vector<vector<Edge>> e;
	Graph(int n) : sz(n), v(n), e(n) {}
	template<class... Args>
	inline void assign_vertex(int pos, Args... args) {
		v[pos] = V(args...);
	}
	template<class... Args>
	inline void add_edge(int pos, Args... args) {
		e[pos].emplace_back(args...);
	}
	inline int size() {
		return sz;
	}
};
struct Centroid : public Graph {
	vector<bool> dead;
	vector<int> subsize;
	vector<int> par;
	vector<vector<edge>> child_par;
	vector<vector<edge>> par_child;
	Centroid(int n) : Graph(n), dead(sz, false), subsize(sz, sz), par(sz, -1), child_par(n), par_child(n) {}
	void centroid_dfs(int v, int chsize, vector<int>& res, int p = -1) {
		stack<int> s;
		stack<int> st;
		st.push(v);
		map<int, int> ok;
		par[v] = -1;
		while (!st.empty()) {
			auto t = st.top(); st.pop();
			subsize[t] = 1;
			s.push(t); 
			ok[t] = 1;
			for (auto& x: e[t]) {
				if (dead[x.to] || par[t] == x.to) continue;
				par[x.to] = t;
				st.push(x.to);
			}
		}
		while (!s.empty()) {
			auto t = s.top(); s.pop();
			if (par[t] != -1) {
				subsize[par[t]] += subsize[t];
				if (subsize[t] > chsize / 2) {
					ok[par[t]] = 0;
				}
			}
		}
		for (auto& o : ok) {
			if (o.second && (chsize + 1) / 2 <= subsize[o.first]) {
				res.push_back(o.first);
			}
		}
	}
	int centroid_build(int root = 0) {
		vector<int> next;
		int r = centroid_find(root, next);
		for (auto& x: next) {
			int t = centroid_build(x);
			par_child[r].emplace_back(t);
			child_par[t].emplace_back(r);
		}
		return r;
	}
	int centroid_find(int root, vector<int>& next_root) {
		vector<int> centroids;
		centroid_dfs(root, subsize[root], centroids);
		int centor = centroids[0];
		if (par[centor] >= 0) subsize[par[centor]] = subsize[root] - subsize[centor];
		dead[centor] = true;
		for (auto& x: e[centor]) {
			if (dead[x.to]) continue;
			next_root.emplace_back(x.to);
		}
		return centor;
	}
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph_tree/develop/Centroid.cpp"
struct Graph {
	struct Vertex{};
	struct Edge {
		int to;
		Edge(int t) : to(t) {}
		Edge() {}
	};
	int sz;
	vector<Vertex> v;
	vector<vector<Edge>> e;
	Graph(int n) : sz(n), v(n), e(n) {}
	template<class... Args>
	inline void assign_vertex(int pos, Args... args) {
		v[pos] = V(args...);
	}
	template<class... Args>
	inline void add_edge(int pos, Args... args) {
		e[pos].emplace_back(args...);
	}
	inline int size() {
		return sz;
	}
};
struct Centroid : public Graph {
	vector<bool> dead;
	vector<int> subsize;
	vector<int> par;
	vector<vector<edge>> child_par;
	vector<vector<edge>> par_child;
	Centroid(int n) : Graph(n), dead(sz, false), subsize(sz, sz), par(sz, -1), child_par(n), par_child(n) {}
	void centroid_dfs(int v, int chsize, vector<int>& res, int p = -1) {
		stack<int> s;
		stack<int> st;
		st.push(v);
		map<int, int> ok;
		par[v] = -1;
		while (!st.empty()) {
			auto t = st.top(); st.pop();
			subsize[t] = 1;
			s.push(t); 
			ok[t] = 1;
			for (auto& x: e[t]) {
				if (dead[x.to] || par[t] == x.to) continue;
				par[x.to] = t;
				st.push(x.to);
			}
		}
		while (!s.empty()) {
			auto t = s.top(); s.pop();
			if (par[t] != -1) {
				subsize[par[t]] += subsize[t];
				if (subsize[t] > chsize / 2) {
					ok[par[t]] = 0;
				}
			}
		}
		for (auto& o : ok) {
			if (o.second && (chsize + 1) / 2 <= subsize[o.first]) {
				res.push_back(o.first);
			}
		}
	}
	int centroid_build(int root = 0) {
		vector<int> next;
		int r = centroid_find(root, next);
		for (auto& x: next) {
			int t = centroid_build(x);
			par_child[r].emplace_back(t);
			child_par[t].emplace_back(r);
		}
		return r;
	}
	int centroid_find(int root, vector<int>& next_root) {
		vector<int> centroids;
		centroid_dfs(root, subsize[root], centroids);
		int centor = centroids[0];
		if (par[centor] >= 0) subsize[par[centor]] = subsize[root] - subsize[centor];
		dead[centor] = true;
		for (auto& x: e[centor]) {
			if (dead[x.to]) continue;
			next_root.emplace_back(x.to);
		}
		return centor;
	}
};
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

