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


# :x: snippet/monoid.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#54de4c5e0ecfc39083b31b56ee36cb19">snippet</a>
* <a href="{{ site.github.repository_url }}/blob/master/snippet/monoid.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-25 01:14:06+09:00




## Verified with

* :x: <a href="../../verify/test/aoj/syakutori_DSL_3_A.test.cpp.html">test/aoj/syakutori_DSL_3_A.test.cpp</a>
* :x: <a href="../../verify/test/aoj/syakutori_DSL_3_C.test.cpp.html">test/aoj/syakutori_DSL_3_C.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<class T, T UNITY>
struct monoid {
	monoid operator+(const monoid& rhs) const noexcept; // {return monoid(val + rhs.val);}
	monoid() : val(UNITY) {}
	explicit monoid(T x) : val(x) {}
	T val;
	bool operator<(const monoid& rhs) const noexcept {return val < rhs.val;}
	bool operator>(const monoid& rhs) const noexcept {return rhs < *this;}
	bool operator<=(const monoid& rhs) const noexcept {return !(rhs < *this);}
	bool operator>=(const monoid& rhs) const noexcept {return !(*this < rhs);}
	bool operator==(const monoid& rhs) const noexcept {return !(*this < rhs) && !(rhs < *this);}
	bool operator!=(const monoid& rhs) const noexcept {return *this < rhs || rhs < *this;}
	friend istream& operator>>(istream& lhs, monoid& rhs) {
		lhs >> rhs.val;
		return lhs;
	}
	friend ostream& operator<<(ostream& lhs, monoid& rhs) {
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
#line 1 "snippet/monoid.cpp"
template<class T, T UNITY>
struct monoid {
	monoid operator+(const monoid& rhs) const noexcept; // {return monoid(val + rhs.val);}
	monoid() : val(UNITY) {}
	explicit monoid(T x) : val(x) {}
	T val;
	bool operator<(const monoid& rhs) const noexcept {return val < rhs.val;}
	bool operator>(const monoid& rhs) const noexcept {return rhs < *this;}
	bool operator<=(const monoid& rhs) const noexcept {return !(rhs < *this);}
	bool operator>=(const monoid& rhs) const noexcept {return !(*this < rhs);}
	bool operator==(const monoid& rhs) const noexcept {return !(*this < rhs) && !(rhs < *this);}
	bool operator!=(const monoid& rhs) const noexcept {return *this < rhs || rhs < *this;}
	friend istream& operator>>(istream& lhs, monoid& rhs) {
		lhs >> rhs.val;
		return lhs;
	}
	friend ostream& operator<<(ostream& lhs, monoid& rhs) {
		lhs << rhs.val;
		return lhs;
	}
	using monoid_type = T;
};
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

