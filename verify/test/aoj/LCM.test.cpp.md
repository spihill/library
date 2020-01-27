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


# :heavy_check_mark: test/aoj/LCM.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/LCM.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-27 00:26:08+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_C">https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_C</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/math/ctz.cpp.html">__builtin_ctz の代用関数</a>
* :heavy_check_mark: <a href="../../../library/math/gcd.cpp.html">最大公約数</a>
* :heavy_check_mark: <a href="../../../library/math/lcm.cpp.html">最小公倍数</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_C"

#include<bits/stdc++.h>
using namespace std;

#include "../../math/lcm.cpp"

int main() {
	uint_fast32_t res = 1;
	int n; cin >> n;
	for (int i = 0; i < n; i++) {
		uint_fast32_t a; cin >> a;
		res = lcm(res, a);
	}
	cout << res << endl;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj/LCM.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_C"

#include<bits/stdc++.h>
using namespace std;

#line 1 "test/aoj/../../math/ctz.cpp"
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
 * @brief __builtin_ctz の代用関数で、下位何ビット0が連続しているかを返す ($O(\log \log N)$)
 */
template<class T>
constexpr enable_if_t<is_integral<T>::value, int> ctz(T x) {
	static_assert(numeric_limits<make_unsigned_t<T>>::digits < 65, "");
	constexpr auto lb = lower_bit();
	int ok = 0, ng = numeric_limits<make_unsigned_t<T>>::digits + 1;
	while (ng - ok != 1) {
		int mid = (ok + ng) >> 1;
		(lb.val[mid] & x ? ng : ok) = mid;
	}
	return ok;
}#line 3 "test/aoj/../../math/gcd.cpp"
/**
 * @title 最大公約数
 */

// @brief Binary GCD
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

// @brief map<素数, 冪> の形の整数の gcd
template<class T>
enable_if_t<is_integral<T>::value, map<T, int>> gcd(const map<T, int>& a, const map<T, int>& b) {
	map<T, int> res;
	for (const auto& x : a) if (b.count(x.first)) res[x.first] = min(x.second, b.at(x.first));
	for (const auto& x : b) if (!a.count(x.first)) res.erase(x.first);
	return res;
}#line 2 "test/aoj/../../math/lcm.cpp"
// @title 最小公倍数

// @brief 最小公倍数を求める。(Binary GCD を利用)
template<class T>
constexpr enable_if_t<is_integral<T>::value, T> lcm(T a, T b) {
	if (a < 0) a = -a;
	if (b < 0) b = -b;
	return a / gcd(a, b) * b;
}

// @brief map<素数, 冪> の形の整数の lcm
template<class T>
enable_if_t<is_integral<T>::value, map<T, int>> lcm(const map<T, int>& a, const map<T, int>& b) {
	map<T, int> res = a;
	for (const auto& x : b) res[x.first] = max(res[x.first], x.second);
	return res;
}#line 7 "test/aoj/LCM.test.cpp"

int main() {
	uint_fast32_t res = 1;
	int n; cin >> n;
	for (int i = 0; i < n; i++) {
		uint_fast32_t a; cin >> a;
		res = lcm(res, a);
	}
	cout << res << endl;
}
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

