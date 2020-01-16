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


# :heavy_check_mark: 素因数分解

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7e676e9e663beb40fd133f5ee24487c2">math</a>
* <a href="{{ site.github.repository_url }}/blob/master/math/Factorize.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-17 01:32:20+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/Factorize_map.test.cpp.html">test/aoj/Factorize_map.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/Factorize_vec.test.cpp.html">test/aoj/Factorize_vec.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// @title 素因数分解
template<class T>
void Factorize(T n, map<T, int>& res) {
	for (T i = 2; i * i <= n; i++) {
		while (n % i == 0) {
			res[i]++;
			n /= i;
		}
	}
	if (n != 1) res[n]++;
}
template<class T>
void Factorize(T n, vector<T>& res) {
	for (T i = 2; i * i <= n; i++) {
		while (n % i == 0) {
			res.push_back(i);
			n /= i;
		}
	}
	if (n != 1) res.push_back(n);
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "math/Factorize.cpp"
// @title 素因数分解
template<class T>
void Factorize(T n, map<T, int>& res) {
	for (T i = 2; i * i <= n; i++) {
		while (n % i == 0) {
			res[i]++;
			n /= i;
		}
	}
	if (n != 1) res[n]++;
}
template<class T>
void Factorize(T n, vector<T>& res) {
	for (T i = 2; i * i <= n; i++) {
		while (n % i == 0) {
			res.push_back(i);
			n /= i;
		}
	}
	if (n != 1) res.push_back(n);
}
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

