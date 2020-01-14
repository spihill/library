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


# :x: datastructure/SegmentTree/RSQ.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#cbada5aa9c548d7605cff951f3e28eda">datastructure/SegmentTree</a>
* <a href="{{ site.github.repository_url }}/blob/master/datastructure/SegmentTree/RSQ.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-25 01:14:06+09:00




## Verified with

* :x: <a href="../../../verify/test/aoj/SegmentTree_RSQ.test.cpp.html">test/aoj/SegmentTree_RSQ.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<class T = long long, class U = T>
struct RSQ {
	T val;
	constexpr static T UNITY = 0;
	explicit RSQ(T v) : val(v) {}
	explicit RSQ() : val(UNITY) {}
	inline RSQ operator+(const RSQ& rhs) const {
		return RSQ(val + rhs.val);
	}
	inline void assign(const U v) {
		val += v;
	}
	using NODE_T = T; using ASSIGN_T = U;
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "datastructure/SegmentTree/RSQ.cpp"
template<class T = long long, class U = T>
struct RSQ {
	T val;
	constexpr static T UNITY = 0;
	explicit RSQ(T v) : val(v) {}
	explicit RSQ() : val(UNITY) {}
	inline RSQ operator+(const RSQ& rhs) const {
		return RSQ(val + rhs.val);
	}
	inline void assign(const U v) {
		val += v;
	}
	using NODE_T = T; using ASSIGN_T = U;
};
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

