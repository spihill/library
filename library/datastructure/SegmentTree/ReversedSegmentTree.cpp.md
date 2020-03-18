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


# :heavy_check_mark: datastructure/SegmentTree/ReversedSegmentTree.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#cbada5aa9c548d7605cff951f3e28eda">datastructure/SegmentTree</a>
* <a href="{{ site.github.repository_url }}/blob/master/datastructure/SegmentTree/ReversedSegmentTree.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-18 22:44:33+09:00




## Depends on

* :heavy_check_mark: <a href="SegmentTree.cpp.html">セグメント木</a>


## Required by

* :heavy_check_mark: <a href="../HLD.cpp.html">重軽分解(Heavy Light Decomposition)</a>


## Verified with

* :heavy_check_mark: <a href="../../../verify/test/yosupo/HLD_path_fold.test.cpp.html">test/yosupo/HLD_path_fold.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/test/yosupo/HLD_path_sum.test.cpp.html">test/yosupo/HLD_path_sum.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/test/yosupo/HLD_subtree_sum.test.cpp.html">test/yosupo/HLD_subtree_sum.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
namespace reversed_segmenttree_n {
#include "SegmentTree.cpp"
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
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "datastructure/SegmentTree/ReversedSegmentTree.cpp"
namespace reversed_segmenttree_n {
#line 1 "datastructure/SegmentTree/SegmentTree.cpp"
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
#line 3 "datastructure/SegmentTree/ReversedSegmentTree.cpp"
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

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

