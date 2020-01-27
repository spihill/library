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
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: algorithm/dictionary_order.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ed469618898d75b149e5c7c4b6a1c415">algorithm</a>
* <a href="{{ site.github.repository_url }}/blob/master/algorithm/dictionary_order.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-17 02:27:23+09:00




## Depends on

* :heavy_check_mark: <a href="../datastructure/BIT.cpp.html">BIT (Binary Indexed Tree)</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/mytest/dictionary_order.test.cpp.html">test/mytest/dictionary_order.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "../datastructure/BIT.cpp"
// 辞書順で何番目かを返す。(0-indexed)
// O(Nlog(N) + log(mod))
template<class T, class mint = modint>
mint dictionary_order(const vector<T>& vec) {
	size_t n = vec.size();
	if (n <= 1) return mint(0);
	vector<size_t> ord(n);
	vector<size_t> cnt(n);
	vector<size_t> cnt_sum(n+1);
	{
		map<T, size_t> ord_m;
		for (auto x : vec) ord_m[x] = 1;
		size_t index = 0;
		for (auto& p : ord_m) p.second = index++;
		for (size_t i = 0; i < n; i++) ord[i] = ord_m[vec[i]];
		for (size_t i = 0; i < n; i++) cnt[ord[i]]++;
		for (size_t i = 0; i < n; i++) cnt_sum[i+1] = cnt_sum[i] + cnt[i];
	}
	vector<mint> fact(n+1, 1);
	vector<mint> facti(n+1, 1);
	for (size_t i = 1; i <= n; i++) fact[i] = fact[i-1] * i;
	facti.back() = 1 / fact.back();
	for (size_t i = n-1; i > 0; i--) facti[i] = facti[i+1] * (i+1);
	BIT<int> bit(n+1);
	mint res = 0;
	mint inv = 1;
	for (size_t i = 0; i < n; i++) {
		inv *= facti[cnt[i]];
	}
	for (size_t i = 0; i < n-1; i++) {
		res += fact[n-i-1] * (mint(cnt_sum[ord[i]]) - bit.get(ord[i])) * inv;
		inv *= cnt[ord[i]]--;
		bit.add(ord[i], 1);
	}
	return res;
}
template<class mint = modint>
mint dictionary_order(const string& s) {
	vector<char> vs(s.begin(), s.end());
	return dictionary_order(vs);
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "algorithm/../datastructure/BIT.cpp"
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
};#line 2 "algorithm/dictionary_order.cpp"
// 辞書順で何番目かを返す。(0-indexed)
// O(Nlog(N) + log(mod))
template<class T, class mint = modint>
mint dictionary_order(const vector<T>& vec) {
	size_t n = vec.size();
	if (n <= 1) return mint(0);
	vector<size_t> ord(n);
	vector<size_t> cnt(n);
	vector<size_t> cnt_sum(n+1);
	{
		map<T, size_t> ord_m;
		for (auto x : vec) ord_m[x] = 1;
		size_t index = 0;
		for (auto& p : ord_m) p.second = index++;
		for (size_t i = 0; i < n; i++) ord[i] = ord_m[vec[i]];
		for (size_t i = 0; i < n; i++) cnt[ord[i]]++;
		for (size_t i = 0; i < n; i++) cnt_sum[i+1] = cnt_sum[i] + cnt[i];
	}
	vector<mint> fact(n+1, 1);
	vector<mint> facti(n+1, 1);
	for (size_t i = 1; i <= n; i++) fact[i] = fact[i-1] * i;
	facti.back() = 1 / fact.back();
	for (size_t i = n-1; i > 0; i--) facti[i] = facti[i+1] * (i+1);
	BIT<int> bit(n+1);
	mint res = 0;
	mint inv = 1;
	for (size_t i = 0; i < n; i++) {
		inv *= facti[cnt[i]];
	}
	for (size_t i = 0; i < n-1; i++) {
		res += fact[n-i-1] * (mint(cnt_sum[ord[i]]) - bit.get(ord[i])) * inv;
		inv *= cnt[ord[i]]--;
		bit.add(ord[i], 1);
	}
	return res;
}
template<class mint = modint>
mint dictionary_order(const string& s) {
	vector<char> vs(s.begin(), s.end());
	return dictionary_order(vs);
}
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

