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


# :heavy_check_mark: monoid/min_monoid.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c3437aaac8e99d51d51e80f390e49b05">monoid</a>
* <a href="{{ site.github.repository_url }}/blob/master/monoid/min_monoid.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-12 20:38:33+09:00




## Depends on

* :heavy_check_mark: <a href="../for_include/is_addable.cpp.html">for_include/is_addable.cpp</a>
* :heavy_check_mark: <a href="../for_include/monoid_wrapper.cpp.html">for_include/monoid_wrapper.cpp</a>


## Required by

* :heavy_check_mark: <a href="../datastructure/SegmentTree/RmQ.cpp.html">datastructure/SegmentTree/RmQ.cpp</a>
* :heavy_check_mark: <a href="pair/min_plus_monoid.cpp.html">monoid/pair/min_plus_monoid.cpp</a>
* :heavy_check_mark: <a href="pair/min_update_monoid.cpp.html">monoid/pair/min_update_monoid.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/DynamicSetgree_RMQ.test.cpp.html">test/aoj/DynamicSetgree_RMQ.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/LazySegmentTree_RMQ_RAQ.test.cpp.html">test/aoj/LazySegmentTree_RMQ_RAQ.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/LazySegmentTree_RMQ_RUQ.test.cpp.html">test/aoj/LazySegmentTree_RMQ_RUQ.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/RBST_RMQ.test.cpp.html">test/aoj/RBST_RMQ.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/SegmentTree_RMQ.test.cpp.html">test/aoj/SegmentTree_RMQ.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/SegmentTree_RMQ_2.test.cpp.html">test/aoj/SegmentTree_RMQ_2.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
namespace min_monoid_n {
#include "../for_include/monoid_wrapper.cpp"
template<class T>
struct min_monoid_impl {
	T val;
	min_monoid_impl(T v) : val(v) {}
	min_monoid_impl() : val(numeric_limits<T>::max()) {}
	min_monoid_impl<T> operator+(const min_monoid_impl<T>& rhs) const {
		return min_monoid_impl(min(this->val, rhs.val));
	}
};
template<class T, class Impl = min_monoid_impl<T>, class Wrapper = monoid_wrapper<Impl, T>>
struct min_monoid : Wrapper {
	using Wrapper::Wrapper;
};
}
using min_monoid_n::min_monoid;
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "monoid/min_monoid.cpp"
namespace min_monoid_n {
#line 1 "monoid/../for_include/is_addable.cpp"
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
#line 2 "monoid/../for_include/monoid_wrapper.cpp"
struct has_val_impl {
	template <class T>
	static true_type check(decltype(T::val)*);
	template <class T>
	static false_type check(...);
};

template <class T>
class has_val : public decltype(has_val_impl::check<T>(nullptr)) {};

template<class Monoid, class Monoid_Construct_With>
struct monoid_wrapper : public Monoid {
	static_assert(has_val<Monoid>::value, "monoid_wrapper : not found val.");
	struct monoid_tag {};
	using monoid_type = Monoid_Construct_With;
	using Monoid::Monoid;
	monoid_wrapper() = default;
	monoid_wrapper(const Monoid& rhs) {
		this->val = rhs.val;
	}
	static_assert(is_default_constructible<Monoid>::value, "monoid_wrapper : cannot construct(defalut).");
	static_assert(is_constructible<Monoid, Monoid_Construct_With>::value, "monoid_wrapper : cannot construct(Monoid_Construct_With).");
	static_assert(is_addable<Monoid>::value, "monoid_wrapper : not addable (Monoid_Construct_With).");
	static_assert(is_same<decltype(declval<Monoid>()+declval<Monoid>()), Monoid>::value, "monoid_wrapper : cannot +");
};
#line 3 "monoid/min_monoid.cpp"
template<class T>
struct min_monoid_impl {
	T val;
	min_monoid_impl(T v) : val(v) {}
	min_monoid_impl() : val(numeric_limits<T>::max()) {}
	min_monoid_impl<T> operator+(const min_monoid_impl<T>& rhs) const {
		return min_monoid_impl(min(this->val, rhs.val));
	}
};
template<class T, class Impl = min_monoid_impl<T>, class Wrapper = monoid_wrapper<Impl, T>>
struct min_monoid : Wrapper {
	using Wrapper::Wrapper;
};
}
using min_monoid_n::min_monoid;

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

