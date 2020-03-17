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


# :heavy_check_mark: test/yosupo/HLD_path_sum.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#0b58406058f6619a0f31a172defc0230">test/yosupo</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yosupo/HLD_path_sum.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-18 00:23:49+09:00


* see: <a href="https://judge.yosupo.jp/problem/vertex_add_path_sum">https://judge.yosupo.jp/problem/vertex_add_path_sum</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/datastructure/HLD.cpp.html">datastructure/HLD.cpp</a>
* :heavy_check_mark: <a href="../../../library/datastructure/SegmentTree/SegmentTree.cpp.html">セグメント木</a>
* :heavy_check_mark: <a href="../../../library/monoid/plus_monoid.cpp.html">monoid/plus_monoid.cpp</a>
* :heavy_check_mark: <a href="../../../library/template/WeightedVertexGraph.cpp.html">template/WeightedVertexGraph.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"
#include<bits/stdc++.h>
using namespace std;

#include "../../datastructure/HLD.cpp"
#include "../../monoid/plus_monoid.cpp"

int main() {
	int N, Q; cin >> N >> Q;
	auto G = make_hld_graph<plus_monoid<long long>>(N);
	for (int i = 0; i < N; i++) {
		cin >> G[i];
	}
	for (int i = 1; i < N; i++) {
		int u, v; cin >> u >> v;
		G.add_edge(u, v);
		G.add_edge(v, u);
	}
	auto seg = G.make_segmenttree(0);
	for (int i = 0; i < Q; i++) {
		int q; cin >> q;
		if (q == 0) {
			int u, x; cin >> u >> x;
			seg.set(u, seg[u] + x);
		} else {
			int u, v; cin >> u >> v;
			cout << seg.path_sum(u, v) << endl;
		}
	}
	return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yosupo/HLD_path_sum.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"
#include<bits/stdc++.h>
using namespace std;

#line 1 "test/yosupo/../../datastructure/HLD.cpp"
namespace hld_n {
#line 1 "test/yosupo/../../datastructure/../template/WeightedVertexGraph.cpp"
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
using weighted_vertex_graph_n::WeightedVertexGraph;
using weighted_vertex_graph_n::make_weighted_vertex_graph;
#line 1 "test/yosupo/../../datastructure/../datastructure/SegmentTree/SegmentTree.cpp"
/**
 * @title セグメント木
 * @brief 0-indexed 半開区間
 * @brief クラス Node は Monoid であり、{型(monoid_type), 演算(operator+), 単位元(default constructor), constructor(monoid_type)} の4つを持つ。
 * @brief Node の具体例は monoid/ にある。
 */
namespace segmenttree_n {
template<class Node>
struct SegmentTree {
	using node_type = typename Node::monoid_type;
	using index_type = uint_fast32_t;
	index_type n;
	vector<Node> node;
	// @brief サイズ N で初期化(初期値は単位元) $O(N)$
	SegmentTree (index_type N) {build(N);}
	// @brief vector で初期化 $O(N)$
	SegmentTree (const vector<node_type>& v) {build(v);}
	// @brief サイズ N で再構築(初期値は単位元) $O(N)$
	void build(index_type N) {
		n = calc_n(N);
		node.clear(); node.resize(2*n-1);
	}
	// @brief vector で再構築 $O(N)$
	void build(const vector<node_type>& v) {
		build(index_type(v.size()));
		for (size_t i = 0; i < v.size(); i++) {
			node[i+n-1].val = v[i];
		}
		for (int i = n - 2; i >= 0; i--){
			node[i] = Node::merge(node[i*2+1], node[i*2+2]);
		}
	}
	// @brief index i に v を代入 $O(\log N)$
	void set(index_type i, Node v) {
		i += n - 1;
		node[i] = v;
		while (i) {
			i = (i-1) / 2;
			node[i] = Node::merge(node[i*2+1], node[i*2+2]);
		}
	}
	// @brief [l, r) を取得 $O(\log N)$
	node_type get(index_type l, index_type r) const {
		Node val_l, val_r;
		for (l += n-1, r += n-1; l < r; l /= 2, r = (r - 1) / 2) {
			if (l % 2 == 0) val_l = Node::merge(val_l, node[l]);
			if (r % 2 == 0) val_r = Node::merge(node[r-1], val_r);
		}
		return Node::merge(val_l, val_r).val;
	}
	// @brief index i を取得 $O(\log N)$
	const node_type& operator[](index_type i) const {
		return node[i+n-1].val;
	}
private:
	index_type calc_n(index_type n_, index_type t = 1) {return n_ > t ? calc_n(n_, t << 1) : t;}
};
} // namespace segmenttree_n
using segmenttree_n::SegmentTree;
#line 4 "test/yosupo/../../datastructure/HLD.cpp"
using u32 = uint_fast32_t;

template<class Node, class node_type = typename Node::monoid_type>
struct HLDSegmentTree {
	SegmentTree<Node> seg;
	const vector<u32> in;
	const vector<u32> out;
	const vector<u32> nxt;
	const vector<u32> par;
	const vector<u32>& id;
	HLDSegmentTree(vector<node_type>& v, vector<u32>& in, vector<u32>& out, vector<u32>& nxt, vector<u32>& par) : seg(v), in(in), out(out), nxt(nxt), par(par), id(in) {}
	node_type get(u32 l, u32 r) const {
		return seg.get(id[l], id[r]);
	}
	void set(u32 p, node_type v) {
		return seg.set(id[p], v);
	}
	const node_type& operator[](u32 i) const {
		return seg[id[i]];
	}
	node_type subtree_sum(u32 v) const {
		return seg.get(in[v], out[v]);
	}
	node_type path_sum(u32 u, u32 v) {
		Node res;
		for (;;) {
			if (id[u] > id[v]) swap(u, v);
			res = Node::merge(res, seg.get(max(id[nxt[v]], id[u]), id[v] + 1));
			if (nxt[u] == nxt[v]) break;
			v = par[nxt[v]];
		}
		return res.val;
	}
};

template<class Node, class node_type = typename Node::monoid_type>
struct HLDecomposition : WeightedVertexGraph<node_type> {
	using WeightedVertexGraph<node_type>::n;
	using WeightedVertexGraph<node_type>::e;
	using WeightedVertexGraph<node_type>::v;
	vector<u32> sz;
	vector<u32> in;
	vector<u32> out;
	vector<u32> nxt;
	vector<u32> par;
	vector<u32>& id;
	HLDecomposition(u32 N) : WeightedVertexGraph<node_type>(N), sz(N), in(N), out(N), nxt(N), par(N, N), id(in) {}
	HLDSegmentTree<Node> make_segmenttree(u32 root = 0) {
		dfs_sz(root, n);
		u32 t = 0;
		nxt[root] = root;
		dfs_hld(root, t, n);
		vector<node_type> res(n);
		for (u32 i = 0; i < n; i++) {
			res[id[i]] = v[i].val;
		}
		return HLDSegmentTree<Node>(res, in, out, nxt, par);
	}
	node_type& operator[](u32 i) {
		return v[i].val;
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
template<class Node>
HLDecomposition<Node> make_hld_graph(u32 N) {
	return HLDecomposition<Node>(N);
}
}
using hld_n::HLDecomposition;
using hld_n::make_hld_graph;
#line 1 "test/yosupo/../../monoid/plus_monoid.cpp"
namespace plus_monoid_n {
template<class T>
struct plus_monoid {
	using monoid_type = T;
	T val;
	plus_monoid(T v) : val(v) {}
	plus_monoid() : val(0) {}
	static plus_monoid merge(const plus_monoid& lhs, const plus_monoid& rhs) {
		return plus_monoid(lhs.val + rhs.val);
	}
};
}
using plus_monoid_n::plus_monoid;
#line 7 "test/yosupo/HLD_path_sum.test.cpp"

int main() {
	int N, Q; cin >> N >> Q;
	auto G = make_hld_graph<plus_monoid<long long>>(N);
	for (int i = 0; i < N; i++) {
		cin >> G[i];
	}
	for (int i = 1; i < N; i++) {
		int u, v; cin >> u >> v;
		G.add_edge(u, v);
		G.add_edge(v, u);
	}
	auto seg = G.make_segmenttree(0);
	for (int i = 0; i < Q; i++) {
		int q; cin >> q;
		if (q == 0) {
			int u, x; cin >> u >> x;
			seg.set(u, seg[u] + x);
		} else {
			int u, v; cin >> u >> v;
			cout << seg.path_sum(u, v) << endl;
		}
	}
	return 0;
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

