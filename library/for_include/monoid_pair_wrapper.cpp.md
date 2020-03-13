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


# :warning: for_include/monoid_pair_wrapper.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#8be7b0dfa7a3a788ad1d174f54f0cafd">for_include</a>
* <a href="{{ site.github.repository_url }}/blob/master/for_include/monoid_pair_wrapper.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-12 21:53:19+09:00




## Depends on

* :warning: <a href="is_addable.cpp.html">for_include/is_addable.cpp</a>
* :warning: <a href="is_monoid.cpp.html">for_include/is_monoid.cpp</a>
* :warning: <a href="is_productable.cpp.html">for_include/is_productable.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "is_monoid.cpp"
#include "is_addable.cpp"
#include "is_productable.cpp"
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
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "for_include/is_monoid.cpp"
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
#line 1 "for_include/is_productable.cpp"
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
#line 4 "for_include/monoid_pair_wrapper.cpp"
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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

