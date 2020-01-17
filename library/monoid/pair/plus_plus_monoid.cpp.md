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
    - Last commit date: 2020-01-17 14:13:11+09:00




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
	template<class TT> using lazy_monoid = plus_monoid<TT>;
	template<class TT> using node_monoid = plus_monoid<TT>;
	struct Lazy : public lazy_monoid<U> {
		using lazy_monoid<U>::lazy_monoid;
		using lazy_monoid<U>::operator+;
		using lazy_monoid<U>::operator=;
		Lazy(lazy_monoid<U> x) : lazy_monoid<U>(x) {}
		inline Lazy operator*(int len) const {
			return Lazy(this->val * len);
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
	template<class TT> using lazy_monoid = plus_monoid<TT>;
	template<class TT> using node_monoid = plus_monoid<TT>;
	struct Lazy : public lazy_monoid<U> {
		using lazy_monoid<U>::lazy_monoid;
		using lazy_monoid<U>::operator+;
		using lazy_monoid<U>::operator=;
		Lazy(lazy_monoid<U> x) : lazy_monoid<U>(x) {}
		inline Lazy operator*(int len) const {
			return Lazy(this->val * len);
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
		inline Node operator+(const Lazy& rhs) const {
			return Node(this->val + rhs.val);
		}
	};
};
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

