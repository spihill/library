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


# :heavy_check_mark: monoid/affine_monoid.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c3437aaac8e99d51d51e80f390e49b05">monoid</a>
* <a href="{{ site.github.repository_url }}/blob/master/monoid/affine_monoid.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-16 21:55:39+09:00




## Required by

* :heavy_check_mark: <a href="pair/plus_affine_monoid.cpp.html">monoid/pair/plus_affine_monoid.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/yosupo/DynamicSegTree_Affine.test.cpp.html">test/yosupo/DynamicSegTree_Affine.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yosupo/DynamicSegTree_Affine_2.test.cpp.html">test/yosupo/DynamicSegTree_Affine_2.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yosupo/LazySegTree_Plus_Affine.test.cpp.html">test/yosupo/LazySegTree_Plus_Affine.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yosupo/RBST_Affine.test.cpp.html">test/yosupo/RBST_Affine.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yosupo/RBST_Affine_2.test.cpp.html">test/yosupo/RBST_Affine_2.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yosupo/SWAG_Affine.test.cpp.html">test/yosupo/SWAG_Affine.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yosupo/SegTree_Affine.test.cpp.html">test/yosupo/SegTree_Affine.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<class T>
struct affine_monoid {
	using mono = affine_monoid;
	affine_monoid() : affine_monoid(pair<T, T>(1, 0)) {}
	explicit affine_monoid(pair<T, T> x) : val(x) {}
	pair<T, T> val;
	mono operator+(const mono& rhs) const {
		return mono(pair<T, T>(rhs.val.first * val.first, rhs.val.first * val.second + rhs.val.second));
	}
	friend istream& operator>>(istream& lhs, mono& rhs) {
		lhs >> rhs.val.first >> rhs.val.second;
		return lhs;
	}
	friend ostream& operator<<(ostream& lhs, mono& rhs) {
		lhs << rhs.val.first << ' ' << rhs.val.second;
		return lhs;
	}
	using monoid_type = pair<T, T>;
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "monoid/affine_monoid.cpp"
template<class T>
struct affine_monoid {
	using mono = affine_monoid;
	affine_monoid() : affine_monoid(pair<T, T>(1, 0)) {}
	explicit affine_monoid(pair<T, T> x) : val(x) {}
	pair<T, T> val;
	mono operator+(const mono& rhs) const {
		return mono(pair<T, T>(rhs.val.first * val.first, rhs.val.first * val.second + rhs.val.second));
	}
	friend istream& operator>>(istream& lhs, mono& rhs) {
		lhs >> rhs.val.first >> rhs.val.second;
		return lhs;
	}
	friend ostream& operator<<(ostream& lhs, mono& rhs) {
		lhs << rhs.val.first << ' ' << rhs.val.second;
		return lhs;
	}
	using monoid_type = pair<T, T>;
};
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

