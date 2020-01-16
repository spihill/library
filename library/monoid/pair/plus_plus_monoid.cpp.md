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


# :heavy_check_mark: monoid/pair/plus_plus_monoid.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#8bd1ab4c7cd9516f57d0eb7bdbde5819">monoid/pair</a>
* <a href="{{ site.github.repository_url }}/blob/master/monoid/pair/plus_plus_monoid.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-16 19:28:18+09:00




## Depends on

* :heavy_check_mark: <a href="../plus_monoid.cpp.html">monoid/plus_monoid.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../../verify/test/aoj/LazySegmentTree_RSQ_RAQ.test.cpp.html">test/aoj/LazySegmentTree_RSQ_RAQ.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "../plus_monoid.cpp"

template<class T, class U = T>
struct plus_plus_monoid {
	struct Lazy : public plus_monoid<U> {
		using plus_monoid<U>::plus_monoid;
		using plus_monoid<U>::operator+;
		using plus_monoid<U>::operator=;
		Lazy(plus_monoid<U> x) : plus_monoid<U>(x) {}
		inline Lazy operator*(int len) const {
			return Lazy(this->val * len);
		}
		inline bool is_unity() const {
			return this->val == T();
		}
	};
	struct Monoid : public plus_monoid<T> {
		using plus_monoid<T>::plus_monoid;
		using plus_monoid<T>::operator+;
		using plus_monoid<T>::operator=;
		Monoid(plus_monoid<T> x) : plus_monoid<T>(x) {}
		inline Monoid operator+(const Lazy& rhs) const {
			return Monoid(this->val + rhs.val);
		}
	};
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "monoid/pair/../plus_monoid.cpp"
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
};#line 2 "monoid/pair/plus_plus_monoid.cpp"

template<class T, class U = T>
struct plus_plus_monoid {
	struct Lazy : public plus_monoid<U> {
		using plus_monoid<U>::plus_monoid;
		using plus_monoid<U>::operator+;
		using plus_monoid<U>::operator=;
		Lazy(plus_monoid<U> x) : plus_monoid<U>(x) {}
		inline Lazy operator*(int len) const {
			return Lazy(this->val * len);
		}
		inline bool is_unity() const {
			return this->val == T();
		}
	};
	struct Monoid : public plus_monoid<T> {
		using plus_monoid<T>::plus_monoid;
		using plus_monoid<T>::operator+;
		using plus_monoid<T>::operator=;
		Monoid(plus_monoid<T> x) : plus_monoid<T>(x) {}
		inline Monoid operator+(const Lazy& rhs) const {
			return Monoid(this->val + rhs.val);
		}
	};
};
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

