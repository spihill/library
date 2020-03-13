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


# :heavy_check_mark: monoid/pair/min_update_monoid.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#8bd1ab4c7cd9516f57d0eb7bdbde5819">monoid/pair</a>
* <a href="{{ site.github.repository_url }}/blob/master/monoid/pair/min_update_monoid.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-13 21:37:20+09:00




## Depends on

* :heavy_check_mark: <a href="../min_monoid.cpp.html">monoid/min_monoid.cpp</a>
* :heavy_check_mark: <a href="../update_monoid.cpp.html">monoid/update_monoid.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../../verify/test/aoj/LazySegmentTree_RMQ_RUQ.test.cpp.html">test/aoj/LazySegmentTree_RMQ_RUQ.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
namespace min_update_monoid_n {
#include "../min_monoid.cpp"
#include "../update_monoid.cpp"
template<class T, class U = T, class NODE = min_monoid<T>, class LAZY = update_monoid<U>>
struct min_update_monoid {
	using Node = NODE;
	using Lazy = LAZY;
	static Node apply(const Node& lhs, const LAZY& rhs) {
		if (rhs.val.second) return lhs;
		return Node(rhs.val.first);
	}
	static Lazy propagate(const Lazy& lhs, int len) {
		return lhs;
	}
};
} // namespace min_update_monoid
using min_update_monoid_n::min_update_monoid;
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "monoid/pair/min_update_monoid.cpp"
namespace min_update_monoid_n {
#line 1 "monoid/pair/../min_monoid.cpp"
namespace min_monoid_n {
template<class T>
struct min_monoid {
	using monoid_type = T;
	T val;
	min_monoid(T v) : val(v) {}
	min_monoid() : val(numeric_limits<T>::max()) {}
	static min_monoid merge(const min_monoid& lhs, const min_monoid& rhs) {
		return min_monoid(min(lhs.val, rhs.val));
	}
};
}
using min_monoid_n::min_monoid;
#line 1 "monoid/pair/../update_monoid.cpp"
namespace update_monoid_n {
template<class T>
struct update_monoid {
	using monoid_type = pair<T, char>;
	pair<T, char> val;
	update_monoid(T v) : val(v, 0) {}
	update_monoid(pair<T, char> v) : val(v) {}
	update_monoid() : val(T(), 1) {}
	static update_monoid merge(const update_monoid& lhs, const update_monoid& rhs) {
		if (rhs.val.second) return lhs;
		return rhs;
	}
};
}
using update_monoid_n::update_monoid;
#line 4 "monoid/pair/min_update_monoid.cpp"
template<class T, class U = T, class NODE = min_monoid<T>, class LAZY = update_monoid<U>>
struct min_update_monoid {
	using Node = NODE;
	using Lazy = LAZY;
	static Node apply(const Node& lhs, const LAZY& rhs) {
		if (rhs.val.second) return lhs;
		return Node(rhs.val.first);
	}
	static Lazy propagate(const Lazy& lhs, int len) {
		return lhs;
	}
};
} // namespace min_update_monoid
using min_update_monoid_n::min_update_monoid;

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

