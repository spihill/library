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


# :warning: メンバ変数を3つ持つ比較可能なクラス (VSCode スニペット)

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#54de4c5e0ecfc39083b31b56ee36cb19">snippet</a>
* <a href="{{ site.github.repository_url }}/blob/master/snippet/class3.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-21 01:44:53+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// @title メンバ変数を3つ持つ比較可能なクラス (VSCode スニペット)
struct $1
{
	$2 $5;
	$3 $6;
	$4 $7;
	$1($2 v1, $3 v2, $4 v3) : $5(v1), $6(v2), $7(v3) {}
	$1() {}
	bool operator<(const $1 r) const {
		if ($5 == r.$5) {
			if ($6 == r.$6) {
				return $7 < r.$7;
			} else {
				return $6 < r.$6;
			}
		} else {
			return $5 < r.$5;
		}
	}
	bool operator>(const $1 r) const {
		return r < *this;
	}
	bool operator>=(const $1 r) const {
		return !(*this < r);
	}
	bool operator<=(const $1 r) const {
		return !(r < *this);
	}
	bool operator==(const $1 r) const {
		return !(r < *this) && !(*this < r);
	}
	bool operator!=(const $1 r) const {
		return (r < *this) || (*this < r);
	}
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "snippet/class3.cpp"
// @title メンバ変数を3つ持つ比較可能なクラス (VSCode スニペット)
struct $1
{
	$2 $5;
	$3 $6;
	$4 $7;
	$1($2 v1, $3 v2, $4 v3) : $5(v1), $6(v2), $7(v3) {}
	$1() {}
	bool operator<(const $1 r) const {
		if ($5 == r.$5) {
			if ($6 == r.$6) {
				return $7 < r.$7;
			} else {
				return $6 < r.$6;
			}
		} else {
			return $5 < r.$5;
		}
	}
	bool operator>(const $1 r) const {
		return r < *this;
	}
	bool operator>=(const $1 r) const {
		return !(*this < r);
	}
	bool operator<=(const $1 r) const {
		return !(r < *this);
	}
	bool operator==(const $1 r) const {
		return !(r < *this) && !(*this < r);
	}
	bool operator!=(const $1 r) const {
		return (r < *this) || (*this < r);
	}
};
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

