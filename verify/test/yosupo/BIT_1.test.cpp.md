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


# :heavy_check_mark: test/yosupo/BIT_1.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/yosupo/BIT_1.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-21 01:27:24+09:00


* see: <a href="https://judge.yosupo.jp/problem/point_add_range_sum">https://judge.yosupo.jp/problem/point_add_range_sum</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/datastructure/BIT.cpp.html">BIT (Binary Indexed Tree)</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include<bits/stdc++.h>
using namespace std;

#include "../../datastructure/BIT.cpp"

int main() {
	int n, Q; cin >> n >> Q;
	BIT<long long> B(n+1);
	for (int i = 0; i < n; i++) {
		int x; cin >> x; B.add(i, x);
	}
	while (Q--) {
		int q; cin >> q;
		if (q) {
			int l, r; cin >> l >> r; cout << B.get(r) - B.get(l) << endl;
		} else {
			int p, x; cin >> p >> x;
			B.add(p, x);
		}
	}
}


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yosupo/BIT_1.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include<bits/stdc++.h>
using namespace std;

#line 1 "test/yosupo/../../datastructure/BIT.cpp"
/**
 * @title BIT (Binary Indexed Tree)
 * @brief 0-indexed 半開区間で扱う。フェニック木 (Fenwick Tree) とも呼ばれる。
 */
template<class T>
struct BIT {
	int n;
	vector<T> bit;
	// @brief 長さ N で初期化 $O(N)$
	BIT(int n_) : n(n_), bit(n) {}
	// @brief vector で初期化 $O(N)$
	BIT(const vector<T>& v) :n(v.size()), bit(v) {
		for (int i = 0; i < n-1; i++) if ((i | (i + 1)) < n) bit[i | (i + 1)] += bit[i];
	}
	// @brief i 番目の要素に v を足す $O(\log N)$
 	// 0-indexed
	void add(int i, T v) {
		for (; i < n; i |= i + 1) bit[i] += v;
	}
	// @brief [0, i) の区間の和 の計算 $O(\log N)$
 	// 0-indexed 半開区間
	T get(int i) {
		T res = 0;
		for (i--; i >= 0; i = (i & (i + 1)) - 1) res += bit[i];
		return res;
	}
	// @brief [i, j) の区間の和 の計算 $O(\log N)$
 	// 0-indexed 半開区間
	T get(int i, int j) {
		return get(j) - get(i);
	}
};#line 7 "test/yosupo/BIT_1.test.cpp"

int main() {
	int n, Q; cin >> n >> Q;
	BIT<long long> B(n+1);
	for (int i = 0; i < n; i++) {
		int x; cin >> x; B.add(i, x);
	}
	while (Q--) {
		int q; cin >> q;
		if (q) {
			int l, r; cin >> l >> r; cout << B.get(r) - B.get(l) << endl;
		} else {
			int p, x; cin >> p >> x;
			B.add(p, x);
		}
	}
}


```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

