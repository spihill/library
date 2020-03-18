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


# :heavy_check_mark: test/yosupo/HLD_path_fold.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#0b58406058f6619a0f31a172defc0230">test/yosupo</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yosupo/HLD_path_fold.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-18 22:57:25+09:00


* see: <a href="https://judge.yosupo.jp/problem/vertex_set_path_composite">https://judge.yosupo.jp/problem/vertex_set_path_composite</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/datastructure/HLD.cpp.html">重軽分解(Heavy Light Decomposition)</a>
* :heavy_check_mark: <a href="../../../library/datastructure/SegmentTree/ReversedSegmentTree.cpp.html">datastructure/SegmentTree/ReversedSegmentTree.cpp</a>
* :heavy_check_mark: <a href="../../../library/datastructure/SegmentTree/SegmentTree.cpp.html">セグメント木</a>
* :heavy_check_mark: <a href="../../../library/math/ModInt.cpp.html">ModInt</a>
* :heavy_check_mark: <a href="../../../library/monoid/affine_monoid.cpp.html">monoid/affine_monoid.cpp</a>
* :heavy_check_mark: <a href="../../../library/template/WeightedVertexGraph.cpp.html">template/WeightedVertexGraph.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/vertex_set_path_composite"
#include<bits/stdc++.h>
using namespace std;

#include "../../datastructure/HLD.cpp"
#include "../../monoid/affine_monoid.cpp"
#include "../../math/ModInt.cpp"
using modint = ModInt<998244353>;

int main() {
	int N, Q; cin >> N >> Q;
	auto G = make_hld_graph<affine_monoid<modint>>(N);
	for (int i = 0; i < N; i++) {
		cin >> G[i].first >> G[i].second;
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
			int p, c, d; cin >> p >> c >> d;
			seg.set(p, {c, d});
		} else {
			int u, v, x; cin >> u >> v >> x;
			auto r = seg.path_fold(u, v);
			cout << r.first * x + r.second << endl;
		}
	}
	return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yosupo/HLD_path_fold.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/vertex_set_path_composite"
#include<bits/stdc++.h>
using namespace std;

