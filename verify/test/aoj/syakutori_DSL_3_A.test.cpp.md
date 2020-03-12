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


# :heavy_check_mark: test/aoj/syakutori_DSL_3_A.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#0d0c91c0cca30af9c1c9faef0cf04aa9">test/aoj</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/syakutori_DSL_3_A.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-12 20:38:33+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/3/DSL_3_A">https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/3/DSL_3_A</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/algorithm/syakutori.cpp.html">尺取り法</a>
* :heavy_check_mark: <a href="../../../library/datastructure/SWAG.cpp.html">SWAG (Sliding Window Aggregation)</a>
* :heavy_check_mark: <a href="../../../library/for_include/is_addable.cpp.html">for_include/is_addable.cpp</a>
* :heavy_check_mark: <a href="../../../library/for_include/monoid_wrapper.cpp.html">for_include/monoid_wrapper.cpp</a>
* :heavy_check_mark: <a href="../../../library/monoid/plus_monoid.cpp.html">monoid/plus_monoid.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/3/DSL_3_A"

#include <bits/stdc++.h>
using namespace std;

#include "../../algorithm/syakutori.cpp"
#include "../../monoid/plus_monoid.cpp"

using monoid = plus_monoid<int>;

int main() {
	int N, S; cin >> N >> S;
	vector<monoid> a(N);
	for (int i = 0; i < N; i++) cin >> a[i].val;
	auto r = syakutori<monoid>(a, [&](auto sum) {
		return sum >= S;
	}, false);
	int res = N + 1;
	for (int l = 0; l < N && r[l] <= N; l++) {
		res = min(res, r[l] - l);
	}
	if (res == N + 1) res = 0;
	cout << res << endl;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj/syakutori_DSL_3_A.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/3/DSL_3_A"

#include <bits/stdc++.h>
using namespace std;

#line 1 "test/aoj/../../algorithm/../datastructure/SWAG.cpp"
/**
 * @title SWAG (Sliding Window Aggregation)
 * @brief 本来 SWAG は半群を扱うことができるが、これは Monoid を扱う。queue が空の時には単位元を返す。
 */
template<class Monoid>
struct SWAG {
	using Monoid_T = typename Monoid::monoid_type;
	struct node {
		Monoid val, sum;
		node() : val(), sum() {}
		node(Monoid_T v, Monoid_T s) : val(v), sum(s) {}
		node(Monoid v, Monoid s) : val(v), sum(s) {}
	};
	stack<node> F, B;
	// @brief queue の中の和をとる $O(1)$
	Monoid_T fold_all() const {
		if (empty()) return Monoid().val;
		if (F.empty()) return B.top().sum.val;
		if (B.empty()) return F.top().sum.val;
		return (F.top().sum + B.top().sum).val;
	}
	void push(Monoid x) {
		if (B.empty()) B.emplace(x, x);
		else {
			Monoid s{B.top().sum + x};
			B.emplace(x, move(s));
		}
	}
	// @brief queue の末尾に要素を push $O(1)$
	void push(Monoid_T x) {
		push(Monoid(x));
	}
	// @brief queue の先頭の要素を pop ならし $O(1)$
	void pop() {
		assert(!empty());
		if (F.empty()) {
			F.emplace(B.top().val, B.top().val); B.pop();
			while (B.size()) {
				F.emplace(B.top().val, B.top().val + F.top().sum);
				B.pop();
			}
		}
		F.pop();
	}
	bool empty() const {
		return size() == 0;
	}
	uint_fast32_t size() const {
		return F.size() + B.size();
	}
};
#line 2 "test/aoj/../../algorithm/syakutori.cpp"
/**
 * @title 尺取り法
 * @brief SWAG を利用して Monoid の列に対して尺取り法を行う。
 * v : 対象の列 (型が monoid_type を持つ必要がある)
 * f : 区間が満たすべき条件を表す関数 (引数 : T::monoid_type 戻り値 : bool)
 * continue_flag (default : true) : f の戻り値が continue_flag と等しいような区間を列挙
 * 戻り値 : ret[l] = r; (条件を満たす区間 [l, i) の中で最大の i が r)
 */
template<class T>
vector<int> syakutori(const vector<T>& v, const function<bool(typename T::monoid_type)>& f, bool continue_flag = true) {
	SWAG<T> S;
	int l = 0, r = 0;
	const int N = v.size();
	vector<int> res(N);
	if (continue_flag) {
		while (l < N) {
			while (r < N && f((T(S.fold_all()) + v[r]).val)) S.push(v[r++]);
			 res[l++] = r;
			if (r < l) r++;
			else S.pop();
		}
	} else {
		while (l < N) {
			while (r < N && !f(S.fold_all())) S.push(v[r++]);
			if (r == N && !f(S.fold_all())) {
				for (; l < N; l++) res[l] = N + 1;
				break;
			}
			res[l++] = r;
			if (r < l) r++;
			else S.pop();
		}
	}
	return move(res);
}
#line 1 "test/aoj/../../monoid/plus_monoid.cpp"
namespace plus_monoid_n {
#line 1 "test/aoj/../../monoid/../for_include/is_addable.cpp"
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
#line 2 "test/aoj/../../monoid/../for_include/monoid_wrapper.cpp"
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
#line 8 "test/aoj/syakutori_DSL_3_A.test.cpp"

using monoid = plus_monoid<int>;

int main() {
	int N, S; cin >> N >> S;
	vector<monoid> a(N);
	for (int i = 0; i < N; i++) cin >> a[i].val;
	auto r = syakutori<monoid>(a, [&](auto sum) {
		return sum >= S;
	}, false);
	int res = N + 1;
	for (int l = 0; l < N && r[l] <= N; l++) {
		res = min(res, r[l] - l);
	}
	if (res == N + 1) res = 0;
	cout << res << endl;
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

