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


# :heavy_check_mark: algorithm/syakutori.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ed469618898d75b149e5c7c4b6a1c415">algorithm</a>
* <a href="{{ site.github.repository_url }}/blob/master/algorithm/syakutori.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-17 12:01:17+09:00




## Depends on

* :heavy_check_mark: <a href="../datastructure/SWAG.cpp.html">datastructure/SWAG.cpp</a>
* :heavy_check_mark: <a href="../math/monoid_t.cpp.html">math/monoid_t.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/syakutori_DSL_3_A.test.cpp.html">test/aoj/syakutori_DSL_3_A.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/syakutori_DSL_3_C.test.cpp.html">test/aoj/syakutori_DSL_3_C.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "../datastructure/SWAG.cpp"
#include "../math/monoid_t.cpp"
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
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "algorithm/../datastructure/SWAG.cpp"
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
	void push(Monoid_T x) {
		push(Monoid(x));
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
};#line 2 "algorithm/../math/monoid_t.cpp"
template<class T>
using monoid_t = typename T::monoid_type;#line 3 "algorithm/syakutori.cpp"
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
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

