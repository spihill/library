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
    - Last commit date: 2020-01-11 17:11:35+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/3/DSL_3_C">https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/3/DSL_3_C</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/algorithm/syakutori.cpp.html">algorithm/syakutori.cpp</a>
* :heavy_check_mark: <a href="../../../library/datastructure/SWAG.cpp.html">datastructure/SWAG.cpp</a>
* :heavy_check_mark: <a href="../../../library/snippet/monoid.cpp.html">snippet/monoid.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/3/DSL_3_C"

#include <bits/stdc++.h>
using namespace std;

#include "../../algorithm/syakutori.cpp"
#include "../../snippet/monoid.cpp"

using mono = monoid<long long, 0>;

template<>
mono mono::operator+(const mono& rhs) const noexcept {
	return mono(this->val + rhs.val);
}

int main() {
	int N, Q; cin >> N >> Q;
	vector<mono> a(N);
	for (int i = 0; i < N; i++) cin >> a[i];
	while (Q--) {
		long long x; cin >> x;
		auto r = syakutori<mono>(a, [&](auto n) {
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
};#line 2 "test/aoj/../../algorithm/syakutori.cpp"
// v : 対象の列 (型が monoid_type を持つ必要がある)
// f : 区間が満たすべき条件を表す関数 (引数 : T::monoid_type 戻り値 : bool)
// continue_flag (default : true) : f の戻り値が continue_flag と等しいような区間を列挙
// 戻り値 : ret[l] = r; (条件を満たす区間 [l, i) の中で最大の i が r)
template<class T>
vector<int> syakutori(const vector<T>& v, const function<bool(typename T::monoid_type)>& f, bool continue_flag = true) {
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
}#line 1 "test/aoj/../../snippet/monoid.cpp"
template<class T, T UNITY>
struct monoid {
	monoid operator+(const monoid& rhs) const noexcept; // {return monoid(val + rhs.val);}
	monoid() : val(UNITY) {}
	explicit monoid(T x) : val(x) {}
	T val;
	bool operator<(const monoid& rhs) const noexcept {return val < rhs.val;}
	bool operator>(const monoid& rhs) const noexcept {return rhs < *this;}
	bool operator<=(const monoid& rhs) const noexcept {return !(rhs < *this);}
	bool operator>=(const monoid& rhs) const noexcept {return !(*this < rhs);}
	bool operator==(const monoid& rhs) const noexcept {return !(*this < rhs) && !(rhs < *this);}
	bool operator!=(const monoid& rhs) const noexcept {return *this < rhs || rhs < *this;}
	friend istream& operator>>(istream& lhs, monoid& rhs) {
		lhs >> rhs.val;
		return lhs;
	}
	friend ostream& operator<<(ostream& lhs, monoid& rhs) {
		lhs << rhs.val;
		return lhs;
	}
	using monoid_type = T;
};#line 8 "test/aoj/syakutori_DSL_3_C.test.cpp"

using mono = monoid<long long, 0>;

template<>
mono mono::operator+(const mono& rhs) const noexcept {
	return mono(this->val + rhs.val);
}

int main() {
	int N, Q; cin >> N >> Q;
	vector<mono> a(N);
	for (int i = 0; i < N; i++) cin >> a[i];
	while (Q--) {
		long long x; cin >> x;
		auto r = syakutori<mono>(a, [&](auto n) {
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

