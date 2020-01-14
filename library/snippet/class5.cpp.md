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


# :warning: snippet/class5.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#54de4c5e0ecfc39083b31b56ee36cb19">snippet</a>
* <a href="{{ site.github.repository_url }}/blob/master/snippet/class5.cpp">View this file on GitHub</a>
    - Last commit date: 2019-07-28 13:56:32+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct $1
{
	$2 $7;
	$3 $8;
	$4 $9;
	$5 $10; 
	$6 $11;
	$1($2 v1, $3 v2, $4 v3, $5 v4, $6 v5) : $7(v1), $8(v2), $9(v3), $10(v4), $11(v5) {}
	$1() {}
	bool operator<(const $1 r) const {
		if ($7 == r.$7) {
			if ($8 == r.$8) {
				if ($9 == r.$9) {
					if ($10 == r.$10) {
						return $11 < r.$11;
					} else {
						return $10 < r.$10;
					}
				} else {
					return $9 < r.$9;
				}
			} else {
				return $8 < r.$8;
			}
		} else {
			return $7 < r.$7;
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
#line 1 "snippet/class5.cpp"
struct $1
{
	$2 $7;
	$3 $8;
	$4 $9;
	$5 $10; 
	$6 $11;
	$1($2 v1, $3 v2, $4 v3, $5 v4, $6 v5) : $7(v1), $8(v2), $9(v3), $10(v4), $11(v5) {}
	$1() {}
	bool operator<(const $1 r) const {
		if ($7 == r.$7) {
			if ($8 == r.$8) {
				if ($9 == r.$9) {
					if ($10 == r.$10) {
						return $11 < r.$11;
					} else {
						return $10 < r.$10;
					}
				} else {
					return $9 < r.$9;
				}
			} else {
				return $8 < r.$8;
			}
		} else {
			return $7 < r.$7;
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

