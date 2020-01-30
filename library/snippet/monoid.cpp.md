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


# :warning: セグ木のモノイドを作る (VSCode スニペット)

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#54de4c5e0ecfc39083b31b56ee36cb19">snippet</a>
* <a href="{{ site.github.repository_url }}/blob/master/snippet/monoid.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-21 01:44:53+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// @title セグ木のモノイドを作る (VSCode スニペット)
template<class T>
struct ${1:monoid} {
	using mono = ${1:monoid};
	${1:monoid}() : ${1:monoid}(${2:T}()) {}
	explicit ${1:monoid}(${2:T} x) : val(x) {}
	${2:T} val;
	mono operator+(const mono& rhs) const {
		return mono(${3:val + rhs.val});
	}
	friend istream& operator>>(istream& lhs, mono& rhs) {
		lhs >> rhs.val;
		return lhs;
	}
	friend ostream& operator<<(ostream& lhs, mono& rhs) {
		lhs << rhs.val;
		return lhs;
	}
	using monoid_type = ${2:T};
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "snippet/monoid.cpp"
// @title セグ木のモノイドを作る (VSCode スニペット)
template<class T>
struct ${1:monoid} {
	using mono = ${1:monoid};
	${1:monoid}() : ${1:monoid}(${2:T}()) {}
	explicit ${1:monoid}(${2:T} x) : val(x) {}
	${2:T} val;
	mono operator+(const mono& rhs) const {
		return mono(${3:val + rhs.val});
	}
	friend istream& operator>>(istream& lhs, mono& rhs) {
		lhs >> rhs.val;
		return lhs;
	}
	friend ostream& operator<<(ostream& lhs, mono& rhs) {
		lhs << rhs.val;
		return lhs;
	}
	using monoid_type = ${2:T};
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

