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
    - Last commit date: 2020-03-12 21:53:19+09:00




## Depends on

* :heavy_check_mark: <a href="../../for_include/is_addable.cpp.html">for_include/is_addable.cpp</a>
* :heavy_check_mark: <a href="../../for_include/is_monoid.cpp.html">for_include/is_monoid.cpp</a>
* :heavy_check_mark: <a href="../../for_include/is_productable.cpp.html">for_include/is_productable.cpp</a>
* :heavy_check_mark: <a href="../../for_include/monoid_pair_wrapper.cpp.html">for_include/monoid_pair_wrapper.cpp</a>
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
#include "../plus_monoid.cpp"
#include "../affine_monoid.cpp"
#include "../../for_include/monoid_pair_wrapper.cpp"
template<class T, class U = T, class NODE = plus_monoid<T>, class LAZY = affine_monoid<U>>
struct plus_affine_monoid_impl {
	struct Lazy;
	struct Node : public NODE {
		using NODE::operator+;
		using NODE::NODE;
		Node operator+(const Lazy& rhs) const {
			return Node(this->val * rhs.val.first + rhs.val.second);
		}
	};
	struct Lazy : public LAZY {
		using LAZY::operator+;
		using LAZY::LAZY;
		inline Lazy operator*(int len) const {
			return Lazy(make_pair(this->val.first, this->val.second * len));
		}
	};
};
template<class T, class U = T, class Wrapper = monoid_pair_wrapper<plus_affine_monoid_impl<T, U>>>
struct plus_affine_monoid : Wrapper {
	using typename Wrapper::Node;
	using typename Wrapper::Lazy;
	using Wrapper::Wrapper;
};
} // namespace plus_update_monoid
using plus_affine_monoid_n::plus_affine_monoid;
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "monoid/pair/plus_affine_monoid.cpp"
namespace plus_affine_monoid_n {
#line 1 "monoid/pair/../plus_monoid.cpp"
namespace plus_monoid_n {
#line 1 "monoid/pair/../../for_include/is_addable.cpp"
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
#line 2 "monoid/pair/../../for_include/monoid_wrapper.cpp"
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
#line 1 "monoid/pair/../affine_monoid.cpp"
namespace affine_monoid_n {
#line 1 "monoid/pair/../../for_include/is_addable.cpp"
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
#line 2 "monoid/pair/../../for_include/monoid_wrapper.cpp"
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
#line 3 "monoid/pair/../affine_monoid.cpp"
template<class T>
struct affine_monoid_impl {
	pair<T, T> val;
	affine_monoid_impl(pair<T, T> v) : val(v) {}
	affine_monoid_impl() : affine_monoid_impl(pair<T, T>(1, 0)) {}
	affine_monoid_impl<T> operator+(const affine_monoid_impl& rhs) const {
		return affine_monoid_impl(pair<T, T>(rhs.val.first * this->val.first, rhs.val.first * this->val.second + rhs.val.second));
	}
};
template<class T, class Impl = affine_monoid_impl<T>, class Wrapper = monoid_wrapper<Impl, pair<T, T>>>
struct affine_monoid : Wrapper {
	using Wrapper::Wrapper;
};
}
using affine_monoid_n::affine_monoid;

// namespace update_monoid_n {
// #include "../for_include/monoid_wrapper.cpp"
// template<class T>
// struct update_monoid_impl {
// 	pair<T, char> val;
// 	update_monoid_impl(T v) : val(v, 0) {}
// 	update_monoid_impl() : val(T(), 1) {}
// 	update_monoid_impl<T> operator+(const update_monoid_impl<T>& rhs) const {
// 		if (rhs.val.second) return *this;
// 		return rhs;
// 	}
// };
// template<class T, class Impl = update_monoid_impl<T>, class Wrapper = monoid_wrapper<Impl, T>>
// struct update_monoid : Wrapper {
// 	using Wrapper::Wrapper;
// };
// }
// using update_monoid_n::update_monoid;
#line 1 "monoid/pair/../../for_include/is_monoid.cpp"
namespace is_monoid_n {
template <class T>
class is_monoid {
	template <class U> static constexpr true_type check(typename U::monoid_tag*);
	template <class U> static constexpr false_type check(...);
public:
	static constexpr bool value = decltype(check<T>(nullptr))::value;
};
template <class T> constexpr bool is_monoid_v = is_monoid<T>::value;
} // namespace is_monoid_n
using is_monoid_n::is_monoid;
using is_monoid_n::is_monoid_v;
#line 1 "monoid/pair/../../for_include/is_addable.cpp"
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
#line 1 "monoid/pair/../../for_include/is_productable.cpp"
namespace is_productable_n {
template <class T1, class T2 = T1>
class is_productable {
	template <class U1, class U2> static constexpr auto check(U1*, U2*) -> decltype(
		declval<U1>() * declval<U2>(), true_type()
	);
	template <class U1, class U2> static constexpr auto check(...) -> false_type;
public:
	static constexpr bool value = decltype(check<T1, T2>(nullptr, nullptr))::value;
};
template <class T, class U = T>
constexpr bool is_productable_v = is_productable<T, U>::value;
} // namespace is_productable_n
using is_productable_n::is_productable;
using is_productable_n::is_productable_v;
#line 4 "monoid/pair/../../for_include/monoid_pair_wrapper.cpp"
template <class T>
class has_Node {
	template <class U> static constexpr bool check(typename U::Node*) { return true;}
	template <class U> static constexpr bool check(...) { return false;}
public:
	static constexpr bool value = check<T>(nullptr);
};
template <class T>
class has_Lazy {
	template <class U> static constexpr bool check(typename U::Lazy*) { return true;}
	template <class U> static constexpr bool check(...) { return false;}
public:
	static constexpr bool value = check<T>(nullptr);
};
template<class MonoidPair>
struct monoid_pair_wrapper {
	using Node = typename MonoidPair::Node;
	using Lazy = typename MonoidPair::Lazy;
	static_assert(has_Node<MonoidPair>::value, "monoid_pair_wrapper : not have Node");
	static_assert(has_Lazy<MonoidPair>::value, "monoid_pair_wrapper : not have Lazy");
	static_assert(is_monoid_v<Node>, "monoid_pair_wrapper : Node is not monoid");
	static_assert(is_monoid_v<Lazy>, "monoid_pair_wrapper : Lazy is not monoid");
	static_assert(is_addable_v<Node, Lazy>, "monoid_pair_wrapper : cannot Node + Lazy");
	static_assert(is_productable_v<Lazy, int>, "monoid_pair_wrapper : cannot Lazy * int");
	struct monoid_pair_tag {};
};
#line 5 "monoid/pair/plus_affine_monoid.cpp"
template<class T, class U = T, class NODE = plus_monoid<T>, class LAZY = affine_monoid<U>>
struct plus_affine_monoid_impl {
	struct Lazy;
	struct Node : public NODE {
		using NODE::operator+;
		using NODE::NODE;
		Node operator+(const Lazy& rhs) const {
			return Node(this->val * rhs.val.first + rhs.val.second);
		}
	};
	struct Lazy : public LAZY {
		using LAZY::operator+;
		using LAZY::LAZY;
		inline Lazy operator*(int len) const {
			return Lazy(make_pair(this->val.first, this->val.second * len));
		}
	};
};
template<class T, class U = T, class Wrapper = monoid_pair_wrapper<plus_affine_monoid_impl<T, U>>>
struct plus_affine_monoid : Wrapper {
	using typename Wrapper::Node;
	using typename Wrapper::Lazy;
	using Wrapper::Wrapper;
};
} // namespace plus_update_monoid
using plus_affine_monoid_n::plus_affine_monoid;

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

