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


# :heavy_check_mark: monoid/max_monoid.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c3437aaac8e99d51d51e80f390e49b05">monoid</a>
* <a href="{{ site.github.repository_url }}/blob/master/monoid/max_monoid.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-11 02:27:56+09:00




## Depends on

* :heavy_check_mark: <a href="../for_include/monoid.cpp.html">for_include/monoid.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/SegmentTree_RMQ_2.test.cpp.html">test/aoj/SegmentTree_RMQ_2.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
namespace max_monoid_n {
#include "../for_include/monoid.cpp"
template<class T>
struct max_monoid : public monoid_base<T> {
	using monoid = max_monoid;
	using monoid_base<T>::monoid_base;
	max_monoid() : max_monoid(numeric_limits<T>::min()) {}
	monoid operator+(const monoid& rhs) const {
		return monoid(max(this->val, rhs.val));
	}
};
}
using max_monoid_n::max_monoid;
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "monoid/max_monoid.cpp"
namespace max_monoid_n {
#line 1 "monoid/../for_include/monoid.cpp"
template<class T>
struct monoid_base {
	struct monoid_tag {};
	using monoid_type = T;
	T val;
	monoid_base(T x) : val(x) {}
};
#line 3 "monoid/max_monoid.cpp"
template<class T>
struct max_monoid : public monoid_base<T> {
	using monoid = max_monoid;
	using monoid_base<T>::monoid_base;
	max_monoid() : max_monoid(numeric_limits<T>::min()) {}
	monoid operator+(const monoid& rhs) const {
		return monoid(max(this->val, rhs.val));
	}
};
}
using max_monoid_n::max_monoid;

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

