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


# :heavy_check_mark: 最小公倍数

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7e676e9e663beb40fd133f5ee24487c2">math</a>
* <a href="{{ site.github.repository_url }}/blob/master/math/lcm.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-15 22:27:27+09:00


* 最小公倍数を求める。(Binary GCD を利用)


## Depends on

* :heavy_check_mark: <a href="ctz.cpp.html">__builtin_ctz の代用関数</a>
* :heavy_check_mark: <a href="gcd.cpp.html">最大公約数</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/LCM.test.cpp.html">test/aoj/LCM.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "gcd.cpp"
/**
 * @title 最小公倍数
 * @brief 最小公倍数を求める。(Binary GCD を利用)
 */
template<class T>
constexpr enable_if_t<is_integral<T>::value, T> lcm(T a, T b) {
	if (a < 0) a = -a;
	if (b < 0) b = -b;
	return a / gcd(a, b) * b;
}



```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "math/ctz.cpp"
struct lower_bit {
	using u64 = uint_fast64_t;
	u64 val[65];
	constexpr lower_bit() : val() {
		val[0] = 0;
		val[1] = 1;
		for (size_t i = 2; i < 65; i++) {
			val[i] = (val[i-1] << 1) | 1;
		}
	}
};
/**
 * @title __builtin_ctz の代用関数
 * @brief __builtin_ctz の代用関数で、下位何ビット0が連続しているかを返す ($(O(\log \log N))$)
 */
template<class T>
constexpr enable_if_t<is_integral<T>::value, int> ctz(T x) {
	static_assert(numeric_limits<T>::digits < 65);
	constexpr auto lb = lower_bit();
	int ok = 0, ng = numeric_limits<T>::digits + 1;
	while (ng - ok != 1) {
		int mid = (ok + ng) >> 1;
		(lb.val[mid] & x ? ng : ok) = mid;
	}
	return ok;
}#line 2 "math/gcd.cpp"
/**
 * @title 最大公約数
 * @brief Binary GCD
 */
template<class T>
constexpr enable_if_t<is_integral<T>::value, T> gcd(T a, T b) {
	if (a < 0) a = -a;
	if (b < 0) b = -b;
	if (a == 0) return b;
	if (b == 0) return a;
	const int k = ctz(a | b);
	a >>= k;
	b >>= k;
	while (a != b) {
		if (a > b) a ^= b ^= a ^= b;
		b -= a;
		b >>= ctz(b);
	}
	return a << k;
}


#line 2 "math/lcm.cpp"
/**
 * @title 最小公倍数
 * @brief 最小公倍数を求める。(Binary GCD を利用)
 */
template<class T>
constexpr enable_if_t<is_integral<T>::value, T> lcm(T a, T b) {
	if (a < 0) a = -a;
	if (b < 0) b = -b;
	return a / gcd(a, b) * b;
}



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

