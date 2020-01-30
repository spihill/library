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


# :heavy_check_mark: monoid/plus_monoid.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c3437aaac8e99d51d51e80f390e49b05">monoid</a>
* <a href="{{ site.github.repository_url }}/blob/master/monoid/plus_monoid.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-16 19:28:18+09:00




## Required by

* :heavy_check_mark: <a href="pair/min_plus_monoid.cpp.html">monoid/pair/min_plus_monoid.cpp</a>
* :heavy_check_mark: <a href="pair/plus_affine_monoid.cpp.html">monoid/pair/plus_affine_monoid.cpp</a>
* :heavy_check_mark: <a href="pair/plus_plus_monoid.cpp.html">monoid/pair/plus_plus_monoid.cpp</a>
* :heavy_check_mark: <a href="pair/plus_update_monoid.cpp.html">monoid/pair/plus_update_monoid.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/DynamicSetgree_RSQ.test.cpp.html">test/aoj/DynamicSetgree_RSQ.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/LazySegmentTree_RMQ_RAQ.test.cpp.html">test/aoj/LazySegmentTree_RMQ_RAQ.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/LazySegmentTree_RSQ_RAQ.test.cpp.html">test/aoj/LazySegmentTree_RSQ_RAQ.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/LazySegmentTree_RSQ_RUQ.test.cpp.html">test/aoj/LazySegmentTree_RSQ_RUQ.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/RBST_RSQ.test.cpp.html">test/aoj/RBST_RSQ.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/SegmentTree_RSQ.test.cpp.html">test/aoj/SegmentTree_RSQ.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/syakutori_DSL_3_A.test.cpp.html">test/aoj/syakutori_DSL_3_A.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/syakutori_DSL_3_C.test.cpp.html">test/aoj/syakutori_DSL_3_C.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yosupo/LazySegTree_Plus_Affine.test.cpp.html">test/yosupo/LazySegTree_Plus_Affine.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<class T>
struct plus_monoid {
	using mono = plus_monoid;
	plus_monoid() : plus_monoid(T()) {}
	explicit plus_monoid(T x) : val(x) {}
	T val;
	mono operator+(const mono& rhs) const {
		return mono(val + rhs.val);
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
#line 1 "monoid/plus_monoid.cpp"
template<class T>
struct plus_monoid {
	using mono = plus_monoid;
	plus_monoid() : plus_monoid(T()) {}
	explicit plus_monoid(T x) : val(x) {}
	T val;
	mono operator+(const mono& rhs) const {
		return mono(val + rhs.val);
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

