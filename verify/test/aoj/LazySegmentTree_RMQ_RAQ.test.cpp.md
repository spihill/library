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


# :heavy_check_mark: test/aoj/LazySegmentTree_RMQ_RAQ.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#0d0c91c0cca30af9c1c9faef0cf04aa9">test/aoj</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/LazySegmentTree_RMQ_RAQ.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-12 20:22:45+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_H">https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_H</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/datastructure/SegmentTree/LazySegmentTree.cpp.html">遅延伝播セグメント木</a>
* :heavy_check_mark: <a href="../../../library/for_include/is_addable.cpp.html">for_include/is_addable.cpp</a>
* :heavy_check_mark: <a href="../../../library/for_include/is_monoid.cpp.html">for_include/is_monoid.cpp</a>
* :heavy_check_mark: <a href="../../../library/for_include/monoid_pair.cpp.html">for_include/monoid_pair.cpp</a>
* :heavy_check_mark: <a href="../../../library/for_include/monoid_wrapper.cpp.html">for_include/monoid_wrapper.cpp</a>
* :heavy_check_mark: <a href="../../../library/monoid/min_monoid.cpp.html">monoid/min_monoid.cpp</a>
* :heavy_check_mark: <a href="../../../library/monoid/pair/min_plus_monoid.cpp.html">monoid/pair/min_plus_monoid.cpp</a>
* :heavy_check_mark: <a href="../../../library/monoid/plus_monoid.cpp.html">monoid/plus_monoid.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_H"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/SegmentTree/LazySegmentTree.cpp"
#include "../../monoid/pair/min_plus_monoid.cpp"
using ll = long long;
using monoids = min_plus_monoid<ll>;

