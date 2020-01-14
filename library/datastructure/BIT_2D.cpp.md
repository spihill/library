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


# :warning: datastructure/BIT_2D.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#8dc87745f885a4cc532acd7b15b8b5fe">datastructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/datastructure/BIT_2D.cpp">View this file on GitHub</a>
    - Last commit date: 2019-07-28 13:56:32+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<class T>
struct BIT_2D {
	int R, C;
	vector<vector<T>> bit;
	BIT_2D(int r, int c) {
		R = r;
		C = c;
		bit.resize(r+1, vector<T>(c+1, 0));
	}
	void add(int r, int c, T v) {
		for (int i = r+1; i <= R; i += i & -i) {
			for (int j = c+1; j <= C; j += j & -j) {
				bit[i][j] += v;
			}
		}
	}
	T get(int r, int c) {
		T res = 0;
		for (int i = r+1; i; i -= i & -i) {
			for (int j = c+1; j; j -= j & -j) {
				res += bit[i][j];
			}
		}
		return res;
	}
// bit[r1][c1] ~~ bit[r2 - 1][c2 - 1]
	T get_sum(int r1, int c1, int r2, int c2) {
		r1--; c1--; r2--; c2--;
		return get(r2, c2) - get(r1, c2) - get(r2, c1) + get(r1, c1);
	}
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "datastructure/BIT_2D.cpp"
template<class T>
struct BIT_2D {
	int R, C;
	vector<vector<T>> bit;
	BIT_2D(int r, int c) {
		R = r;
		C = c;
		bit.resize(r+1, vector<T>(c+1, 0));
	}
	void add(int r, int c, T v) {
		for (int i = r+1; i <= R; i += i & -i) {
			for (int j = c+1; j <= C; j += j & -j) {
				bit[i][j] += v;
			}
		}
	}
	T get(int r, int c) {
		T res = 0;
		for (int i = r+1; i; i -= i & -i) {
			for (int j = c+1; j; j -= j & -j) {
				res += bit[i][j];
			}
		}
		return res;
	}
// bit[r1][c1] ~~ bit[r2 - 1][c2 - 1]
	T get_sum(int r1, int c1, int r2, int c2) {
		r1--; c1--; r2--; c2--;
		return get(r2, c2) - get(r1, c2) - get(r2, c1) + get(r1, c1);
	}
};
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

