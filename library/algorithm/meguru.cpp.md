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


# :heavy_check_mark: algorithm/meguru.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ed469618898d75b149e5c7c4b6a1c415">algorithm</a>
* <a href="{{ site.github.repository_url }}/blob/master/algorithm/meguru.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-11 17:11:35+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/meguru.test.cpp.html">test/aoj/meguru.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/meguru_2.test.cpp.html">test/aoj/meguru_2.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// meguru<T>(ok, ng, isok)で呼ぶ
template<class T>
T meguru(T ok, T ng, function<bool(T)> isok) {
	while (abs(ok - ng) > 1) {
		T mid = (ok + ng) / 2;
		(isok(mid) ? ok : ng) = mid;
	}
	return ok;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "algorithm/meguru.cpp"
// meguru<T>(ok, ng, isok)で呼ぶ
template<class T>
T meguru(T ok, T ng, function<bool(T)> isok) {
	while (abs(ok - ng) > 1) {
		T mid = (ok + ng) / 2;
		(isok(mid) ? ok : ng) = mid;
	}
	return ok;
}
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

