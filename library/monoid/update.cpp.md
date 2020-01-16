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


# :heavy_check_mark: monoid/update.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c3437aaac8e99d51d51e80f390e49b05">monoid</a>
* <a href="{{ site.github.repository_url }}/blob/master/monoid/update.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-16 18:33:41+09:00




## Required by

* :heavy_check_mark: <a href="pair/min_update.cpp.html">monoid/pair/min_update.cpp</a>
* :heavy_check_mark: <a href="pair/plus_update.cpp.html">monoid/pair/plus_update.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/LazySegmentTree_RMQ_RUQ.test.cpp.html">test/aoj/LazySegmentTree_RMQ_RUQ.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/LazySegmentTree_RSQ_RUQ.test.cpp.html">test/aoj/LazySegmentTree_RSQ_RUQ.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<class T>
struct update_monoid {
	using mono = update_monoid;
	T val;
	bool unit;
	update_monoid() : val(T()), unit(true) {}
	explicit update_monoid(T x) : val(x), unit(false) {}
	mono operator+(const mono& rhs) const {
		if (rhs.unit) return *this;
		return rhs;
	}
	mono operator=(const mono& rhs) {
		unit = rhs.unit;
		val = rhs.val;
		return *this;
	}
	friend istream& operator>>(istream& lhs, mono& rhs) {
		lhs >> rhs.val;
		return lhs;
	}
	friend ostream& operator<<(ostream& lhs, mono& rhs) {
		lhs << rhs.val;
		return lhs;
	}
	using monoid_type = T;
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "monoid/update.cpp"
template<class T>
struct update_monoid {
	using mono = update_monoid;
	T val;
	bool unit;
	update_monoid() : val(T()), unit(true) {}
	explicit update_monoid(T x) : val(x), unit(false) {}
	mono operator+(const mono& rhs) const {
		if (rhs.unit) return *this;
		return rhs;
	}
	mono operator=(const mono& rhs) {
		unit = rhs.unit;
		val = rhs.val;
		return *this;
	}
	friend istream& operator>>(istream& lhs, mono& rhs) {
		lhs >> rhs.val;
		return lhs;
	}
	friend ostream& operator<<(ostream& lhs, mono& rhs) {
		lhs << rhs.val;
		return lhs;
	}
	using monoid_type = T;
};
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

