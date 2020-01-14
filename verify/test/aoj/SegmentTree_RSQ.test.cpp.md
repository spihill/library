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


# :heavy_check_mark: test/aoj/SegmentTree_RSQ.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/SegmentTree_RSQ.test.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-25 01:14:06+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B">https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/datastructure/SegmentTree/RSQ.cpp.html">datastructure/SegmentTree/RSQ.cpp</a>
* :heavy_check_mark: <a href="../../../library/datastructure/SegmentTree/SegmentTree.cpp.html">datastructure/SegmentTree/SegmentTree.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/SegmentTree/SegmentTree.cpp"
#include "../../datastructure/SegmentTree/RSQ.cpp"

int main() {
	int N, Q;
	scanf("%d %d", &N, &Q);
	vector<long long> v(N, 0);
	SegmentTree<RSQ<>> S(v);
	while (Q--) {
		int q, x, y;
		scanf("%d %d %d", &q, &x, &y);
		if (q == 0) {
			x--;
			S.set(x, y);
		} else {
			x--;
			y--;
			printf("%lld\n", S.get(x, y+1));
		}
	}
	return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj/SegmentTree_RSQ.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B"

#include<bits/stdc++.h>

using namespace std;

#line 1 "test/aoj/../../datastructure/SegmentTree/SegmentTree.cpp"
template<class NODE>
struct SegmentTree {
	using NODE_T = typename NODE::NODE_T;
	using ASSIGN_T = typename NODE::ASSIGN_T;
	using index_type = uint_fast32_t;
	index_type n;
	vector<NODE> node;
	SegmentTree (index_type n_) {build(n_);}
	SegmentTree (const vector<NODE_T>& v) {build(v);}
	void build(index_type n_) {
		n = calc_n(n_);
		node.clear(); node.resize(2*n-1);
	}
	void build(const vector<NODE_T>& v) {
		build(index_type(v.size()));
		for (size_t i = 0; i < v.size(); i++) {
			node[i+n-1].val = v[i];
		}
		for (int i = n - 2; i >= 0; i--){
			node[i] = node[i*2+1] + node[i*2+2];
		}
	}
	void set(index_type p, ASSIGN_T v) {
		p += n - 1;
		node[p].assign(v);
		while (p) {
			p = (p-1) / 2;
			node[p] = node[p*2+1] + node[p*2+2];
		}
	}
	NODE_T get(index_type l, index_type r) {
		NODE val_l, val_r;
		for (l += n-1, r += n-1; l < r; l /= 2, r = (r - 1) / 2) {
			if (l % 2 == 0) val_l = val_l + node[l];
			if (r % 2 == 0) val_r = node[r-1] + val_r;
		}
		return (val_l + val_r).val;
	}
	const NODE_T& operator[](index_type i) {
		return node[i+n-1].val;
	}
	index_type calc_n(index_type n_, index_type t = 1) {return n_ > t ? calc_n(n_, t << 1) : t;}
};
#line 1 "test/aoj/../../datastructure/SegmentTree/RSQ.cpp"
template<class T = long long, class U = T>
struct RSQ {
	T val;
	constexpr static T UNITY = 0;
	explicit RSQ(T v) : val(v) {}
	explicit RSQ() : val(UNITY) {}
	inline RSQ operator+(const RSQ& rhs) const {
		return RSQ(val + rhs.val);
	}
	inline void assign(const U v) {
		val += v;
	}
	using NODE_T = T; using ASSIGN_T = U;
};#line 9 "test/aoj/SegmentTree_RSQ.test.cpp"

int main() {
	int N, Q;
	scanf("%d %d", &N, &Q);
	vector<long long> v(N, 0);
	SegmentTree<RSQ<>> S(v);
	while (Q--) {
		int q, x, y;
		scanf("%d %d %d", &q, &x, &y);
		if (q == 0) {
			x--;
			S.set(x, y);
		} else {
			x--;
			y--;
			printf("%lld\n", S.get(x, y+1));
		}
	}
	return 0;
}
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

