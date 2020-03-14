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


# :heavy_check_mark: datastructure/HLD.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#8dc87745f885a4cc532acd7b15b8b5fe">datastructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/datastructure/HLD.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-14 20:34:03+09:00




## Depends on

* :heavy_check_mark: <a href="../template/WeightedVertexGraph.cpp.html">template/WeightedVertexGraph.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/yosupo/HLD_path_sum.test.cpp.html">test/yosupo/HLD_path_sum.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yosupo/HLD_subtree_sum.test.cpp.html">test/yosupo/HLD_subtree_sum.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
namespace hld_n {
#include "../template/WeightedVertexGraph.cpp"
using weighted_vertex_graph_n::WeightedVertexGraph;
using weighted_vertex_graph_n::make_weighted_vertex_graph;
using u32 = uint_fast32_t;
template<class T>
struct HLDecomposition : WeightedVertexGraph<T> {
	using WeightedVertexGraph<T>::n;
	using WeightedVertexGraph<T>::e;
	using WeightedVertexGraph<T>::v;
	vector<u32> sz;
	vector<u32> in;
	vector<u32> out;
	vector<u32> nxt;
	vector<u32> par;
	vector<u32>& id;
	HLDecomposition(u32 N) : WeightedVertexGraph<T>(N), sz(N), in(N), out(N), nxt(N), par(N, N), id(in) {}
	vector<T> build(u32 root = 0) {
		dfs_sz(root, n);
		u32 t = 0;
		nxt[root] = root;
		dfs_hld(root, t, n);
		vector<T> res(n);
		for (u32 i = 0; i < n; i++) {
			res[id[i]] = v[i].val;
		}
		return res;
	}
	pair<u32, u32> subtree(u32 v) {
		return {in[v], out[v]};
	}
	vector<pair<u32, u32>> path(u32 u, u32 v) {
		vector<pair<u32, u32>> res;
		for (;;) {
			if (id[u] > id[v]) swap(u, v);
			res.emplace_back(max(id[nxt[v]], id[u]), id[v] + 1);
			if (nxt[u] == nxt[v]) break;
			v = par[nxt[v]];
		}
		reverse(res.begin(), res.end());
		return res;
	}
private:
	void dfs_sz(u32 root, u32 p) {
		sz[root] = 1;
		for (auto& u: e[root]) {
			if (u.to == p) continue;
			par[u.to] = root;
			dfs_sz(u.to, root);
			sz[root] += sz[u.to];
			if (sz[u.to] > sz[e[root][0].to]) {
				swap(u.to, e[root][0].to);
			}
		}
	}
	void dfs_hld(u32 root, u32& t, u32 p) {
		in[root] = t++;
		for (auto& u: e[root]) {
			if (u.to == p) continue;
			nxt[u.to] = (u.to == e[root][0].to ? nxt[root] : u.to);
			dfs_hld(u.to, t, root);
		}
		out[root] = t;
	}
};
template<class T = long long>
HLDecomposition<T> make_hld_graph(u32 N) {
	return HLDecomposition<T>(N);
}
}
using hld_n::HLDecomposition;
using hld_n::make_hld_graph;
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "datastructure/HLD.cpp"
namespace hld_n {
#line 1 "datastructure/../template/WeightedVertexGraph.cpp"
namespace weighted_vertex_graph_n {
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
using u32 = uint_fast32_t;
template<class T>
struct Vertex {
	T val;
};
struct Edge {
	u32 to;
	Edge(u32 x) : to(x) {}
};
template<class T> using WeightedVertexGraph = Graph<Edge, Vertex<T>>;

template<class T>
WeightedVertexGraph<T> make_weighted_vertex_graph(u32 N) {
	return WeightedVertexGraph<T>(N);
}
}
#line 3 "datastructure/HLD.cpp"
using weighted_vertex_graph_n::WeightedVertexGraph;
using weighted_vertex_graph_n::make_weighted_vertex_graph;
using u32 = uint_fast32_t;
template<class T>
struct HLDecomposition : WeightedVertexGraph<T> {
	using WeightedVertexGraph<T>::n;
	using WeightedVertexGraph<T>::e;
	using WeightedVertexGraph<T>::v;
	vector<u32> sz;
	vector<u32> in;
	vector<u32> out;
	vector<u32> nxt;
	vector<u32> par;
	vector<u32>& id;
	HLDecomposition(u32 N) : WeightedVertexGraph<T>(N), sz(N), in(N), out(N), nxt(N), par(N, N), id(in) {}
	vector<T> build(u32 root = 0) {
		dfs_sz(root, n);
		u32 t = 0;
		nxt[root] = root;
		dfs_hld(root, t, n);
		vector<T> res(n);
		for (u32 i = 0; i < n; i++) {
			res[id[i]] = v[i].val;
		}
		return res;
	}
	pair<u32, u32> subtree(u32 v) {
		return {in[v], out[v]};
	}
	vector<pair<u32, u32>> path(u32 u, u32 v) {
		vector<pair<u32, u32>> res;
		for (;;) {
			if (id[u] > id[v]) swap(u, v);
			res.emplace_back(max(id[nxt[v]], id[u]), id[v] + 1);
			if (nxt[u] == nxt[v]) break;
			v = par[nxt[v]];
		}
		reverse(res.begin(), res.end());
		return res;
	}
private:
	void dfs_sz(u32 root, u32 p) {
		sz[root] = 1;
		for (auto& u: e[root]) {
			if (u.to == p) continue;
			par[u.to] = root;
			dfs_sz(u.to, root);
			sz[root] += sz[u.to];
			if (sz[u.to] > sz[e[root][0].to]) {
				swap(u.to, e[root][0].to);
			}
		}
	}
	void dfs_hld(u32 root, u32& t, u32 p) {
		in[root] = t++;
		for (auto& u: e[root]) {
			if (u.to == p) continue;
			nxt[u.to] = (u.to == e[root][0].to ? nxt[root] : u.to);
			dfs_hld(u.to, t, root);
		}
		out[root] = t;
	}
};
template<class T = long long>
HLDecomposition<T> make_hld_graph(u32 N) {
	return HLDecomposition<T>(N);
}
}
using hld_n::HLDecomposition;
using hld_n::make_hld_graph;

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

