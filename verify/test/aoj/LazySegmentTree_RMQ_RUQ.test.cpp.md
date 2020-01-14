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

* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/LazySegmentTree_RMQ_RUQ.test.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-25 01:14:06+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_F">https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_F</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/datastructure/SegmentTree/LazySegmentTree.cpp.html">datastructure/SegmentTree/LazySegmentTree.cpp</a>
* :heavy_check_mark: <a href="../../../library/datastructure/SegmentTree/RMQ_RUQ.cpp.html">datastructure/SegmentTree/RMQ_RUQ.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_F"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/SegmentTree/LazySegmentTree.cpp"
#include "../../datastructure/SegmentTree/RMQ_RUQ.cpp"


int main() {
	int n, Q;
	cin >> n >> Q;
	LazySegmentTree<RMQ_RUQ<int, int>> L(n);
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
#include <bits/stdc++.h>
using namespace std;

template<class MonoidPair>
struct LazySegmentTree {
	int n;
	using NODE = typename MonoidPair::NODE; using NODE_T = typename MonoidPair::NODE_T;
	using LAZY = typename MonoidPair::LAZY; using LAZY_T = typename MonoidPair::LAZY_T;
	vector<NODE> node;
	vector<LAZY> lazy;
	LazySegmentTree (int n_) {build(n_);}
	LazySegmentTree (const vector<NODE_T>& v) {build(v);}
	LazySegmentTree () {}
	void build(int n_) {
		n = calc_n(n_);
		node.clear(); node.resize(2*n-1);
		lazy.clear(); lazy.resize(2*n-1);
	}
	void build(const vector<NODE_T>& v) {
		build(v.size());
		for (size_t i = 0; i < v.size(); i++) {
			node[i+n-1].val = v[i];
		}
		for (int i = n - 2; i >= 0; i--){
			node[i] = node[i*2+1] + node[i*2+2];
		}
	}
	void eval(int len, int k) {
		if (lazy[k].val == LAZY::UNITY) return;
		if (2*k+1 < 2*n-1) {
			lazy[2*k+1] = lazy[2*k+1] + lazy[k];
			lazy[2*k+2] = lazy[2*k+2] + lazy[k];
		}
		node[k] = node[k] + lazy[k] * len;
		lazy[k].val = LAZY::UNITY;
	}
	NODE set(int a, int b, LAZY_T x, int k, int l, int r) {
		eval(r-l, k);
		if (r <= a || b <= l) return node[k];
		if (a <= l && r <= b) {
			lazy[k] = lazy[k] + LAZY(x);
			return node[k] + lazy[k] * (r-l);
		}
		return node[k] = set(a, b, x, 2*k+1, l, (l+r) / 2) + set(a, b, x, 2*k+2, (l+r) / 2, r);
	}
	void set(int a, int b, LAZY_T x) {set(a, b, x, 0, 0, n);}
	NODE get(int a, int b, int k, int l, int r) {
		eval(r-l, k);
		if (a <= l && r <= b) {
			return node[k];
		} else if (b <= l || r <= a) {
			return NODE();
		}
		return get(a, b, 2*k+1, l, (l+r) / 2) + get(a, b, 2*k+2, (l+r) / 2, r);
	}
	NODE_T get(int a, int b) {return get(a, b, 0, 0, n).val;}
	const NODE_T& operator[](int i) {
		return node[i+n-1].val;
	}
	int calc_n(int n_, int t = 1) {return n_ > t ? calc_n(n_, t << 1) : t;}
};#line 1 "test/aoj/../../datastructure/SegmentTree/RMQ_RUQ.cpp"
template<class T, class U>
struct RMQ_RUQ {
	struct RMQ {
		constexpr static T UNITY = numeric_limits<T>::max();
		T val;
		explicit RMQ(T v) : val(v) {}
		explicit RMQ() : val(UNITY) {}
		inline RMQ operator+(const RMQ& rhs) const {
			return RMQ(min(val, rhs.val));
		}
	};
	struct RUQ {
		constexpr static U UNITY = numeric_limits<U>::min();
		U val;
		explicit RUQ(U v) : val(v) {}
		explicit RUQ() : val(UNITY) {}
		inline RUQ operator+(const RUQ& rhs) const {
			return RUQ(rhs.val);
		}
		inline RUQ operator*(const int len) const {
			return RUQ(*this);
		}
	};
	friend inline RMQ operator+(const RMQ& lhs, const RUQ& rhs) {
		return RMQ(rhs.val);
	}
	using NODE = RMQ; using NODE_T = T;
	using LAZY = RUQ; using LAZY_T = U;
};#line 9 "test/aoj/LazySegmentTree_RMQ_RUQ.test.cpp"


int main() {
	int n, Q;
	cin >> n >> Q;
	LazySegmentTree<RMQ_RUQ<int, int>> L(n);
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

