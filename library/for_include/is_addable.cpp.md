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


# :heavy_check_mark: for_include/is_addable.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#8be7b0dfa7a3a788ad1d174f54f0cafd">for_include</a>
* <a href="{{ site.github.repository_url }}/blob/master/for_include/is_addable.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-11 02:12:45+09:00




## Required by

* :heavy_check_mark: <a href="../datastructure/SegmentTree/SegmentTree.cpp.html">セグメント木</a>
* :heavy_check_mark: <a href="is_monoid.cpp.html">for_include/is_monoid.cpp</a>
* :heavy_check_mark: <a href="monoid_pair.cpp.html">for_include/monoid_pair.cpp</a>
* :heavy_check_mark: <a href="monoid_wrapper.cpp.html">for_include/monoid_wrapper.cpp</a>
* :heavy_check_mark: <a href="../monoid/max_monoid.cpp.html">monoid/max_monoid.cpp</a>
* :heavy_check_mark: <a href="../monoid/min_monoid.cpp.html">monoid/min_monoid.cpp</a>
* :heavy_check_mark: <a href="../monoid/pair/min_plus_monoid.cpp.html">monoid/pair/min_plus_monoid.cpp</a>
* :heavy_check_mark: <a href="../monoid/pair/min_update_monoid.cpp.html">monoid/pair/min_update_monoid.cpp</a>
* :heavy_check_mark: <a href="../monoid/pair/plus_affine_monoid.cpp.html">monoid/pair/plus_affine_monoid.cpp</a>
* :heavy_check_mark: <a href="../monoid/pair/plus_plus_monoid.cpp.html">monoid/pair/plus_plus_monoid.cpp</a>
* :heavy_check_mark: <a href="../monoid/pair/plus_update_monoid.cpp.html">monoid/pair/plus_update_monoid.cpp</a>
* :heavy_check_mark: <a href="../monoid/plus_monoid.cpp.html">monoid/plus_monoid.cpp</a>
* :heavy_check_mark: <a href="../monoid/update_monoid.cpp.html">monoid/update_monoid.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/DynamicSetgree_RMQ.test.cpp.html">test/aoj/DynamicSetgree_RMQ.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/DynamicSetgree_RSQ.test.cpp.html">test/aoj/DynamicSetgree_RSQ.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/LazySegmentTree_RMQ_RAQ.test.cpp.html">test/aoj/LazySegmentTree_RMQ_RAQ.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/LazySegmentTree_RMQ_RUQ.test.cpp.html">test/aoj/LazySegmentTree_RMQ_RUQ.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/LazySegmentTree_RSQ_RAQ.test.cpp.html">test/aoj/LazySegmentTree_RSQ_RAQ.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/LazySegmentTree_RSQ_RUQ.test.cpp.html">test/aoj/LazySegmentTree_RSQ_RUQ.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/RBST_RMQ.test.cpp.html">test/aoj/RBST_RMQ.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/RBST_RSQ.test.cpp.html">test/aoj/RBST_RSQ.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/SegmentTree_RMQ.test.cpp.html">test/aoj/SegmentTree_RMQ.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/SegmentTree_RMQ_2.test.cpp.html">test/aoj/SegmentTree_RMQ_2.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/SegmentTree_RSQ.test.cpp.html">test/aoj/SegmentTree_RSQ.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/syakutori_DSL_3_A.test.cpp.html">test/aoj/syakutori_DSL_3_A.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/syakutori_DSL_3_C.test.cpp.html">test/aoj/syakutori_DSL_3_C.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yosupo/LazySegTree_Plus_Affine.test.cpp.html">test/yosupo/LazySegTree_Plus_Affine.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yosupo/SegTree_Affine.test.cpp.html">test/yosupo/SegTree_Affine.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
namespace is_addable_n {
template <class T1, class T2 = T1>
class is_addable {
	template <class U1, class U2> static constexpr auto check(U1*, U2*) -> decltype(
		declval<U1>() + declval<U2>(), true_type()
	);
	template <class U1, class U2> static constexpr auto check(...) -> false_type;
public:
	static constexpr bool value = decltype(check<T1, T2>(nullptr, nullptr))::value;
};
template <class T, class U = T>
constexpr bool is_addable_v = is_addable<T, U>::value;
} // namespace is_addable_n
using is_addable_n::is_addable;
using is_addable_n::is_addable_v;
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "for_include/is_addable.cpp"
namespace is_addable_n {
template <class T1, class T2 = T1>
class is_addable {
	template <class U1, class U2> static constexpr auto check(U1*, U2*) -> decltype(
		declval<U1>() + declval<U2>(), true_type()
	);
	template <class U1, class U2> static constexpr auto check(...) -> false_type;
public:
	static constexpr bool value = decltype(check<T1, T2>(nullptr, nullptr))::value;
};
template <class T, class U = T>
constexpr bool is_addable_v = is_addable<T, U>::value;
} // namespace is_addable_n
using is_addable_n::is_addable;
using is_addable_n::is_addable_v;

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

