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
    - Last commit date: 2020-01-26 21:46:50+09:00




## Depends on

* :heavy_check_mark: <a href="../min_monoid.cpp.html">monoid/min_monoid.cpp</a>
* :heavy_check_mark: <a href="../update_monoid.cpp.html">monoid/update_monoid.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../../verify/test/aoj/LazySegmentTree_RMQ_RUQ.test.cpp.html">test/aoj/LazySegmentTree_RMQ_RUQ.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "../min_monoid.cpp"
#include "../update_monoid.cpp"

template<class T, class U = T>
struct min_update_monoid {
	template<class TT> using lazy_monoid = update_monoid<TT>;
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
			return this->unit;
		}
	};
	struct Node : public node_monoid<T> {
		using node_monoid<T>::node_monoid;
		using node_monoid<T>::operator+;
		using node_monoid<T>::operator=;
		Node(node_monoid<T> x) : node_monoid<T>(x) {}
		Node() : node_monoid<T>() {}
		inline Node operator+(const Lazy& rhs) const {
			return Node(rhs.val);
		}
	};
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "monoid/pair/../min_monoid.cpp"
template<class T>
struct min_monoid {
	using mono = min_monoid;
	min_monoid() : min_monoid(numeric_limits<T>::max()) {}
	explicit min_monoid(T x) : val(x) {}
	T val;
	mono operator+(const mono& rhs) const {
		return mono(min(val, rhs.val));
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
#line 1 "monoid/pair/../update_monoid.cpp"
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
#line 3 "monoid/pair/min_update_monoid.cpp"

template<class T, class U = T>
struct min_update_monoid {
	template<class TT> using lazy_monoid = update_monoid<TT>;
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
			return this->unit;
		}
	};
	struct Node : public node_monoid<T> {
		using node_monoid<T>::node_monoid;
		using node_monoid<T>::operator+;
		using node_monoid<T>::operator=;
		Node(node_monoid<T> x) : node_monoid<T>(x) {}
		Node() : node_monoid<T>() {}
		inline Node operator+(const Lazy& rhs) const {
			return Node(rhs.val);
		}
	};
};

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

