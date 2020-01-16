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


# :heavy_check_mark: test/aoj/LazySegmentTree_RSQ_RAQ.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/LazySegmentTree_RSQ_RAQ.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-16 18:41:18+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_G&lang=ja">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_G&lang=ja</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/datastructure/SegmentTree/LazySegmentTree.cpp.html">datastructure/SegmentTree/LazySegmentTree.cpp</a>
* :heavy_check_mark: <a href="../../../library/monoid/pair/plus_plus.cpp.html">monoid/pair/plus_plus.cpp</a>
* :heavy_check_mark: <a href="../../../library/monoid/plus.cpp.html">monoid/plus.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_G&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/SegmentTree/LazySegmentTree.cpp"
#include "../../monoid/pair/plus_plus.cpp"
using monoids = plus_plus_monoid<long long>;


int main() {
	int n, Q;
	cin >> n >> Q;
	LazySegmentTree<monoids> L(n);
	while (Q--) {
		int q;
		cin >> q;
		if (q == 0) {
			int s, t, x; cin >> s >> t >> x; s--; t--;
			L.set(s, t+1, x);
		} else {
			int s, t; cin >> s >> t; s--; t--;
			cout << L.get(s, t+1) << endl;
		}
	}
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj/LazySegmentTree_RSQ_RAQ.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_G&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#line 1 "test/aoj/../../datastructure/SegmentTree/LazySegmentTree.cpp"
template<class MonoidPair>
struct LazySegmentTree {
	int n;
	using Monoid = typename MonoidPair::Monoid; using Monoid_T = typename MonoidPair::Monoid::monoid_type;
	using Lazy = typename MonoidPair::Lazy; using Lazy_T = typename MonoidPair::Lazy::monoid_type;
	vector<Monoid> node;
	vector<Lazy> lazy;
	LazySegmentTree (int n_) {build(n_);}
	LazySegmentTree (const vector<Monoid_T>& v) {build(v);}
	LazySegmentTree () {}
	void build(int n_) {
		n = calc_n(n_);
		node.clear(); node.resize(2*n-1);
		lazy.clear(); lazy.resize(2*n-1);
	}
	void build(const vector<Monoid_T>& v) {
		build(v.size());
		for (size_t i = 0; i < v.size(); i++) {
			node[i+n-1].val = v[i];
		}
		for (int i = n - 2; i >= 0; i--){
			node[i] = node[i*2+1] + node[i*2+2];
		}
	}
	void eval(int len, int k) {
		if (lazy[k].is_unity()) return;
		if (2*k+1 < 2*n-1) {
			lazy[2*k+1] = lazy[2*k+1] + lazy[k];
			lazy[2*k+2] = lazy[2*k+2] + lazy[k];
		}
		node[k] = node[k] + lazy[k] * len;
		lazy[k] = Lazy();
	}
	Monoid set(int a, int b, Lazy_T x, int k, int l, int r) {
		eval(r-l, k);
		if (r <= a || b <= l) return node[k];
		if (a <= l && r <= b) {
			lazy[k] = lazy[k] + Lazy(x);
			return node[k] + lazy[k] * (r-l);
		}
		return node[k] = Monoid(set(a, b, x, 2*k+1, l, (l+r) / 2) + set(a, b, x, 2*k+2, (l+r) / 2, r));
	}
	void set(int a, int b, Lazy_T x) {set(a, b, x, 0, 0, n);}
	Monoid get(int a, int b, int k, int l, int r) {
		eval(r-l, k);
		if (a <= l && r <= b) {
			return node[k];
		} else if (b <= l || r <= a) {
			return Monoid();
		}
		return get(a, b, 2*k+1, l, (l+r) / 2) + get(a, b, 2*k+2, (l+r) / 2, r);
	}
	Monoid_T get(int a, int b) {return get(a, b, 0, 0, n).val;}
	const Monoid_T& operator[](int i) {
		return node[i+n-1].val;
	}
	int calc_n(int n_, int t = 1) {return n_ > t ? calc_n(n_, t << 1) : t;}
};#line 1 "test/aoj/../../monoid/pair/../plus.cpp"
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
};#line 2 "test/aoj/../../monoid/pair/plus_plus.cpp"

template<class T, class U = T>
struct plus_plus_monoid {
	struct Lazy : public plus_monoid<U> {
		using plus_monoid<U>::plus_monoid;
		using plus_monoid<U>::operator+;
		using plus_monoid<U>::operator=;
		Lazy(plus_monoid<U> x) : plus_monoid<U>(x) {}
		inline Lazy operator*(int len) const {
			return Lazy(this->val * len);
		}
		inline bool is_unity() const {
			return this->val == T();
		}
	};
	struct Monoid : public plus_monoid<T> {
		using plus_monoid<T>::plus_monoid;
		using plus_monoid<T>::operator+;
		using plus_monoid<T>::operator=;
		Monoid(plus_monoid<T> x) : plus_monoid<T>(x) {}
		inline Monoid operator+(const Lazy& rhs) const {
			return Monoid(this->val + rhs.val);
		}
	};
};#line 9 "test/aoj/LazySegmentTree_RSQ_RAQ.test.cpp"
using monoids = plus_plus_monoid<long long>;


int main() {
	int n, Q;
	cin >> n >> Q;
	LazySegmentTree<monoids> L(n);
	while (Q--) {
		int q;
		cin >> q;
		if (q == 0) {
			int s, t, x; cin >> s >> t >> x; s--; t--;
			L.set(s, t+1, x);
		} else {
			int s, t; cin >> s >> t; s--; t--;
			cout << L.get(s, t+1) << endl;
		}
	}
}
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

