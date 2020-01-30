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


# :heavy_check_mark: for_include/has_graph_tag.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#8be7b0dfa7a3a788ad1d174f54f0cafd">for_include</a>
* <a href="{{ site.github.repository_url }}/blob/master/for_include/has_graph_tag.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-27 18:45:58+09:00




## Required by

* :heavy_check_mark: <a href="../graph/SCC.cpp.html">graph/SCC.cpp</a>
* :heavy_check_mark: <a href="../graph/TopologicalSort.cpp.html">トポロジカルソート</a>
* :heavy_check_mark: <a href="../graph/is_Biparite.cpp.html">graph/is_Biparite.cpp</a>
* :heavy_check_mark: <a href="../graph_tree/LCA.cpp.html">graph_tree/LCA.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/LCA.test.cpp.html">test/aoj/LCA.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/TopologicalSort.test.cpp.html">test/aoj/TopologicalSort.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/is_Biparite.test.cpp.html">test/aoj/is_Biparite.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yosupo/SCC.test.cpp.html">test/yosupo/SCC.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template <class T>
class has_graph_tag {
	template <class U> static constexpr std::true_type check(typename U::graph_tag*);
	template <class U> static constexpr std::false_type check(...);
public:
	static constexpr bool value = decltype(check<T>(nullptr))::value;
};
template <class T> constexpr bool has_graph_tag_v = has_graph_tag<T>::value;
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "for_include/has_graph_tag.cpp"
template <class T>
class has_graph_tag {
	template <class U> static constexpr std::true_type check(typename U::graph_tag*);
	template <class U> static constexpr std::false_type check(...);
public:
	static constexpr bool value = decltype(check<T>(nullptr))::value;
};
template <class T> constexpr bool has_graph_tag_v = has_graph_tag<T>::value;

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

