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


# :heavy_check_mark: math/ModComb_compiletime.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7e676e9e663beb40fd133f5ee24487c2">math</a>
* <a href="{{ site.github.repository_url }}/blob/master/math/ModComb_compiletime.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-14 17:23:24+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/ModComb_compiletime.test.cpp.html">test/aoj/ModComb_compiletime.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
namespace modcomb_compiletime_n {
constexpr int N = 200000;
constexpr int mod = modint::M;
struct Fact {
	int_fast32_t val[N+1];
	int_fast32_t vali[N+1];
	constexpr Fact() : val() , vali() {
		val[0] = 1;
		for (int_fast32_t i = 1; i <= N; i++) val[i] = static_cast<int_fast64_t>(val[i-1]) * i % mod;
		vali[N] = static_cast<int_fast32_t>(modint(val[N]).inv().x);
		for (int_fast32_t i = N; i; i--) vali[i-1] = static_cast<int_fast64_t>(vali[i]) * i % mod;
	}
};
constexpr auto fact = Fact();
constexpr modint nCr(int n, int r) {
	assert(n <= N+1);
	if(n < 0 || r < 0 || n < r) return 0;
	return modint(fact.val[n]) * fact.vali[r] * fact.vali[n-r];
}
constexpr modint nPr(int n, int r) {
	assert(n <= N+1);
	if(n < 0 || r < 0 || n < r) return 0;
	return modint(fact.val[n]) * fact.vali[n-r];
}
constexpr modint nHr(int n, int r) {
	if(n < 0 || r < 0) return 0;
	return nCr(n + r - 1, r);
}
} // namespace modcomb_compiletime_n
using namespace modcomb_compiletime_n;
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "math/ModComb_compiletime.cpp"
namespace modcomb_compiletime_n {
constexpr int N = 200000;
constexpr int mod = modint::M;
struct Fact {
	int_fast32_t val[N+1];
	int_fast32_t vali[N+1];
	constexpr Fact() : val() , vali() {
		val[0] = 1;
		for (int_fast32_t i = 1; i <= N; i++) val[i] = static_cast<int_fast64_t>(val[i-1]) * i % mod;
		vali[N] = static_cast<int_fast32_t>(modint(val[N]).inv().x);
		for (int_fast32_t i = N; i; i--) vali[i-1] = static_cast<int_fast64_t>(vali[i]) * i % mod;
	}
};
constexpr auto fact = Fact();
constexpr modint nCr(int n, int r) {
	assert(n <= N+1);
	if(n < 0 || r < 0 || n < r) return 0;
	return modint(fact.val[n]) * fact.vali[r] * fact.vali[n-r];
}
constexpr modint nPr(int n, int r) {
	assert(n <= N+1);
	if(n < 0 || r < 0 || n < r) return 0;
	return modint(fact.val[n]) * fact.vali[n-r];
}
constexpr modint nHr(int n, int r) {
	if(n < 0 || r < 0) return 0;
	return nCr(n + r - 1, r);
}
} // namespace modcomb_compiletime_n
using namespace modcomb_compiletime_n;
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

