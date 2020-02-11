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


# :heavy_check_mark: monoid/pair/min_plus_monoid.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#8bd1ab4c7cd9516f57d0eb7bdbde5819">monoid/pair</a>
* <a href="{{ site.github.repository_url }}/blob/master/monoid/pair/min_plus_monoid.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-11 22:35:37+09:00




## Depends on

* :heavy_check_mark: <a href="../../for_include/is_addable.cpp.html">for_include/is_addable.cpp</a>
* :heavy_check_mark: <a href="../../for_include/is_monoid.cpp.html">for_include/is_monoid.cpp</a>
* :heavy_check_mark: <a href="../../for_include/monoid.cpp.html">for_include/monoid.cpp</a>
* :heavy_check_mark: <a href="../../for_include/monoid_pair.cpp.html">for_include/monoid_pair.cpp</a>
* :heavy_check_mark: <a href="../min_monoid.cpp.html">monoid/min_monoid.cpp</a>
* :heavy_check_mark: <a href="../plus_monoid.cpp.html">monoid/plus_monoid.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../../verify/test/aoj/LazySegmentTree_RMQ_RAQ.test.cpp.html">test/aoj/LazySegmentTree_RMQ_RAQ.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
namespace min_plus_monoid_n {
#include "../min_monoid.cpp"
#include "../plus_monoid.cpp"
#include "../../for_include/monoid_pair.cpp"
template<class T, class U = T>
struct min_plus_monoid : public monoid_pair_base<min_monoid<T>, plus_monoid<U>> {
	using super = monoid_pair_base<min_monoid<T>, plus_monoid<U>>;
	struct Lazy : public super::Lazy_m {
		Lazy operator*(int len) const {
			return Lazy(this->val);
		}
		bool is_unity() const {
			return this->val == T();
		}
		using super::Lazy_m::operator+;
		using super::Lazy_m::operator=;
		using super::Lazy_m::Lazy_m;
	};
	struct Node : public super::Node_m {
		Node operator+(const Lazy& rhs) const {
			return Node(this->val + rhs.val);
		}
		using super::Node_m::operator+;
		using super::Node_m::operator=;
		using super::Node_m::Node_m;
	};
};
} // namespace min_plus_monoid_n
using min_plus_monoid_n::min_plus_monoid;
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "monoid/pair/min_plus_monoid.cpp"
namespace min_plus_monoid_n {
#line 1 "monoid/pair/../min_monoid.cpp"
namespace min_monoid_n {
#line 1 "monoid/pair/../../for_include/monoid.cpp"
template<class T>
struct monoid_base {
	struct monoid_tag {};
	using monoid_type = T;
	T val;
	monoid_base(T x) : val(x) {}
};
#line 3 "monoid/pair/../min_monoid.cpp"
template<class T>
struct min_monoid : public monoid_base<T> {
	using monoid = min_monoid;
	using monoid_base<T>::monoid_base;
	min_monoid() : min_monoid(numeric_limits<T>::max()) {}
	monoid operator+(const monoid& rhs) const {
		return monoid(min(this->val, rhs.val));
	}
};
}
using min_monoid_n::min_monoid;
#line 1 "monoid/pair/../plus_monoid.cpp"
namespace plus_monoid_n {
#line 1 "monoid/pair/../../for_include/monoid.cpp"
template<class T>
struct monoid_base {
	struct monoid_tag {};
	using monoid_type = T;
	T val;
	monoid_base(T x) : val(x) {}
};
#line 3 "monoid/pair/../plus_monoid.cpp"
template<class T>
struct plus_monoid : public monoid_base<T> {
	using monoid = plus_monoid;
	using monoid_base<T>::monoid_base;
	plus_monoid() : plus_monoid(0) {}
	monoid operator+(const monoid& rhs) const {
		return monoid(this->val + rhs.val);
	}
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
	struct Lazy_m : LAZY {
		using LAZY::LAZY;
		using LAZY::operator+;
		using LAZY::operator=;
		Lazy_m(LAZY x) : LAZY(x) {}
		Lazy_m() : LAZY() {}
	};
	struct Node_m : NODE {
		using NODE::NODE;
		using NODE::operator+;
		using NODE::operator=;
		Node_m(NODE x) : NODE(x) {}
		Node_m() : NODE() {}
	};
};
} // namespace monoid_pair_base
using monoid_pair_n::monoid_pair_base;
#line 5 "monoid/pair/min_plus_monoid.cpp"
template<class T, class U = T>
struct min_plus_monoid : public monoid_pair_base<min_monoid<T>, plus_monoid<U>> {
	using super = monoid_pair_base<min_monoid<T>, plus_monoid<U>>;
	struct Lazy : public super::Lazy_m {
		Lazy operator*(int len) const {
			return Lazy(this->val);
		}
		bool is_unity() const {
			return this->val == T();
		}
		using super::Lazy_m::operator+;
		using super::Lazy_m::operator=;
		using super::Lazy_m::Lazy_m;
	};
	struct Node : public super::Node_m {
		Node operator+(const Lazy& rhs) const {
			return Node(this->val + rhs.val);
		}
		using super::Node_m::operator+;
		using super::Node_m::operator=;
		using super::Node_m::Node_m;
	};
};
} // namespace min_plus_monoid_n
using min_plus_monoid_n::min_plus_monoid;

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

