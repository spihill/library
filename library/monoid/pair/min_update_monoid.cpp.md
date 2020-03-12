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


# :heavy_check_mark: monoid/pair/min_update_monoid.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#8bd1ab4c7cd9516f57d0eb7bdbde5819">monoid/pair</a>
* <a href="{{ site.github.repository_url }}/blob/master/monoid/pair/min_update_monoid.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-12 21:53:19+09:00




## Depends on

* :heavy_check_mark: <a href="../../for_include/is_addable.cpp.html">for_include/is_addable.cpp</a>
* :heavy_check_mark: <a href="../../for_include/is_monoid.cpp.html">for_include/is_monoid.cpp</a>
* :heavy_check_mark: <a href="../../for_include/is_productable.cpp.html">for_include/is_productable.cpp</a>
* :heavy_check_mark: <a href="../../for_include/monoid_pair_wrapper.cpp.html">for_include/monoid_pair_wrapper.cpp</a>
* :heavy_check_mark: <a href="../../for_include/monoid_wrapper.cpp.html">for_include/monoid_wrapper.cpp</a>
* :heavy_check_mark: <a href="../min_monoid.cpp.html">monoid/min_monoid.cpp</a>
* :heavy_check_mark: <a href="../update_monoid.cpp.html">monoid/update_monoid.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../../verify/test/aoj/LazySegmentTree_RMQ_RUQ.test.cpp.html">test/aoj/LazySegmentTree_RMQ_RUQ.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
namespace min_update_monoid_n {
#include "../min_monoid.cpp"
#include "../update_monoid.cpp"
#include "../../for_include/monoid_pair_wrapper.cpp"
template<class T, class U = T, class NODE = min_monoid<T>, class LAZY = update_monoid<U>>
struct min_update_monoid_impl {
	struct Lazy;
	struct Node : public NODE {
		using NODE::operator+;
		using NODE::NODE;
		Node operator+(const Lazy& rhs) const {
			if (rhs.val.second) return *this;
			return Node(rhs.val.first);
		}
	};
	struct Lazy : public LAZY {
		using LAZY::operator+;
		using LAZY::LAZY;
		Lazy operator*(int len) const {
			if (this->val.second) return *this;
			return this->val.first;
		}
	};
};
template<class T, class U = T, class Wrapper = monoid_pair_wrapper<min_update_monoid_impl<T, U>>>
struct min_update_monoid : Wrapper {
	using typename Wrapper::Node;
	using typename Wrapper::Lazy;
	using Wrapper::Wrapper;
};
} // namespace min_update_monoid
using min_update_monoid_n::min_update_monoid;
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "monoid/pair/min_update_monoid.cpp"
namespace min_update_monoid_n {
#line 1 "monoid/pair/../min_monoid.cpp"
namespace min_monoid_n {
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
#line 3 "monoid/pair/../min_monoid.cpp"
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
#line 1 "monoid/pair/../update_monoid.cpp"
namespace update_monoid_n {
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
#line 3 "monoid/pair/../update_monoid.cpp"
template<class T>
struct update_monoid_impl {
	pair<T, char> val;
	update_monoid_impl(T v) : val(v, 0) {}
	update_monoid_impl() : val(T(), 1) {}
	update_monoid_impl<T> operator+(const update_monoid_impl<T>& rhs) const {
		if (rhs.val.second) return *this;
		return rhs;
	}
};
template<class T, class Impl = update_monoid_impl<T>, class Wrapper = monoid_wrapper<Impl, T>>
struct update_monoid : Wrapper {
	using Wrapper::Wrapper;
};
}
using update_monoid_n::update_monoid;
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
#line 5 "monoid/pair/min_update_monoid.cpp"
template<class T, class U = T, class NODE = min_monoid<T>, class LAZY = update_monoid<U>>
struct min_update_monoid_impl {
	struct Lazy;
	struct Node : public NODE {
		using NODE::operator+;
		using NODE::NODE;
		Node operator+(const Lazy& rhs) const {
			if (rhs.val.second) return *this;
			return Node(rhs.val.first);
		}
	};
	struct Lazy : public LAZY {
		using LAZY::operator+;
		using LAZY::LAZY;
		Lazy operator*(int len) const {
			if (this->val.second) return *this;
			return this->val.first;
		}
	};
};
template<class T, class U = T, class Wrapper = monoid_pair_wrapper<min_update_monoid_impl<T, U>>>
struct min_update_monoid : Wrapper {
	using typename Wrapper::Node;
	using typename Wrapper::Lazy;
	using Wrapper::Wrapper;
};
} // namespace min_update_monoid
using min_update_monoid_n::min_update_monoid;

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