int main() {
	int n, Q;
	cin >> n >> Q;
	LazySegmentTree<monoids> L;
	L.build(vector<ll>(n, 0));
	while (Q--) {
		int q;
		cin >> q;
		if (q == 0) {
			int s, t, x; cin >> s >> t >> x;
			L.set(s, t+1, x);
		} else {
			int s, t; cin >> s >> t;
			cout << L.get(s, t+1) << endl;
		}
	}
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj/LazySegmentTree_RMQ_RAQ.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_H"

#include<bits/stdc++.h>

using namespace std;

#line 1 "test/aoj/../../datastructure/SegmentTree/LazySegmentTree.cpp"
/**
 * @title 遅延伝播セグメント木
 * @brief 0-indexed 半開区間
 * @brief MonoidPair はクラス Node と クラス Lazy を持つ。
 * @brief クラス Node と Lazy は Monoid であり、{型(monoid_type), 演算(operator+), 単位元(default constructor), constructor(monoid_type)} の4つを持つ。
 * @brief クラス Lazy は {operator*(int), is_unity()} も持つ。
 * @brief クラス Node は operator+(const Lazy&) も持つ。
 * @brief MonoidPair の具体例は monoid/pair/ にある。
 */
template<class MonoidPair>
struct LazySegmentTree {
	int n;
	using Node = typename MonoidPair::Node; using Node_T = typename MonoidPair::Node::monoid_type;
	using Lazy = typename MonoidPair::Lazy; using Lazy_T = typename MonoidPair::Lazy::monoid_type;
	vector<Node> node;
	vector<Lazy> lazy;
	// @brief サイズ N で初期化(初期値は単位元) $O(N)$
	LazySegmentTree (int N) {build(N);}
	// @brief vector で初期化 $O(N)$
	LazySegmentTree (const vector<Node_T>& v) {build(v);}
	LazySegmentTree () {}
	// @brief (a, b] に x を遅延伝播 $O(\log N)$
	void set(int a, int b, Lazy_T x) {set(a, b, x, 0, 0, n);}
	// @brief (a, b] を取得 $O(\log N)$
	Node_T get(int a, int b) {return get(a, b, 0, 0, n).val;}
	// @brief index i を取得 $O(\log N)$
	Node_T operator[](int i) {
		return get(i, i+1);
	}
	// @brief サイズ N で再構築(初期値は単位元) $O(N)$
	void build(int n_) {
		n = calc_n(n_);
		node.clear(); node.resize(2*n-1);
		lazy.clear(); lazy.resize(2*n-1);
	}
	// @brief vector で再構築 $O(N)$
	void build(const vector<Node_T>& v) {
		build(v.size());
		for (size_t i = 0; i < v.size(); i++) {
			node[i+n-1].val = v[i];
		}
		for (int i = n - 2; i >= 0; i--){
			node[i] = node[i*2+1] + node[i*2+2];
		}
	}
private:
	void eval(int len, int k) {
		if (2*k+1 < 2*n-1) {
			lazy[2*k+1] = lazy[2*k+1] + lazy[k];
			lazy[2*k+2] = lazy[2*k+2] + lazy[k];
		}
		node[k] = node[k] + lazy[k] * len;
		lazy[k] = Lazy();
	}
	Node set(int a, int b, Lazy_T x, int k, int l, int r) {
		eval(r-l, k);
		if (r <= a || b <= l) return node[k];
		if (a <= l && r <= b) {
			lazy[k] = lazy[k] + Lazy(x);
			return node[k] + lazy[k] * (r-l);
		}
		return node[k] = set(a, b, x, 2*k+1, l, (l+r) / 2) + set(a, b, x, 2*k+2, (l+r) / 2, r);
	}
	Node get(int a, int b, int k, int l, int r) {
		eval(r-l, k);
		if (a <= l && r <= b) {
			return node[k];
		} else if (b <= l || r <= a) {
			return Node();
		}
		return get(a, b, 2*k+1, l, (l+r) / 2) + get(a, b, 2*k+2, (l+r) / 2, r);
	}
	int calc_n(int n_, int t = 1) {return n_ > t ? calc_n(n_, t << 1) : t;}
};
#line 1 "test/aoj/../../monoid/pair/min_plus_monoid.cpp"
namespace min_plus_monoid_n {
#line 1 "test/aoj/../../monoid/pair/../min_monoid.cpp"
namespace min_monoid_n {
#line 1 "test/aoj/../../monoid/pair/../../for_include/monoid_wrapper.cpp"
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
#line 3 "test/aoj/../../monoid/pair/../min_monoid.cpp"
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
#line 1 "test/aoj/../../monoid/pair/../plus_monoid.cpp"
namespace plus_monoid_n {
#line 1 "test/aoj/../../monoid/pair/../../for_include/monoid_wrapper.cpp"
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
#line 3 "test/aoj/../../monoid/pair/../plus_monoid.cpp"
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
#line 2 "test/aoj/../../monoid/pair/../../for_include/monoid_pair.cpp"
using namespace std;
namespace monoid_pair_n {
#line 1 "test/aoj/../../monoid/pair/../../for_include/../for_include/is_monoid.cpp"
namespace is_monoid_n {
#line 1 "test/aoj/../../monoid/pair/../../for_include/../for_include/is_addable.cpp"
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
#line 3 "test/aoj/../../monoid/pair/../../for_include/../for_include/is_monoid.cpp"
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
#line 5 "test/aoj/../../monoid/pair/../../for_include/monoid_pair.cpp"
template<class NODE, class LAZY>
struct monoid_pair_base {
	static_assert(is_monoid_v<NODE> && is_monoid_v<LAZY>, "");
	struct monoid_pair_tag {};
	using Lazy = LAZY;
	using Node = NODE;
};
} // namespace monoid_pair_base
using monoid_pair_n::monoid_pair_base;
#line 5 "test/aoj/../../monoid/pair/min_plus_monoid.cpp"
template<class T, class U = T>
struct min_plus_monoid : public monoid_pair_base<min_monoid<T>, plus_monoid<U>> {
	using super = monoid_pair_base<min_monoid<T>, plus_monoid<U>>;
	struct Lazy;
	struct Node : public super::Node {
		using super::Node::operator+;
		using super::Node::Node;
		Node operator+(const Lazy& rhs) const {
			return Node(this->val + rhs.val);
		}
	};
	struct Lazy : public super::Lazy {
		using super::Lazy::operator+;
		using super::Lazy::Lazy;
		Lazy operator*(int len) const {
			return Lazy(this->val);
		}
	};
};
} // namespace min_plus_monoid_n
using min_plus_monoid_n::min_plus_monoid;
#line 9 "test/aoj/LazySegmentTree_RMQ_RAQ.test.cpp"
using ll = long long;
using monoids = min_plus_monoid<ll>;

int main() {
	int n, Q;
	cin >> n >> Q;
	LazySegmentTree<monoids> L;
	L.build(vector<ll>(n, 0));
	while (Q--) {
		int q;
		cin >> q;
		if (q == 0) {
			int s, t, x; cin >> s >> t >> x;
			L.set(s, t+1, x);
		} else {
			int s, t; cin >> s >> t;
			cout << L.get(s, t+1) << endl;
		}
	}
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

