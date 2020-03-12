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


# :heavy_check_mark: test/aoj/SegmentTree_RSQ.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#0d0c91c0cca30af9c1c9faef0cf04aa9">test/aoj</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/SegmentTree_RSQ.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-12 20:22:45+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B">https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/datastructure/SegmentTree/SegmentTree.cpp.html">セグメント木</a>
* :heavy_check_mark: <a href="../../../library/for_include/is_addable.cpp.html">for_include/is_addable.cpp</a>
* :heavy_check_mark: <a href="../../../library/for_include/is_monoid.cpp.html">for_include/is_monoid.cpp</a>
* :heavy_check_mark: <a href="../../../library/for_include/monoid_wrapper.cpp.html">for_include/monoid_wrapper.cpp</a>
* :heavy_check_mark: <a href="../../../library/monoid/plus_monoid.cpp.html">monoid/plus_monoid.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/SegmentTree/SegmentTree.cpp"
#include "../../monoid/plus_monoid.cpp"

int main() {
	int N, Q;
	scanf("%d %d", &N, &Q);
	vector<long long> v(N, 0);
	SegmentTree<plus_monoid<long long>> S(v);
	while (Q--) {
		int q, x, y;
		scanf("%d %d %d", &q, &x, &y);
		if (q == 0) {
			x--;
			S.set(x, S[x] + y);
		} else {
			x--;
			y--;
			printf("%lld\n", S.get(x, y+1));
		}
	}
	return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj/SegmentTree_RSQ.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B"

#include<bits/stdc++.h>

using namespace std;

#line 1 "test/aoj/../../datastructure/SegmentTree/SegmentTree.cpp"
/**
 * @title セグメント木
 * @brief 0-indexed 半開区間
 * @brief クラス Node は Monoid であり、{型(monoid_type), 演算(operator+), 単位元(default constructor), constructor(monoid_type)} の4つを持つ。
 * @brief Node の具体例は monoid/ にある。
 */
namespace segmenttree_n {
#line 1 "test/aoj/../../datastructure/SegmentTree/../../for_include/is_monoid.cpp"
namespace is_monoid_n {
#line 1 "test/aoj/../../datastructure/SegmentTree/../../for_include/is_addable.cpp"
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
#line 3 "test/aoj/../../datastructure/SegmentTree/../../for_include/is_monoid.cpp"
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
#line 9 "test/aoj/../../datastructure/SegmentTree/SegmentTree.cpp"
template<class Node>
struct SegmentTree {
	static_assert(is_monoid_v<Node>, "");
	using Node_T = typename Node::monoid_type;
	using index_type = uint_fast32_t;
	index_type n;
	vector<Node> node;
	// @brief サイズ N で初期化(初期値は単位元) $O(N)$
	SegmentTree (index_type N) {build(N);}
	// @brief vector で初期化 $O(N)$
	SegmentTree (const vector<Node_T>& v) {build(v);}
	// @brief サイズ N で再構築(初期値は単位元) $O(N)$
	void build(index_type N) {
		n = calc_n(N);
		node.clear(); node.resize(2*n-1);
	}
	// @brief vector で再構築 $O(N)$
	void build(const vector<Node_T>& v) {
		build(index_type(v.size()));
		for (size_t i = 0; i < v.size(); i++) {
			node[i+n-1].val = v[i];
		}
		for (int i = n - 2; i >= 0; i--){
			node[i] = node[i*2+1] + node[i*2+2];
		}
	}
	// @brief index i に v を代入 $O(\log N)$
	void set(index_type i, Node_T v) {
		i += n - 1;
		node[i].val = move(v);
		while (i) {
			i = (i-1) / 2;
			node[i] = node[i*2+1] + node[i*2+2];
		}
	}
	// @brief [l, r) を取得 $O(\log N)$
	Node_T get(index_type l, index_type r) {
		Node val_l, val_r;
		for (l += n-1, r += n-1; l < r; l /= 2, r = (r - 1) / 2) {
			if (l % 2 == 0) val_l = val_l + node[l];
			if (r % 2 == 0) val_r = node[r-1] + val_r;
		}
		return (val_l + val_r).val;
	}
	// @brief index i を取得 $O(\log N)$
	const Node_T& operator[](index_type i) {
		return node[i+n-1].val;
	}
private:
	index_type calc_n(index_type n_, index_type t = 1) {return n_ > t ? calc_n(n_, t << 1) : t;}
};
} // namespace segmenttree_n
using segmenttree_n::SegmentTree;
#line 1 "test/aoj/../../monoid/plus_monoid.cpp"
namespace plus_monoid_n {
#line 1 "test/aoj/../../monoid/../for_include/monoid_wrapper.cpp"
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
#line 3 "test/aoj/../../monoid/plus_monoid.cpp"
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
#line 9 "test/aoj/SegmentTree_RSQ.test.cpp"

int main() {
	int N, Q;
	scanf("%d %d", &N, &Q);
	vector<long long> v(N, 0);
	SegmentTree<plus_monoid<long long>> S(v);
	while (Q--) {
		int q, x, y;
		scanf("%d %d %d", &q, &x, &y);
		if (q == 0) {
			x--;
			S.set(x, S[x] + y);
		} else {
			x--;
			y--;
			printf("%lld\n", S.get(x, y+1));
		}
	}
	return 0;
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

