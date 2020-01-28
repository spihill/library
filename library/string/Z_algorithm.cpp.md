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


# :heavy_check_mark: string/Z_algorithm.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#b45cffe084dd3d20d928bee85e7b0f21">string</a>
* <a href="{{ site.github.repository_url }}/blob/master/string/Z_algorithm.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-12 00:37:17+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/yosupo/Z_algorithm.test.cpp.html">test/yosupo/Z_algorithm.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
namespace z_algorithm_n {
	using i32 = int_fast32_t;
	using u32 = uint_fast32_t;
	template<class T>
	vector<i32> Z_algorithm(const T& v) {
		const u32 n = v.size();
		vector<i32> res(n, n);
		u32 i = 1, j = 0;
		while (i < n) {
			for (;i + j < n && v[j] == v[i+j]; j++);
			res[i] = j;
			if (j == 0) {i++; continue;}
			int k;
			for (k = 1; k + res[k] < j; k++) res[i+k] = res[k];
			i += k, j -= k;
		}
		return res;
	}
} 
using namespace z_algorithm_n;
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "string/Z_algorithm.cpp"
namespace z_algorithm_n {
	using i32 = int_fast32_t;
	using u32 = uint_fast32_t;
	template<class T>
	vector<i32> Z_algorithm(const T& v) {
		const u32 n = v.size();
		vector<i32> res(n, n);
		u32 i = 1, j = 0;
		while (i < n) {
			for (;i + j < n && v[j] == v[i+j]; j++);
			res[i] = j;
			if (j == 0) {i++; continue;}
			int k;
			for (k = 1; k + res[k] < j; k++) res[i+k] = res[k];
			i += k, j -= k;
		}
		return res;
	}
} 
using namespace z_algorithm_n;
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

