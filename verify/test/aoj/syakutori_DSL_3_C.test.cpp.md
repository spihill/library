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


# :x: test/aoj/syakutori_DSL_3_C.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/syakutori_DSL_3_C.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-17 12:39:37+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/3/DSL_3_C">https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/3/DSL_3_C</a>


## Depends on

* :x: <a href="../../../library/algorithm/syakutori.cpp.html">尺取り法</a>
* :x: <a href="../../../library/datastructure/SWAG.cpp.html">SWAG (Sliding Window Aggregation)</a>
* :heavy_check_mark: <a href="../../../library/monoid/plus_monoid.cpp.html">monoid/plus_monoid.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/3/DSL_3_C"

#include <bits/stdc++.h>
using namespace std;

#include "../../algorithm/syakutori.cpp"

#include "../../monoid/plus_monoid.cpp"

using monoid = plus_monoid<long long>;

int main() {
	int N, Q; cin >> N >> Q;
	vector<monoid> a(N);
	for (int i = 0; i < N; i++) cin >> a[i];
	while (Q--) {
		long long x; cin >> x;
		auto r = syakutori<monoid>(a, [&](auto n) {
			return n <= x;
		});
		long long res = 0;
		for (int l = 0; l < N; l++) res += r[l] - l;
		cout << res << endl;
	}
	return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj/syakutori_DSL_3_C.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/3/DSL_3_C"

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
};#line 2 "test/aoj/../../algorithm/syakutori.cpp"
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
}#line 7 "test/aoj/syakutori_DSL_3_C.test.cpp"

#line 1 "test/aoj/../../monoid/plus_monoid.cpp"
template<class T>
struct plus_monoid {
	using mono = plus_monoid;
	plus_monoid() : plus_monoid(T()) {}
	explicit plus_monoid(T x) : val(x) {}
	T val;
	mono operator+(const mono& rhs) const {
		return mono(val + rhs.val);
	}
	friend istream& operator>>(istream& lhs, mono& rhs) {
		lhs >> rhs.val;
		return lhs;
	}
	friend ostream& operator<<(ostream& lhs, mono& rhs) {
		lhs << rhs.val;
		return lhs;
	}
	using monoid_type = T;
};#line 9 "test/aoj/syakutori_DSL_3_C.test.cpp"

using monoid = plus_monoid<long long>;

int main() {
	int N, Q; cin >> N >> Q;
	vector<monoid> a(N);
	for (int i = 0; i < N; i++) cin >> a[i];
	while (Q--) {
		long long x; cin >> x;
		auto r = syakutori<monoid>(a, [&](auto n) {
			return n <= x;
		});
		long long res = 0;
		for (int l = 0; l < N; l++) res += r[l] - l;
		cout << res << endl;
	}
	return 0;
}
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

