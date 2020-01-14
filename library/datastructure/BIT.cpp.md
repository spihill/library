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


# :x: datastructure/BIT.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#8dc87745f885a4cc532acd7b15b8b5fe">datastructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/datastructure/BIT.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-09 01:39:24+09:00




## Required by

* :x: <a href="../algorithm/dictionary_order.cpp.html">algorithm/dictionary_order.cpp</a>


## Verified with

* :x: <a href="../../verify/test/mytest/dictionary_order.test.cpp.html">test/mytest/dictionary_order.test.cpp</a>
* :x: <a href="../../verify/test/yosupo/BIT_1.test.cpp.html">test/yosupo/BIT_1.test.cpp</a>
* :x: <a href="../../verify/test/yosupo/BIT_2.test.cpp.html">test/yosupo/BIT_2.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<class T>
struct BIT {
	int n;
	vector<T> bit;
	BIT(int n_) : n(n_), bit(n) {}
	BIT(const vector<T>& v) : BIT(v.size()) {
		for (int i = 0; i < n; i++) bit[i] = v[i];
		for (int i = 0; i < n-1; i++) if ((i | (i + 1)) < n) bit[i | (i + 1)] += bit[i];
	}
	// bit[i] += v
	void add(int i, T v) {
		for (; i < n; i |= i + 1) bit[i] += v;
	}
	// sum of [0, i)
	T get(int i) {
		T res = 0;
		for (i--; i >= 0; i = (i & (i + 1)) - 1) res += bit[i];
		return res;
	}
	// sum of [i, j)
	T get(int i, int j) {
		return get(j) - get(i);
	}
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "datastructure/BIT.cpp"
template<class T>
struct BIT {
	int n;
	vector<T> bit;
	BIT(int n_) : n(n_), bit(n) {}
	BIT(const vector<T>& v) : BIT(v.size()) {
		for (int i = 0; i < n; i++) bit[i] = v[i];
		for (int i = 0; i < n-1; i++) if ((i | (i + 1)) < n) bit[i | (i + 1)] += bit[i];
	}
	// bit[i] += v
	void add(int i, T v) {
		for (; i < n; i |= i + 1) bit[i] += v;
	}
	// sum of [0, i)
	T get(int i) {
		T res = 0;
		for (i--; i >= 0; i = (i & (i + 1)) - 1) res += bit[i];
		return res;
	}
	// sum of [i, j)
	T get(int i, int j) {
		return get(j) - get(i);
	}
};
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

