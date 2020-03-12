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


# :heavy_check_mark: monoid/pair/plus_affine_monoid.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#8bd1ab4c7cd9516f57d0eb7bdbde5819">monoid/pair</a>
* <a href="{{ site.github.repository_url }}/blob/master/monoid/pair/plus_affine_monoid.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-12 20:22:45+09:00




## Depends on

* :heavy_check_mark: <a href="../../for_include/is_addable.cpp.html">for_include/is_addable.cpp</a>
* :heavy_check_mark: <a href="../../for_include/is_monoid.cpp.html">for_include/is_monoid.cpp</a>
* :heavy_check_mark: <a href="../../for_include/monoid.cpp.html">for_include/monoid.cpp</a>
* :heavy_check_mark: <a href="../../for_include/monoid_pair.cpp.html">for_include/monoid_pair.cpp</a>
* :heavy_check_mark: <a href="../../for_include/monoid_wrapper.cpp.html">for_include/monoid_wrapper.cpp</a>
* :heavy_check_mark: <a href="../affine_monoid.cpp.html">monoid/affine_monoid.cpp</a>
* :heavy_check_mark: <a href="../plus_monoid.cpp.html">monoid/plus_monoid.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../../verify/test/yosupo/LazySegTree_Plus_Affine.test.cpp.html">test/yosupo/LazySegTree_Plus_Affine.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
namespace plus_affine_monoid_n {
#include "../affine_monoid.cpp"
#include "../plus_monoid.cpp"
#include "../../for_include/monoid_pair.cpp"
template<class T, class U = T>
struct plus_affine_monoid : public monoid_pair_base<plus_monoid<T>, affine_monoid<U>> {
	using super = monoid_pair_base<plus_monoid<T>, affine_monoid<U>>;
	struct Lazy;
	struct Node : public super::Node {
		using super::Node::operator+;
		using super::Node::Node;
		Node operator+(const Lazy& rhs) const {
			return Node(this->val * rhs.val.first + rhs.val.second);
		}
	};
	struct Lazy : public super::Lazy {
		using super::Lazy::operator+;
		using super::Lazy::operator=;
		using super::Lazy::Lazy;
		inline Lazy operator*(int len) const {
			return Lazy(make_pair(this->val.first, this->val.second * len));
		}
	};
};
} // namespace plus_affine_monoid_n
using plus_affine_monoid_n::plus_affine_monoid;
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "monoid/pair/plus_affine_monoid.cpp"
namespace plus_affine_monoid_n {
#line 1 "monoid/pair/../affine_monoid.cpp"
namespace affine_monoid_n {
#line 1 "monoid/pair/../../for_include/monoid.cpp"
template<class T>
struct monoid_base {
	struct monoid_tag {};
	using monoid_type = T;
	T val;
	monoid_base(T x) : val(x) {}
};
#line 3 "monoid/pair/../affine_monoid.cpp"
template<class T>
struct affine_monoid : public monoid_base<pair<T, T>> {
	using monoid = affine_monoid;
	using monoid_base<pair<T, T>>::monoid_base;
	affine_monoid() : affine_monoid(pair<T, T>(1, 0)) {}
	monoid operator+(const monoid& rhs) const {
		return monoid(pair<T, T>(rhs.val.first * this->val.first, rhs.val.first * this->val.second + rhs.val.second));
	}
};
}
using affine_monoid_n::affine_monoid;
#line 1 "monoid/pair/../plus_monoid.cpp"
namespace plus_monoid_n {
#line 1 "monoid/pair/../../for_include/monoid_wrapper.cpp"
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
#line 3 "monoid/pair/../plus_monoid.cpp"
template<class T>
struct plus_monoid_impl {
	T val;
	plus_monoid_impl(T v) : val(v) {}
	plus_monoid_impl() : plus_monoid_impl(0) {}
	plus_monoid_impl<T> operator+(const plus_monoid_impl<T>& rhs) const {
		return plus_monoid_impl(this->val + rhs.val);
	}
};
template<class T, class Impl = plus_monoid_impl<T>, class Wrapper = monoid_wrapper<Impl, T>>
struct plus_monoid : Wrapper {
	using Wrapper::Wrapper;
};
}
using plus_monoid_n::plus_monoid;
#line 1 "monoid/pair/../../for_include/monoid_pair.cpp"
#include <bits/stdc++.h>
using namespace std;
namespace monoid_pair_n {
#line 1 "monoid/pair/../../for_include/../for_include/is_monoid.cpp"
namespace is_monoid_n {
#line 1 "monoid/pair/../../for_include/../for_include/is_addable.cpp"
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
#line 3 "monoid/pair/../../for_include/../for_include/is_monoid.cpp"
template <class T>
class is_monoid {
	template <class U> static constexpr true_type check(typename U::monoid_tag*);
	template <class U> static constexpr false_type check(...);
public:
	static constexpr bool value = decltype(check<T>(nullptr))::value && is_addable_v<T>;
};
template <class T> constexpr bool is_monoid_v = is_monoid<T>::value;
} // namespace is_monoid_n
using is_monoid_n::is_monoid;
using is_monoid_n::is_monoid_v;
#line 5 "monoid/pair/../../for_include/monoid_pair.cpp"
template<class NODE, class LAZY>
struct monoid_pair_base {
	static_assert(is_monoid_v<NODE> && is_monoid_v<LAZY>, "");
	struct monoid_pair_tag {};
	using Lazy = LAZY;
	using Node = NODE;
};
} // namespace monoid_pair_base
using monoid_pair_n::monoid_pair_base;
#line 5 "monoid/pair/plus_affine_monoid.cpp"
template<class T, class U = T>
struct plus_affine_monoid : public monoid_pair_base<plus_monoid<T>, affine_monoid<U>> {
	using super = monoid_pair_base<plus_monoid<T>, affine_monoid<U>>;
	struct Lazy;
	struct Node : public super::Node {
		using super::Node::operator+;
		using super::Node::Node;
		Node operator+(const Lazy& rhs) const {
			return Node(this->val * rhs.val.first + rhs.val.second);
		}
	};
	struct Lazy : public super::Lazy {
		using super::Lazy::operator+;
		using super::Lazy::operator=;
		using super::Lazy::Lazy;
		inline Lazy operator*(int len) const {
			return Lazy(make_pair(this->val.first, this->val.second * len));
		}
	};
};
} // namespace plus_affine_monoid_n
using plus_affine_monoid_n::plus_affine_monoid;

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

