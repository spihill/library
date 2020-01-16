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


# :heavy_check_mark: test/aoj/syakutori_DSL_3_C.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/syakutori_DSL_3_C.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-16 18:33:41+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/3/DSL_3_C">https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/3/DSL_3_C</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/algorithm/syakutori.cpp.html">algorithm/syakutori.cpp</a>
* :heavy_check_mark: <a href="../../../library/datastructure/SWAG.cpp.html">datastructure/SWAG.cpp</a>
* :heavy_check_mark: <a href="../../../library/math/monoid_t.cpp.html">math/monoid_t.cpp</a>
* :heavy_check_mark: <a href="../../../library/monoid/plus.cpp.html">monoid/plus.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/3/DSL_3_C"

#include <bits/stdc++.h>
using namespace std;

#include "../../algorithm/syakutori.cpp"

#include "../../monoid/plus.cpp"

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
template<class Monoid>
struct SWAG {
	struct node {
		Monoid val, sum;
		node() : val(), sum() {}
		node(Monoid v, Monoid s) : val(v), sum(s) {}
	};
	stack<node> F, B;
	Monoid fold_all() const {
		if (empty()) return Monoid();
		if (F.empty()) return B.top().sum;
		if (B.empty()) return F.top().sum;
		return F.top().sum + B.top().sum;
	}
	void push(Monoid x) {
		if (B.empty()) B.emplace(x, x);
		else {
			Monoid s{B.top().sum + x};
			B.emplace(x, move(s));
		}
	}
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
};#line 2 "test/aoj/../../algorithm/../math/monoid_t.cpp"
template<class T>
using monoid_t = typename T::monoid_type;#line 3 "test/aoj/../../algorithm/syakutori.cpp"
// v : 対象の列 (型が monoid_type を持つ必要がある)
// f : 区間が満たすべき条件を表す関数 (引数 : T::monoid_type 戻り値 : bool)
// continue_flag (default : true) : f の戻り値が continue_flag と等しいような区間を列挙
// 戻り値 : ret[l] = r; (条件を満たす区間 [l, i) の中で最大の i が r)
template<class T>
vector<int> syakutori(const vector<T>& v, const function<bool(monoid_t<T>)>& f, bool continue_flag = true) {
	SWAG<T> S;
	int l = 0, r = 0;
	const int N = v.size();
	vector<int> res(N);
	if (continue_flag) {
		while (l < N) {
			while (r < N && f((S.fold_all() + v[r]).val)) S.push(v[r++]);
			 res[l++] = r;
			if (r < l) r++;
			else S.pop();
		}
	} else {
		while (l < N) {
			while (r < N && !f(S.fold_all().val)) S.push(v[r++]);
			if (r == N && !f(S.fold_all().val)) {
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

#line 1 "test/aoj/../../monoid/plus.cpp"
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

