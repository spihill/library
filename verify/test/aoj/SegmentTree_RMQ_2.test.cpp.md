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


# :heavy_check_mark: test/aoj/SegmentTree_RMQ_2.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/SegmentTree_RMQ_2.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-16 19:28:18+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A">https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/datastructure/SegmentTree/SegmentTree.cpp.html">datastructure/SegmentTree/SegmentTree.cpp</a>
* :heavy_check_mark: <a href="../../../library/monoid/max_monoid.cpp.html">monoid/max_monoid.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/SegmentTree/SegmentTree.cpp"
#include "../../monoid/max_monoid.cpp"


int main() {
	int n, Q;
	cin >> n >> Q;
	vector<long long> v(n, LLONG_MIN);
	SegmentTree<max_monoid<long long>> S(n);
	while (Q--) {
		long long q, x, y;
		cin >> q >> x >> y;
		if (q == 0) {
			S.set(x, -y);
			v[x] = -y;
		} else {
			long long r = S.get(x, y+1);
			if (r == LLONG_MIN) r = -INT_MAX;
			cout << -r << endl;
		}
	}
	SegmentTree<max_monoid<long long>> T(v);
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
#line 1 "test/aoj/SegmentTree_RMQ_2.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A"

#include<bits/stdc++.h>

using namespace std;

#line 1 "test/aoj/../../datastructure/SegmentTree/SegmentTree.cpp"
template<class Monoid>
struct SegmentTree {
	using Monoid_T = typename Monoid::monoid_type;
	using index_type = uint_fast32_t;
	index_type n;
	vector<Monoid> node;
	SegmentTree (index_type n_) {build(n_);}
	SegmentTree (const vector<Monoid_T>& v) {build(v);}
	void build(index_type n_) {
		n = calc_n(n_);
		node.clear(); node.resize(2*n-1);
	}
	void build(const vector<Monoid_T>& v) {
		build(index_type(v.size()));
		for (size_t i = 0; i < v.size(); i++) {
			node[i+n-1].val = v[i];
		}
		for (int i = n - 2; i >= 0; i--){
			node[i] = node[i*2+1] + node[i*2+2];
		}
	}
	void set(index_type p, Monoid_T v) {
		p += n - 1;
		node[p].val = move(v);
		while (p) {
			p = (p-1) / 2;
			node[p] = node[p*2+1] + node[p*2+2];
		}
	}
	Monoid_T get(index_type l, index_type r) {
		Monoid val_l, val_r;
		for (l += n-1, r += n-1; l < r; l /= 2, r = (r - 1) / 2) {
			if (l % 2 == 0) val_l = val_l + node[l];
			if (r % 2 == 0) val_r = node[r-1] + val_r;
		}
		return (val_l + val_r).val;
	}
	const Monoid_T& operator[](index_type i) {
		return node[i+n-1].val;
	}
	index_type calc_n(index_type n_, index_type t = 1) {return n_ > t ? calc_n(n_, t << 1) : t;}
};
#line 1 "test/aoj/../../monoid/max_monoid.cpp"
template<class T>
struct max_monoid {
	using mono = max_monoid;
	max_monoid() : max_monoid(numeric_limits<T>::min()) {}
	explicit max_monoid(T x) : val(x) {}
	T val;
	mono operator+(const mono& rhs) const {
		return mono(max(val, rhs.val));
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
};#line 9 "test/aoj/SegmentTree_RMQ_2.test.cpp"


int main() {
	int n, Q;
	cin >> n >> Q;
	vector<long long> v(n, LLONG_MIN);
	SegmentTree<max_monoid<long long>> S(n);
	while (Q--) {
		long long q, x, y;
		cin >> q >> x >> y;
		if (q == 0) {
			S.set(x, -y);
			v[x] = -y;
		} else {
			long long r = S.get(x, y+1);
			if (r == LLONG_MIN) r = -INT_MAX;
			cout << -r << endl;
		}
	}
	SegmentTree<max_monoid<long long>> T(v);
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
