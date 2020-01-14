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


# :warning: snippet/SegNode.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#54de4c5e0ecfc39083b31b56ee36cb19">snippet</a>
* <a href="{{ site.github.repository_url }}/blob/master/snippet/SegNode.cpp">View this file on GitHub</a>
    - Last commit date: 2019-10-06 07:09:46+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<class T, class U = T>
struct Node {
	T val;
	const static T UNITY = $1;
	explicit Node(T v) : val(v) {}
	explicit Node() : val(UNITY) {}
	inline Node operator+(const Node& rhs) const { // valとrhs.valの演算 
		return Node($2);
	}
	inline void assign(const U v) { // setクエリで代入する際の処理
		val = $3;
	}
	using NODE_T = T; using ASSIGN_T = U;
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "snippet/SegNode.cpp"
template<class T, class U = T>
struct Node {
	T val;
	const static T UNITY = $1;
	explicit Node(T v) : val(v) {}
	explicit Node() : val(UNITY) {}
	inline Node operator+(const Node& rhs) const { // valとrhs.valの演算 
		return Node($2);
	}
	inline void assign(const U v) { // setクエリで代入する際の処理
		val = $3;
	}
	using NODE_T = T; using ASSIGN_T = U;
};
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

