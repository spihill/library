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


# :heavy_check_mark: monoid/max_monoid.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c3437aaac8e99d51d51e80f390e49b05">monoid</a>
* <a href="{{ site.github.repository_url }}/blob/master/monoid/max_monoid.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-12 20:22:45+09:00




## Depends on

* :heavy_check_mark: <a href="../for_include/monoid_wrapper.cpp.html">for_include/monoid_wrapper.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/SegmentTree_RMQ_2.test.cpp.html">test/aoj/SegmentTree_RMQ_2.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
namespace max_monoid_n {
#include "../for_include/monoid_wrapper.cpp"
template<class T>
struct max_monoid_impl {
	T val;
	max_monoid_impl(T v) : val(v) {}
	max_monoid_impl() : val(numeric_limits<T>::min()) {}
	max_monoid_impl<T> operator+(const max_monoid_impl<T>& rhs) const {
		return max_monoid_impl(max(this->val, rhs.val));
	}
};
template<class T, class Impl = max_monoid_impl<T>, class Wrapper = monoid_wrapper<Impl, T>>
struct max_monoid : Wrapper {
	using Wrapper::Wrapper;
};
}
using max_monoid_n::max_monoid;
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "monoid/max_monoid.cpp"
namespace max_monoid_n {
#line 1 "monoid/../for_include/monoid_wrapper.cpp"
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
	static_assert(is_same<decltype(declval<Monoid>()+declval<Monoid>()), Monoid>::value, "monoid_wrapper : cannot +");
};
#line 3 "monoid/max_monoid.cpp"
template<class T>
struct max_monoid_impl {
	T val;
	max_monoid_impl(T v) : val(v) {}
	max_monoid_impl() : val(numeric_limits<T>::min()) {}
	max_monoid_impl<T> operator+(const max_monoid_impl<T>& rhs) const {
		return max_monoid_impl(max(this->val, rhs.val));
	}
};
template<class T, class Impl = max_monoid_impl<T>, class Wrapper = monoid_wrapper<Impl, T>>
struct max_monoid : Wrapper {
	using Wrapper::Wrapper;
};
}
using max_monoid_n::max_monoid;

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

