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


# :heavy_check_mark: monoid/pair/min_plus_monoid.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#8bd1ab4c7cd9516f57d0eb7bdbde5819">monoid/pair</a>
* <a href="{{ site.github.repository_url }}/blob/master/monoid/pair/min_plus_monoid.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-11 02:13:33+09:00




## Depends on

* :heavy_check_mark: <a href="../../for_include/monoid.cpp.html">for_include/monoid.cpp</a>
* :heavy_check_mark: <a href="../min_monoid.cpp.html">monoid/min_monoid.cpp</a>
* :heavy_check_mark: <a href="../plus_monoid.cpp.html">monoid/plus_monoid.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../../verify/test/aoj/LazySegmentTree_RMQ_RAQ.test.cpp.html">test/aoj/LazySegmentTree_RMQ_RAQ.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "../min_monoid.cpp"
#include "../plus_monoid.cpp"

template<class T, class U = T>
struct min_plus_monoid {
	template<class TT> using lazy_monoid = plus_monoid<TT>;
	template<class TT> using node_monoid = min_monoid<TT>;
	struct Lazy : public lazy_monoid<U> {
		using lazy_monoid<U>::lazy_monoid;
		using lazy_monoid<U>::operator+;
		using lazy_monoid<U>::operator=;
		Lazy(lazy_monoid<U> x) : lazy_monoid<U>(x) {}
		Lazy() : lazy_monoid<U>() {}
		inline Lazy operator*(int len) const {
			return Lazy(this->val);
		}
		inline bool is_unity() const {
			return this->val == T();
		}
	};
	struct Node : public node_monoid<T> {
		using node_monoid<T>::node_monoid;
		using node_monoid<T>::operator+;
		using node_monoid<T>::operator=;
		Node(node_monoid<T> x) : node_monoid<T>(x) {}
		Node() : node_monoid<T>() {}
		inline Node operator+(const Lazy& rhs) const {
			return Node(this->val + rhs.val);
		}
	};
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "monoid/pair/../min_monoid.cpp"
namespace min_monoid_n {
#line 1 "monoid/pair/../../for_include/monoid.cpp"
template<class T>
struct monoid_base {
	struct monoid_tag {};
	using monoid_type = T;
	T val;
	monoid_base(T x) : val(x) {}
};
#line 3 "monoid/pair/../min_monoid.cpp"
template<class T>
struct min_monoid : public monoid_base<T> {
	using monoid = min_monoid;
	using monoid_base<T>::monoid_base;
	min_monoid() : min_monoid(numeric_limits<T>::max()) {}
	monoid operator+(const monoid& rhs) const {
		return monoid(min(this->val, rhs.val));
	}
};
}
using min_monoid_n::min_monoid;
#line 1 "monoid/pair/../plus_monoid.cpp"
namespace plus_monoid_n {
#line 1 "monoid/pair/../../for_include/monoid.cpp"
template<class T>
struct monoid_base {
	struct monoid_tag {};
	using monoid_type = T;
	T val;
	monoid_base(T x) : val(x) {}
};
#line 3 "monoid/pair/../plus_monoid.cpp"
template<class T>
struct plus_monoid : public monoid_base<T> {
	using monoid = plus_monoid;
	using monoid_base<T>::monoid_base;
	plus_monoid() : plus_monoid(0) {}
	monoid operator+(const monoid& rhs) const {
		return monoid(this->val + rhs.val);
	}
};
}
using plus_monoid_n::plus_monoid;
#line 3 "monoid/pair/min_plus_monoid.cpp"

template<class T, class U = T>
struct min_plus_monoid {
	template<class TT> using lazy_monoid = plus_monoid<TT>;
	template<class TT> using node_monoid = min_monoid<TT>;
	struct Lazy : public lazy_monoid<U> {
		using lazy_monoid<U>::lazy_monoid;
		using lazy_monoid<U>::operator+;
		using lazy_monoid<U>::operator=;
		Lazy(lazy_monoid<U> x) : lazy_monoid<U>(x) {}
		Lazy() : lazy_monoid<U>() {}
		inline Lazy operator*(int len) const {
			return Lazy(this->val);
		}
		inline bool is_unity() const {
			return this->val == T();
		}
	};
	struct Node : public node_monoid<T> {
		using node_monoid<T>::node_monoid;
		using node_monoid<T>::operator+;
		using node_monoid<T>::operator=;
		Node(node_monoid<T> x) : node_monoid<T>(x) {}
		Node() : node_monoid<T>() {}
		inline Node operator+(const Lazy& rhs) const {
			return Node(this->val + rhs.val);
		}
	};
};

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

