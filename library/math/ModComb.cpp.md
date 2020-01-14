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


# :heavy_check_mark: math/ModComb.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7e676e9e663beb40fd133f5ee24487c2">math</a>
* <a href="{{ site.github.repository_url }}/blob/master/math/ModComb.cpp">View this file on GitHub</a>
    - Last commit date: 2019-07-29 01:47:35+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/ModComb.test.cpp.html">test/aoj/ModComb.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<class T>
struct ModComb {
	vector<T> fact;
	vector<T> facti;
	ModComb(int n) : fact(n+1), facti(n+1) {
		fact[0] = 1;
		for (int i = 1; i < n + 1; i++) {
			fact[i] = fact[i-1] * i;
		}
		facti[n] = 1 / fact[n];
		for (int i = n-1; i >= 0; i--) {
			facti[i] = facti[i+1] * (i + 1);
		}
	}
	T C(int n, int r) const {
		if(n < 0 || r < 0 || n < r) return 0;
		return fact[n] * facti[r] * facti[n-r];
	}
	T P(int n, int r) const {
		if(n < 0 || r < 0 || n < r) return 0;
		return fact[n] * facti[n-r];
	}
	T H(int n, int r) const {
		if(n < 0 || r < 0) return 0;
		return C(n + r - 1, r);
	}
};
using modcomb = ModComb<modint>;
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "math/ModComb.cpp"
template<class T>
struct ModComb {
	vector<T> fact;
	vector<T> facti;
	ModComb(int n) : fact(n+1), facti(n+1) {
		fact[0] = 1;
		for (int i = 1; i < n + 1; i++) {
			fact[i] = fact[i-1] * i;
		}
		facti[n] = 1 / fact[n];
		for (int i = n-1; i >= 0; i--) {
			facti[i] = facti[i+1] * (i + 1);
		}
	}
	T C(int n, int r) const {
		if(n < 0 || r < 0 || n < r) return 0;
		return fact[n] * facti[r] * facti[n-r];
	}
	T P(int n, int r) const {
		if(n < 0 || r < 0 || n < r) return 0;
		return fact[n] * facti[n-r];
	}
	T H(int n, int r) const {
		if(n < 0 || r < 0) return 0;
		return C(n + r - 1, r);
	}
};
using modcomb = ModComb<modint>;
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

