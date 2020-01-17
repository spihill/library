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


# :heavy_check_mark: test/aoj/LazySegmentTree_RMQ_RAQ.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/LazySegmentTree_RMQ_RAQ.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-17 14:13:11+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_H">https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_H</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/datastructure/SegmentTree/LazySegmentTree.cpp.html">遅延伝播セグメント木</a>
* :heavy_check_mark: <a href="../../../library/monoid/min_monoid.cpp.html">monoid/min_monoid.cpp</a>
* :heavy_check_mark: <a href="../../../library/monoid/pair/min_plus_monoid.cpp.html">monoid/pair/min_plus_monoid.cpp</a>
* :heavy_check_mark: <a href="../../../library/monoid/plus_monoid.cpp.html">monoid/plus_monoid.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_H"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/SegmentTree/LazySegmentTree.cpp"
#include "../../monoid/pair/min_plus_monoid.cpp"
using ll = long long;
using monoids = min_plus_monoid<ll>;


int main() {
	int n, Q;
	cin >> n >> Q;
	LazySegmentTree<monoids> L;
	L.build(vector<ll>(n, 0));
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
#line 1 "test/aoj/LazySegmentTree_RMQ_RAQ.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_H"

#include<bits/stdc++.h>

using namespace std;

#line 1 "test/aoj/../../datastructure/SegmentTree/LazySegmentTree.cpp"
/**
 * @title 遅延伝播セグメント木
 * @brief MonoidPair はクラス Node と クラス Lazy を持つ。
 * @brief クラス Node と Lazy は Monoid であり、{型(monoid_type), 演算(operator+), 単位元(default constructor), constructor(monoid_type)} の4つを持つ。
 * @brief クラス Lazy は {operator*(int), is_unity()} も持つ。
 * @brief クラス Node は operator+(const Lazy&) も持つ。
 * @brief MonoidPair の具体例は monoid/pair/ にある。
 */
template<class MonoidPair>
struct LazySegmentTree {
	int n;
	using Node = typename MonoidPair::Node; using Node_T = typename MonoidPair::Node::monoid_type;
	using Lazy = typename MonoidPair::Lazy; using Lazy_T = typename MonoidPair::Lazy::monoid_type;
	vector<Node> node;
	vector<Lazy> lazy;
	// @brief サイズ N で初期化(初期値は単位元) $O(N)$
	LazySegmentTree (int N) {build(N);}
	// @brief vector で初期化 $O(N)$
	LazySegmentTree (const vector<Node_T>& v) {build(v);}
	// @brief 初期化しない
	LazySegmentTree () {}
	// @brief (a, b] に x を遅延伝播 $O(\log N)$
	void set(int a, int b, Lazy_T x) {set(a, b, x, 0, 0, n);}
	// @brief (a, b] を取得 $O(\log N)$
	Node_T get(int a, int b) {return get(a, b, 0, 0, n).val;}
	// @brief index i を取得 $O(\log N)$
	const Node_T& operator[](int i) {
		return get(i, i+1);
	}
	// @brief サイズ N で再構築(初期値は単位元) $O(N)$
	void build(int n_) {
		n = calc_n(n_);
		node.clear(); node.resize(2*n-1);
		lazy.clear(); lazy.resize(2*n-1);
	}
	// @brief vector で再構築 $O(N)$
	void build(const vector<Node_T>& v) {
		build(v.size());
		for (size_t i = 0; i < v.size(); i++) {
			node[i+n-1].val = v[i];
		}
		for (int i = n - 2; i >= 0; i--){
			node[i] = node[i*2+1] + node[i*2+2];
		}
	}
private:
	void eval(int len, int k) {
		if (lazy[k].is_unity()) return;
		if (2*k+1 < 2*n-1) {
			lazy[2*k+1] = lazy[2*k+1] + lazy[k];
			lazy[2*k+2] = lazy[2*k+2] + lazy[k];
		}
		node[k] = node[k] + lazy[k] * len;
		lazy[k] = Lazy();
	}
	Node set(int a, int b, Lazy_T x, int k, int l, int r) {
		eval(r-l, k);
		if (r <= a || b <= l) return node[k];
		if (a <= l && r <= b) {
			lazy[k] = lazy[k] + Lazy(x);
			return node[k] + lazy[k] * (r-l);
		}
		return node[k] = set(a, b, x, 2*k+1, l, (l+r) / 2) + set(a, b, x, 2*k+2, (l+r) / 2, r);
	}
	Node get(int a, int b, int k, int l, int r) {
		eval(r-l, k);
		if (a <= l && r <= b) {
			return node[k];
		} else if (b <= l || r <= a) {
			return Node();
		}
		return get(a, b, 2*k+1, l, (l+r) / 2) + get(a, b, 2*k+2, (l+r) / 2, r);
	}
	int calc_n(int n_, int t = 1) {return n_ > t ? calc_n(n_, t << 1) : t;}
};#line 1 "test/aoj/../../monoid/pair/../min_monoid.cpp"
template<class T>
struct min_monoid {
	using mono = min_monoid;
	min_monoid() : min_monoid(numeric_limits<T>::max()) {}
	explicit min_monoid(T x) : val(x) {}
	T val;
	mono operator+(const mono& rhs) const {
		return mono(min(val, rhs.val));
	}
	friend istream& operator>>(istream& lhs, mono& rhs) {
		lhs >> rhs.val;
		return lhs;
	}
	friend ostream& operator<<(ostream& lhs, mono& rhs) {
		lhs << rhs.val;
		return lhs;
	}
	using monoid_type = T;
};#line 1 "test/aoj/../../monoid/pair/../plus_monoid.cpp"
template<class T>
struct plus_monoid {
	using mono = plus_monoid;
	plus_monoid() : plus_monoid(T()) {}
	explicit plus_monoid(T x) : val(x) {}
	T val;
	mono operator+(const mono& rhs) const {
		return mono(val + rhs.val);
	}
	friend istream& operator>>(istream& lhs, mono& rhs) {
		lhs >> rhs.val;
		return lhs;
	}
	friend ostream& operator<<(ostream& lhs, mono& rhs) {
		lhs << rhs.val;
		return lhs;
	}
	using monoid_type = T;
};#line 3 "test/aoj/../../monoid/pair/min_plus_monoid.cpp"

template<class T, class U = T>
struct min_plus_monoid {
	template<class TT> using lazy_monoid = plus_monoid<TT>;
	template<class TT> using node_monoid = min_monoid<TT>;
	struct Lazy : public lazy_monoid<U> {
		using lazy_monoid<U>::lazy_monoid;
		using lazy_monoid<U>::operator+;
		using lazy_monoid<U>::operator=;
		Lazy(lazy_monoid<U> x) : lazy_monoid<U>(x) {}
		inline Lazy operator*(int len) const {
			return Lazy(this->val);
		}
		inline bool is_unity() const {
			return this->val == T();
		}
	};
	struct Node : public node_monoid<T> {
		using node_monoid<T>::node_monoid;
		using node_monoid<T>::operator+;
		using node_monoid<T>::operator=;
		Node(node_monoid<T> x) : node_monoid<T>(x) {}
		inline Node operator+(const Lazy& rhs) const {
			return Node(this->val + rhs.val);
		}
	};
};#line 9 "test/aoj/LazySegmentTree_RMQ_RAQ.test.cpp"
using ll = long long;
using monoids = min_plus_monoid<ll>;


int main() {
	int n, Q;
	cin >> n >> Q;
	LazySegmentTree<monoids> L;
	L.build(vector<ll>(n, 0));
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

