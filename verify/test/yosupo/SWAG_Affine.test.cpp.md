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


# :heavy_check_mark: test/yosupo/SWAG_Affine.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/yosupo/SWAG_Affine.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-30 23:36:16+09:00


* see: <a href="https://judge.yosupo.jp/problem/queue_operate_all_composite">https://judge.yosupo.jp/problem/queue_operate_all_composite</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/datastructure/SWAG.cpp.html">SWAG (Sliding Window Aggregation)</a>
* :heavy_check_mark: <a href="../../../library/math/ModInt.cpp.html">ModInt</a>
* :heavy_check_mark: <a href="../../../library/monoid/affine_monoid.cpp.html">monoid/affine_monoid.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/queue_operate_all_composite"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/SWAG.cpp"
#include "../../monoid/affine_monoid.cpp"
#include "../../math/ModInt.cpp"

using modint = ModInt<998244353>;
using monoid = affine_monoid<modint>;

int main() {
	int Q; cin >> Q;
	SWAG<monoid> S;
	for (int i = 0; i < Q; i++) {
		int q; cin >> q;
		if (q == 0) {
			int a, b; cin >> a >> b;
			S.push({a, b});
		} else if (q == 1) {
			S.pop();
		} else if (q == 2) {
			modint x; cin >> x;
			auto res = S.fold_all();
			cout << res.first * x + res.second << endl;
		}
	}
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yosupo/SWAG_Affine.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/queue_operate_all_composite"

#include<bits/stdc++.h>

using namespace std;

#line 1 "test/yosupo/../../datastructure/SWAG.cpp"
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
#line 1 "test/yosupo/../../monoid/affine_monoid.cpp"
template<class T>
struct affine_monoid {
	using mono = affine_monoid;
	affine_monoid() : affine_monoid(pair<T, T>(1, 0)) {}
	explicit affine_monoid(pair<T, T> x) : val(x) {}
	pair<T, T> val;
	mono operator+(const mono& rhs) const {
		return mono(pair<T, T>(rhs.val.first * val.first, rhs.val.first * val.second + rhs.val.second));
	}
	friend istream& operator>>(istream& lhs, mono& rhs) {
		lhs >> rhs.val.first >> rhs.val.second;
		return lhs;
	}
	friend ostream& operator<<(ostream& lhs, mono& rhs) {
		lhs << rhs.val.first << ' ' << rhs.val.second;
		return lhs;
	}
	using monoid_type = pair<T, T>;

};
#line 1 "test/yosupo/../../math/ModInt.cpp"
/**
 * @title ModInt
 * @brief mod を取りながら計算する。リテラル型の要件を満たし、constexprに対応している。
 * @brief これでも Verify してます。 https://github.com/spihill/library/blob/master/test/mytest/ModInt.test.cpp
 */
namespace modint_n {
template<int mod>
struct ModInt {
	using i64 = int_fast64_t;
	int x;
	constexpr static int get_mod() {
		return mod;
	}
	constexpr ModInt(i64 x_) : x(mod_(x_)) {}
	constexpr ModInt() : ModInt(0) {}
	~ModInt() = default;
	inline constexpr ModInt& operator+=(const ModInt rhs) {
		i64 t = static_cast<i64>(x) + rhs.x;
		if (t >= mod) x = t - mod;
		else x = t;
		return (*this);
	}
	inline constexpr ModInt& operator-=(const ModInt rhs) {
		i64 t = static_cast<i64>(x) + mod - rhs.x;
		if (t >= mod) x = t - mod;
		else x = t;
		return *this;
	}
	inline constexpr ModInt& operator*=(const ModInt rhs) {
		x = static_cast<i64>(x) * rhs.x % mod;
		return *this;
	}
	inline constexpr ModInt& operator/=(ModInt rhs) {
		return *this *= rhs.inv();
	}
	inline constexpr ModInt power(i64 p) const {
		ModInt res = 1;
		ModInt a = x;
		for (; p; res = p & 1 ? res * a : res, a *= a, p >>= 1);
		return res;
	}
	inline constexpr ModInt inv() const {
		int z = 0, w = 0;
		extgcd(mod, x, z, w);
		return ModInt(w);
	}
	inline constexpr ModInt& operator=(const ModInt& rhs) {
		this->x = rhs.x;
		return *this;
	}
	inline constexpr int operator==(const ModInt& rhs) const {
		return this->x == rhs.x;
	}
	inline constexpr int operator!=(const ModInt& rhs) const {
		return !(*this == rhs);
	}
	inline constexpr ModInt operator++(signed unused) {
		ModInt res(*this);
		++(*this);
		return res;
	}
	inline constexpr ModInt& operator++() {
		(*this) += 1;
		return (*this);
	}
	inline constexpr ModInt operator--(signed unused) {
		ModInt res(*this);
		--(*this);
		return res;
	}
	inline constexpr ModInt& operator--() {
		(*this) -= 1;
		return (*this);
	}
	inline constexpr ModInt operator+() const {
		return (*this);
	}
	inline constexpr ModInt operator-() const {
		return (*this).x ? ModInt(mod - (*this).x) : ModInt(0);
	}
	friend constexpr ModInt operator+(const ModInt& lhs, const ModInt& rhs) {return ModInt(lhs) += rhs;}
	friend constexpr ModInt operator-(const ModInt& lhs, const ModInt& rhs) {return ModInt(lhs) -= rhs;}
	friend constexpr ModInt operator*(const ModInt& lhs, const ModInt& rhs) {return ModInt(lhs) *= rhs;}
	friend constexpr ModInt operator/(const ModInt& lhs, const ModInt& rhs) {return ModInt(lhs) /= rhs;}
	explicit constexpr operator int() const {return x;}
	friend ostream& operator<<(ostream& lhs, const ModInt& rhs) {
		lhs << rhs.x;
		return lhs;
	}
	friend istream& operator>>(istream& lhs, ModInt& rhs) {
		i64 t;
		lhs >> t;
		rhs = ModInt(t);
		return lhs;
	}
private:
	constexpr int extgcd(int a, int b, int& x, int& y) const {
		int d = a;
		if (b == 0) {
			x = 1;
			y = 0;
		} else {
			d = extgcd(b, a%b, y, x);
			y -= a / b * x;
		}
		return d;
	}
	constexpr int mod_(i64 x) {
		x %= mod; if (x < 0) x += mod;
		return static_cast<int>(x);
	}
};
}; // modint_n
using namespace modint_n;
namespace std {
template<int N> struct is_integral<ModInt<N>> {
	static constexpr integral_constant<bool, true> value = integral_constant<bool, true>();
};
template<int N> struct is_arithmetic<ModInt<N>> {
	static constexpr integral_constant<bool, true> value = integral_constant<bool, true>();
};
template<int N> struct is_scalar<ModInt<N>> {
	static constexpr integral_constant<bool, true> value = integral_constant<bool, true>();
};
template<int N> struct is_floating_point<ModInt<N>> {
	static constexpr integral_constant<bool, false> value = integral_constant<bool, false>();
};
template<int N> struct is_signed<ModInt<N>> {
	static constexpr integral_constant<bool, false> value = integral_constant<bool, false>();
};
template<int N> struct is_unsigned<ModInt<N>> {
	static constexpr integral_constant<bool, true> value = integral_constant<bool, true>();
};
} // namespace std
//using modint = ModInt<1000000007>;
//using modint = ModInt<998244353>;
#line 10 "test/yosupo/SWAG_Affine.test.cpp"

using modint = ModInt<998244353>;
using monoid = affine_monoid<modint>;

int main() {
	int Q; cin >> Q;
	SWAG<monoid> S;
	for (int i = 0; i < Q; i++) {
		int q; cin >> q;
		if (q == 0) {
			int a, b; cin >> a >> b;
			S.push({a, b});
		} else if (q == 1) {
			S.pop();
		} else if (q == 2) {
			modint x; cin >> x;
			auto res = S.fold_all();
			cout << res.first * x + res.second << endl;
		}
	}
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