#line 1 "test/yosupo/../../datastructure/HLD.cpp"
/**
 * @title 重軽分解(Heavy Light Decomposition)
 * @brief Segment Tree を重軽分解に乗せる。パスや部分木上の合計を求めるが、非可換の演算に対応していない。
 */
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
#line 1 "test/yosupo/../../datastructure/../datastructure/SegmentTree/ReversedSegmentTree.cpp"
namespace reversed_segmenttree_n {
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
#line 3 "test/yosupo/../../datastructure/../datastructure/SegmentTree/ReversedSegmentTree.cpp"
template<class Node>
struct ReversedSegmentTree {
	using node_type = typename Node::monoid_type;
	using u32 = uint_fast32_t;
	SegmentTree<Node> seg;
	u32 sz;
	ReversedSegmentTree(vector<node_type>& v) : seg(vector<node_type>(v.rbegin(), v.rend())), sz(v.size()) {}
	void set(u32 i, Node v) {
		seg.set(sz - i - 1, v);
	}
	node_type get(u32 l, u32 r) const {
		assert(l <= r);
		return seg.get(sz - r, sz - l);
	}
	const node_type& operator[](u32 i) const {
		return seg[sz - i - 1];
	}
};
}
using reversed_segmenttree_n::ReversedSegmentTree;
#line 9 "test/yosupo/../../datastructure/HLD.cpp"
using u32 = uint_fast32_t;
template<class Node, class node_type = typename Node::monoid_type>
struct HLDSegmentTree {
	SegmentTree<Node> seg;
	ReversedSegmentTree<Node> rev_seg;
	const vector<u32> in;
	const vector<u32> out;
	const vector<u32> nxt;
	const vector<u32> par;
	const vector<u32>& id;
	HLDSegmentTree(vector<node_type>& v, vector<u32>& in, vector<u32>& out, vector<u32>& nxt, vector<u32>& par) : seg(v), rev_seg(v), in(in), out(out), nxt(nxt), par(par), id(in) {}
	// @brief 頂点 v に x を代入 O(\log N)$
	void set(u32 v, node_type x) {
		seg.set(id[v], x);
		rev_seg.set(id[v], x);
	}
	// @brief 頂点 v の値 O(1))$
	const node_type& operator[](u32 v) const {
		return seg[id[v]];
	}
	// @brief 頂点 v の部分木の合計 $O(\log N))$
	node_type subtree_sum(u32 v) const {
		return seg.get(in[v], out[v]);
	}
	// @brief u ～ v のパスの合計(可換演算のみ) $O((\log N))^2)$
	node_type path_sum(u32 u, u32 v) const {
		Node res;
		for (;;) {
			if (id[u] > id[v]) swap(u, v);
			res = Node::merge(res, seg.get(max(id[nxt[v]], id[u]), id[v] + 1));
			if (nxt[u] == nxt[v]) break;
			v = par[nxt[v]];
		}
		return res.val;
	}
	// @brief u ～ v のパスの合計 $O((\log N))^2)$
	node_type path_fold(u32 u, u32 v) const {
		Node l, r;
		for (;;) {
			if (id[u] < id[v]) {
				r = Node::merge(seg.get(max(id[nxt[v]], id[u]), id[v] + 1), r);
				if (nxt[u] == nxt[v]) break;
				v = par[nxt[v]];
			} else {
				l = Node::merge(l, rev_seg.get(max(id[nxt[u]], id[v]), id[u] + 1));
				if (nxt[u] == nxt[v]) break;
				u = par[nxt[u]];
			}
		}
		return Node::merge(l, r).val;
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
	// 木の根を root として重軽分解して Segment Tree を返す。
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
// @brief 型 Node はモノイドクラス
template<class Node> HLDecomposition<Node> make_hld_graph(u32 N) {
	return HLDecomposition<Node>(N);
}
}
using hld_n::HLDecomposition;
using hld_n::make_hld_graph;
#line 1 "test/yosupo/../../monoid/affine_monoid.cpp"
namespace affine_monoid_n {
template<class T>
struct affine_monoid {
	using monoid_type = pair<T, T>;
	pair<T, T> val;
	affine_monoid() : affine_monoid(pair<T, T>(1, 0)) {}
	affine_monoid(pair<T, T> v) : val(v) {}
	affine_monoid(T f, T s) : val(f, s) {}
	static affine_monoid merge(const affine_monoid& lhs, const affine_monoid& rhs) {
		return affine_monoid(pair<T, T>(rhs.val.first * lhs.val.first, rhs.val.first * lhs.val.second + rhs.val.second));
	}
};
}
using affine_monoid_n::affine_monoid;
#line 1 "test/yosupo/../../math/ModInt.cpp"
/**
 * @title ModInt
 * @brief mod を取りながら計算する。リテラル型の要件を満たし、constexprに対応している。
 * @brief これでも Verify してます。 https://github.com/spihill/library/blob/master/test/mytest/ModInt.test.cpp
 */
namespace modint_n {
using value_type = signed;
template<value_type mod>
struct ModInt {
	using i64 = int_fast64_t;
	value_type x;
	constexpr static value_type get_mod() {
		return mod;
	}
	constexpr ModInt(i64 x_) : x(mod_(x_)) {}
	constexpr ModInt() : ModInt(0) {}
	~ModInt() = default;
	inline constexpr ModInt& operator+=(const ModInt rhs) {
		i64 t = static_cast<i64>(x) + rhs.x;
		if (t >= mod) x = t - mod;
		else x = t;
		return (*this);
	}
	inline constexpr ModInt& operator-=(const ModInt rhs) {
		i64 t = static_cast<i64>(x) + mod - rhs.x;
		if (t >= mod) x = t - mod;
		else x = t;
		return *this;
	}
	inline constexpr ModInt& operator*=(const ModInt rhs) {
		x = static_cast<i64>(x) * rhs.x % mod;
		return *this;
	}
	inline constexpr ModInt& operator/=(ModInt rhs) {
		return *this *= rhs.inv();
	}
	inline constexpr ModInt power(i64 p) const {
		ModInt res = 1;
		ModInt a = x;
		for (; p; res = p & 1 ? res * a : res, a *= a, p >>= 1);
		return res;
	}
	inline constexpr ModInt inv() const {
		value_type z = 0, w = 0;
		extgcd(mod, x, z, w);
		return ModInt(w);
	}
	inline constexpr ModInt& operator=(const ModInt& rhs) {
		this->x = rhs.x;
		return *this;
	}
	inline constexpr value_type operator==(const ModInt& rhs) const {
		return this->x == rhs.x;
	}
	inline constexpr value_type operator!=(const ModInt& rhs) const {
		return !(*this == rhs);
	}
	inline constexpr ModInt operator++(signed unused) {
		ModInt res(*this);
		++(*this);
		return res;
	}
	inline constexpr ModInt& operator++() {
		(*this) += 1;
		return (*this);
	}
	inline constexpr ModInt operator--(signed unused) {
		ModInt res(*this);
		--(*this);
		return res;
	}
	inline constexpr ModInt& operator--() {
		(*this) -= 1;
		return (*this);
	}
	inline constexpr ModInt operator+() const {
		return (*this);
	}
	inline constexpr ModInt operator-() const {
		return (*this).x ? ModInt(mod - (*this).x) : ModInt(0);
	}
	friend constexpr ModInt operator+(const ModInt& lhs, const ModInt& rhs) {return ModInt(lhs) += rhs;}
	friend constexpr ModInt operator-(const ModInt& lhs, const ModInt& rhs) {return ModInt(lhs) -= rhs;}
	friend constexpr ModInt operator*(const ModInt& lhs, const ModInt& rhs) {return ModInt(lhs) *= rhs;}
	friend constexpr ModInt operator/(const ModInt& lhs, const ModInt& rhs) {return ModInt(lhs) /= rhs;}
	explicit constexpr operator value_type() const {return x;}
	friend ostream& operator<<(ostream& lhs, const ModInt& rhs) {
		lhs << rhs.x;
		return lhs;
	}
	friend istream& operator>>(istream& lhs, ModInt& rhs) {
		i64 t;
		lhs >> t;
		rhs = ModInt(t);
		return lhs;
	}
private:
	constexpr value_type extgcd(value_type a, value_type b, value_type& x, value_type& y) const {
		value_type d = a;
		if (b == 0) {
			x = 1;
			y = 0;
		} else {
			d = extgcd(b, a%b, y, x);
			y -= a / b * x;
		}
		return d;
	}
	constexpr value_type mod_(i64 x) {
		x %= mod; if (x < 0) x += mod;
		return static_cast<value_type>(x);
	}
};
}; // modint_n
using modint_n::ModInt;
namespace std {
template<modint_n::value_type N> struct is_integral<ModInt<N>> {
	static constexpr integral_constant<bool, true> value = integral_constant<bool, true>();
};
template<modint_n::value_type N> struct is_arithmetic<ModInt<N>> {
	static constexpr integral_constant<bool, true> value = integral_constant<bool, true>();
};
template<modint_n::value_type N> struct is_scalar<ModInt<N>> {
	static constexpr integral_constant<bool, true> value = integral_constant<bool, true>();
};
template<modint_n::value_type N> struct is_floating_point<ModInt<N>> {
	static constexpr integral_constant<bool, false> value = integral_constant<bool, false>();
};
template<modint_n::value_type N> struct is_signed<ModInt<N>> {
	static constexpr integral_constant<bool, false> value = integral_constant<bool, false>();
};
template<modint_n::value_type N> struct is_unsigned<ModInt<N>> {
	static constexpr integral_constant<bool, true> value = integral_constant<bool, true>();
};
} // namespace std
//using modint = ModInt<1000000007>;
//using modint = ModInt<998244353>;
#line 8 "test/yosupo/HLD_path_fold.test.cpp"
using modint = ModInt<998244353>;

int main() {
	int N, Q; cin >> N >> Q;
	auto G = make_hld_graph<affine_monoid<modint>>(N);
	for (int i = 0; i < N; i++) {
		cin >> G[i].first >> G[i].second;
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
			int p, c, d; cin >> p >> c >> d;
			seg.set(p, {c, d});
		} else {
			int u, v, x; cin >> u >> v >> x;
			auto r = seg.path_fold(u, v);
			cout << r.first * x + r.second << endl;
		}
	}
	return 0;
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

