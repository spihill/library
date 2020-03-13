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


# :heavy_check_mark: test/aoj/LazySegmentTree_RMQ_RUQ.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#0d0c91c0cca30af9c1c9faef0cf04aa9">test/aoj</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/LazySegmentTree_RMQ_RUQ.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-13 21:59:38+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_F">https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_F</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/datastructure/SegmentTree/LazySegmentTree.cpp.html">遅延伝播セグメント木</a>
* :heavy_check_mark: <a href="../../../library/monoid/min_monoid.cpp.html">monoid/min_monoid.cpp</a>
* :heavy_check_mark: <a href="../../../library/monoid/pair/min_update_monoid.cpp.html">monoid/pair/min_update_monoid.cpp</a>
* :heavy_check_mark: <a href="../../../library/monoid/update_monoid.cpp.html">monoid/update_monoid.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_F"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/SegmentTree/LazySegmentTree.cpp"
#include "../../monoid/pair/min_update_monoid.cpp"
using monoids = min_update_monoid<int>;


int main() {
	int n, Q;
	cin >> n >> Q;
	LazySegmentTree<monoids> L(n);
	while (Q--) {
		int q;
		cin >> q;
		if (q == 0) {
			int s, t, x; cin >> s >> t >> x;
			L.set(s, t+1, x);
		} else {
			int s, t; cin >> s >> t;
			cout << L.get(s, t+1) << endl;
		}
	}
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj/LazySegmentTree_RMQ_RUQ.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_F"

#include<bits/stdc++.h>

using namespace std;

#line 1 "test/aoj/../../datastructure/SegmentTree/LazySegmentTree.cpp"
/**
 * @title 遅延伝播セグメント木
 * @brief 0-indexed 半開区間
 * @brief MonoidPair はクラス Node と クラス Lazy を持つ。
 * @brief クラス Node と Lazy は Monoid であり、{型(monoid_type), 演算(merge), 単位元(default constructor), constructor(monoid_type)} の4つを持つ。
 * @brief MonoidPair の具体例は monoid/pair/ にある。
 */
template<class MonoidPair>
struct LazySegmentTree {
	int n;
	using Node = typename MonoidPair::Node; using node_type = typename MonoidPair::Node::monoid_type;
	using Lazy = typename MonoidPair::Lazy; using lazy_type = typename MonoidPair::Lazy::monoid_type;
	vector<Node> node;
	vector<Lazy> lazy;
	// @brief サイズ N で初期化(初期値は単位元) $O(N)$
	LazySegmentTree (int N) {build(N);}
	// @brief vector で初期化 $O(N)$
	LazySegmentTree (const vector<node_type>& v) {build(v);}
	LazySegmentTree () {}
	// @brief (a, b] に x を遅延伝播 $O(\log N)$
	void set(int a, int b, Lazy x) {set(a, b, x, 0, 0, n);}
	// @brief (a, b] を取得 $O(\log N)$
	node_type get(int a, int b) {return get(a, b, 0, 0, n).val;}
	// @brief index i を取得 $O(\log N)$
	node_type operator[](int i) {
		return get(i, i+1);
	}
	// @brief サイズ N で再構築(初期値は単位元) $O(N)$
	void build(int n_) {
		n = calc_n(n_);
		node.clear(); node.resize(2*n-1);
		lazy.clear(); lazy.resize(2*n-1);
	}
	// @brief vector で再構築 $O(N)$
	void build(const vector<node_type>& v) {
		build(v.size());
		for (size_t i = 0; i < v.size(); i++) {
			node[i+n-1].val = v[i];
		}
		for (int i = n - 2; i >= 0; i--){
			node[i] = Node::merge(node[i*2+1], node[i*2+2]);
		}
	}
private:
	void eval(int len, int k) {
		if (2*k+1 < 2*n-1) {
			lazy[2*k+1] = Lazy::merge(lazy[2*k+1], lazy[k]);
			lazy[2*k+2] = Lazy::merge(lazy[2*k+2], lazy[k]);
		}
		node[k] = MonoidPair::apply(node[k], MonoidPair::propagate(lazy[k], len));
		lazy[k] = Lazy();
	}
	Node set(int a, int b, const Lazy& x, int k, int l, int r) {
		eval(r-l, k);
		if (r <= a || b <= l) return node[k];
		if (a <= l && r <= b) {
			lazy[k] = Lazy::merge(lazy[k], x);
			return MonoidPair::apply(node[k], MonoidPair::propagate(lazy[k], r - l));
		}
		return node[k] = Node::merge(set(a, b, x, 2*k+1, l, (l+r) / 2), set(a, b, x, 2*k+2, (l+r) / 2, r));
	}
	Node get(int a, int b, int k, int l, int r) {
		eval(r-l, k);
		if (a <= l && r <= b) {
			return node[k];
		} else if (b <= l || r <= a) {
			return Node();
		}
		return Node::merge(get(a, b, 2*k+1, l, (l+r) / 2), get(a, b, 2*k+2, (l+r) / 2, r));
	}
	int calc_n(int n_, int t = 1) {return n_ > t ? calc_n(n_, t << 1) : t;}
};
#line 1 "test/aoj/../../monoid/pair/min_update_monoid.cpp"
namespace min_update_monoid_n {
#line 1 "test/aoj/../../monoid/pair/../min_monoid.cpp"
namespace min_monoid_n {
template<class T>
struct min_monoid {
	using monoid_type = T;
	T val;
	min_monoid(T v) : val(v) {}
	min_monoid() : val(numeric_limits<T>::max()) {}
	static min_monoid merge(const min_monoid& lhs, const min_monoid& rhs) {
		return min_monoid(min(lhs.val, rhs.val));
	}
};
}
using min_monoid_n::min_monoid;
#line 1 "test/aoj/../../monoid/pair/../update_monoid.cpp"
namespace update_monoid_n {
template<class T>
struct update_monoid {
	using monoid_type = pair<T, char>;
	pair<T, char> val;
	update_monoid(T v) : val(v, 0) {}
	update_monoid(pair<T, char> v) : val(v) {}
	update_monoid() : val(T(), 1) {}
	static update_monoid merge(const update_monoid& lhs, const update_monoid& rhs) {
		if (rhs.val.second) return lhs;
		return rhs;
	}
};
}
using update_monoid_n::update_monoid;
#line 4 "test/aoj/../../monoid/pair/min_update_monoid.cpp"
template<class T, class U = T, class NODE = min_monoid<T>, class LAZY = update_monoid<U>>
struct min_update_monoid {
	using Node = NODE;
	using Lazy = LAZY;
	static Node apply(const Node& lhs, const LAZY& rhs) {
		if (rhs.val.second) return lhs;
		return Node(rhs.val.first);
	}
	static Lazy propagate(const Lazy& lhs, int len) {
		return lhs;
	}
};
} // namespace min_update_monoid
using min_update_monoid_n::min_update_monoid;
#line 9 "test/aoj/LazySegmentTree_RMQ_RUQ.test.cpp"
using monoids = min_update_monoid<int>;


int main() {
	int n, Q;
	cin >> n >> Q;
	LazySegmentTree<monoids> L(n);
	while (Q--) {
		int q;
		cin >> q;
		if (q == 0) {
			int s, t, x; cin >> s >> t >> x;
			L.set(s, t+1, x);
		} else {
			int s, t; cin >> s >> t;
			cout << L.get(s, t+1) << endl;
		}
	}
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

