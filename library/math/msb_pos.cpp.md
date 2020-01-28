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


# :heavy_check_mark: msb の位置を調べる

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7e676e9e663beb40fd133f5ee24487c2">math</a>
* <a href="{{ site.github.repository_url }}/blob/master/math/msb_pos.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-27 00:26:08+09:00


* __lg の代用関数で、msb が何桁目かを返す (0-indexed で msb が無い場合は -1) ($O(\log \log N)$)


## Required by

* :heavy_check_mark: <a href="../datastructure/SegmentTree/DynamicSegTree.cpp.html">動的セグメント木</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/DynamicSetgree_RMQ.test.cpp.html">test/aoj/DynamicSetgree_RMQ.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/DynamicSetgree_RSQ.test.cpp.html">test/aoj/DynamicSetgree_RSQ.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/mytest/builtin_functions.test.cpp.html">test/mytest/builtin_functions.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yosupo/DynamicSegTree_Affine.test.cpp.html">test/yosupo/DynamicSegTree_Affine.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yosupo/DynamicSegTree_Affine_2.test.cpp.html">test/yosupo/DynamicSegTree_Affine_2.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct upper_bit {
	using u64 = uint_fast64_t;
	u64 val[65];
	constexpr upper_bit() : val() {
		val[64] = 0;
		val[63] = u64(1) << 63;
		for (size_t i = 62; ~i; i--) {
			val[i] = (val[i+1] >> 1) | val[63];
		}
	}
};
/**
 * @title msb の位置を調べる
 * @brief __lg の代用関数で、msb が何桁目かを返す (0-indexed で msb が無い場合は -1) ($O(\log \log N)$)
 */
template<class T>
constexpr enable_if_t<is_integral<T>::value, int> msb_pos(T x) {
	static_assert(numeric_limits<make_unsigned_t<T>>::digits < 65, "");
	constexpr auto ub = upper_bit();
	int ok = numeric_limits<make_unsigned_t<T>>::digits, ng = -1;
	while (ok - ng != 1) {
		int mid = (ok + ng) >> 1;
		(ub.val[mid] & x ? ng : ok) = mid;
	}
	return ok - 1;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "math/msb_pos.cpp"
struct upper_bit {
	using u64 = uint_fast64_t;
	u64 val[65];
	constexpr upper_bit() : val() {
		val[64] = 0;
		val[63] = u64(1) << 63;
		for (size_t i = 62; ~i; i--) {
			val[i] = (val[i+1] >> 1) | val[63];
		}
	}
};
/**
 * @title msb の位置を調べる
 * @brief __lg の代用関数で、msb が何桁目かを返す (0-indexed で msb が無い場合は -1) ($O(\log \log N)$)
 */
template<class T>
constexpr enable_if_t<is_integral<T>::value, int> msb_pos(T x) {
	static_assert(numeric_limits<make_unsigned_t<T>>::digits < 65, "");
	constexpr auto ub = upper_bit();
	int ok = numeric_limits<make_unsigned_t<T>>::digits, ng = -1;
	while (ok - ng != 1) {
		int mid = (ok + ng) >> 1;
		(ub.val[mid] & x ? ng : ok) = mid;
	}
	return ok - 1;
}
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

