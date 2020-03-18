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


# :heavy_check_mark: test/aoj/SegmentTree_RMQ_4.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#0d0c91c0cca30af9c1c9faef0cf04aa9">test/aoj</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/SegmentTree_RMQ_4.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-18 00:23:49+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A">https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/datastructure/SegmentTree/RMQ.cpp.html">datastructure/SegmentTree/RMQ.cpp</a>
* :heavy_check_mark: <a href="../../../library/datastructure/SegmentTree/SegmentTree.cpp.html">セグメント木</a>
* :heavy_check_mark: <a href="../../../library/monoid/max_monoid.cpp.html">monoid/max_monoid.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/SegmentTree/RMQ.cpp"

int main() {
	int n, Q;
	cin >> n >> Q;
	vector<long long> v(n, LLONG_MIN);
	RMQ<long long> S(n);
	while (Q--) {
		long long q, x, y;
		cin >> q >> x >> y;
		if (q == 0) {
			S.set(x, -y);
			v[x] = -y;
		} else {
			long long r = S.get(x, y+1);
			if (r == LLONG_MIN) r = -(long long) INT_MAX;
			cout << -r << endl;
		}
	}
	RMQ<long long> T(v);
	assert(T.n == S.n);
	assert(T.node.size() == T.n*2-1);
	assert(S.node.size() == S.n*2-1);
	for (int i = 0; i < 2*n-1; i++) {
		assert(S.node[i].val == T.node[i].val);
	}
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj/SegmentTree_RMQ_4.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A"

#include<bits/stdc++.h>

using namespace std;

#line 1 "test/aoj/../../datastructure/SegmentTree/RMQ.cpp"
namespace RMQ_n {
#line 1 "test/aoj/../../datastructure/SegmentTree/SegmentTree.cpp"
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
#line 1 "test/aoj/../../datastructure/SegmentTree/../../monoid/max_monoid.cpp"
namespace max_monoid_n {
template<class T>
struct max_monoid {
	using monoid_type = T;
	T val;
	max_monoid(T v) : val(v) {}
	max_monoid() : val(numeric_limits<T>::min()) {}
	static max_monoid merge(const max_monoid& lhs, const max_monoid& rhs) {
		return max_monoid(max(lhs.val, rhs.val));
	}
};
}
using max_monoid_n::max_monoid;
#line 4 "test/aoj/../../datastructure/SegmentTree/RMQ.cpp"
template<class T> using RMQ = SegmentTree<max_monoid<T>>;
}
using RMQ_n::RMQ;
#line 8 "test/aoj/SegmentTree_RMQ_4.test.cpp"

int main() {
	int n, Q;
	cin >> n >> Q;
	vector<long long> v(n, LLONG_MIN);
	RMQ<long long> S(n);
	while (Q--) {
		long long q, x, y;
		cin >> q >> x >> y;
		if (q == 0) {
			S.set(x, -y);
			v[x] = -y;
		} else {
			long long r = S.get(x, y+1);
			if (r == LLONG_MIN) r = -(long long) INT_MAX;
			cout << -r << endl;
		}
	}
	RMQ<long long> T(v);
	assert(T.n == S.n);
	assert(T.node.size() == T.n*2-1);
	assert(S.node.size() == S.n*2-1);
	for (int i = 0; i < 2*n-1; i++) {
		assert(S.node[i].val == T.node[i].val);
	}
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>
