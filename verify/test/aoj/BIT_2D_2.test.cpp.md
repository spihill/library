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


# :heavy_check_mark: test/aoj/BIT_2D_2.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/BIT_2D_2.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-16 03:22:34+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1125">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1125</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/datastructure/BIT_2D.cpp.html">２次元 BIT</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1125"

#include<bits/stdc++.h>
using namespace std;

#include "../../datastructure/BIT_2D.cpp"

int solve(int N) {
	int H, W; cin >> H >> W;
	vector<vector<int>> v(H, vector<int>(W, 0));
	for (int i = 0; i < N; i++) {
		int a, b; cin >> a >> b; v[a-1][b-1] = 1;
	}
	BIT_2D<int> bit(v);
	int S, T; cin >> S >> T;
	int res = 0;
	for (int i = 0; i < H-S+1; i++) for (int j = 0; j < W-T+1; j++) {
		res = max(res, bit.get_sum(i, j, i+S, j+T));
	}
	return res;
}

int main() {
	int n;
	while (cin >> n, n) cout << solve(n) << endl;
}


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj/BIT_2D_2.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1125"

#include<bits/stdc++.h>
using namespace std;

#line 1 "test/aoj/../../datastructure/BIT_2D.cpp"
/**
 * @title２次元 BIT
 * @brief 0-indexed 半開区間で扱う (Binary Indexed Tree)
 */
template<class T>
struct BIT_2D {
	int H, W;
	vector<vector<T>> bit;
	// @brief 大きさ H * W で初期化 $O(H * W)$
	BIT_2D(int h, int w) : H(h), W(w), bit(H, vector<T>(W)) { }
	// @brief 2次元 vector で初期化 $O(H * W)$
	BIT_2D(vector<vector<T>>& v) : bit(v) {
		assert(v.size());
		assert(v[0].size());
		H = v.size();
		W = v[0].size();
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W-1; j++) {
				if ((j | (j + 1)) < W) bit[i][j | (j + 1)] += bit[i][j];
			}
		}
		for (int i = 0; i < H-1; i++) {
			if ((i | (i + 1)) >= H) continue;
			for (int j = 0; j < W; j++) {
				bit[i | (i + 1)][j] += bit[i][j];
			}
		}
	}
	// @brief (r, c) に v を足す $O(\log H * \log W)$
 	// 0-indexed
	void add(int r, int c, T v) {
		for (int i = r; i < H; i |= i + 1) {
			for (int j = c; j < W; j |= j + 1) {
				bit[i][j] += v;
			}
		}
	}
	// @brief (0, 0) ～ (r-1, c-1) の 長方形部分の sum を計算する $O(\log H * \log W)$
 	// 0-indexed 半開区間
	T get(int r, int c) {
		T res = 0;
		for (int i = r; i >= 0; i = (i & (i + 1)) - 1) {
			for (int j = c; j >= 0; j = (j & (j + 1)) - 1) {
				res += bit[i][j];
			}
		}
		return res;
	}
	// @brief (r1, c1) ～ (r2 - 1, c2 - 1) の 長方形部分の sum を計算する $O(\log H * \log W)$
 	// 0-indexed 半開区間
	T get_sum(int r1, int c1, int r2, int c2) {
		r1--; c1--; r2--; c2--;
		return get(r2, c2) - get(r1, c2) - get(r2, c1) + get(r1, c1);
	}
};
#line 7 "test/aoj/BIT_2D_2.test.cpp"

int solve(int N) {
	int H, W; cin >> H >> W;
	vector<vector<int>> v(H, vector<int>(W, 0));
	for (int i = 0; i < N; i++) {
		int a, b; cin >> a >> b; v[a-1][b-1] = 1;
	}
	BIT_2D<int> bit(v);
	int S, T; cin >> S >> T;
	int res = 0;
	for (int i = 0; i < H-S+1; i++) for (int j = 0; j < W-T+1; j++) {
		res = max(res, bit.get_sum(i, j, i+S, j+T));
	}
	return res;
}

int main() {
	int n;
	while (cin >> n, n) cout << solve(n) << endl;
}


```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

