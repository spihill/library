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


# :heavy_check_mark: test/aoj/ModComb_compiletime.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#0d0c91c0cca30af9c1c9faef0cf04aa9">test/aoj</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/ModComb_compiletime.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-24 17:53:21+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1501&lang=ja">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1501&lang=ja</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/math/ModComb_compiletime.cpp.html">コンパイル時前計算 Mod Combination</a>
* :heavy_check_mark: <a href="../../../library/math/ModInt.cpp.html">ModInt</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1501&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#include "../../math/ModInt.cpp"
using modint = ModInt<100000007>;
#include "../../math/ModComb_compiletime.cpp"


int main() {
	int r, c;
	cin >> r >> c;
	int r1, c1, r2, c2;
	cin >> r1 >> c1 >> r2 >> c2;
	int R = abs(r1 - r2);
	int C = abs(c1 - c2);
	int mi = INT_MAX;
	modint res = 0;
	for (int i = 0; i < 2; i++) {
		int a = i ? R : r - R;
		for (int j = 0; j < 2; j++) {
			int b = j ? C : c - C;
			if (a + b < mi) res = nCr(a + b, a);
			else if (a + b == mi) res += nCr(a + b, a);
			assert(nCr(a + b, a) == nHr(b + 1, a));
			assert(nCr(a + b, a) == nPr(a + b, a) / nPr(a, a));
			mi = min(mi, a + b);
		}
	}
	cout << res << endl;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj/ModComb_compiletime.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1501&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#line 1 "test/aoj/../../math/ModInt.cpp"
/**
 * @title ModInt
 * @brief mod を取りながら計算する。リテラル型の要件を満たし、constexprに対応している。
 * @brief これでも Verify してます。 https://github.com/spihill/library/blob/master/test/mytest/ModInt.test.cpp
 */
namespace modint_n {
using value_type = signed;
template<value_type mod>
struct ModInt {
	using i64 = int_fast64_t;
	value_type x;
	constexpr static value_type get_mod() {
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
		value_type z = 0, w = 0;
		extgcd(mod, x, z, w);
		return ModInt(w);
	}
	inline constexpr ModInt& operator=(const ModInt& rhs) {
		this->x = rhs.x;
		return *this;
	}
	inline constexpr value_type operator==(const ModInt& rhs) const {
		return this->x == rhs.x;
	}
	inline constexpr value_type operator!=(const ModInt& rhs) const {
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
	explicit constexpr operator value_type() const {return x;}
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
	constexpr value_type extgcd(value_type a, value_type b, value_type& x, value_type& y) const {
		value_type d = a;
		if (b == 0) {
			x = 1;
			y = 0;
		} else {
			d = extgcd(b, a%b, y, x);
			y -= a / b * x;
		}
		return d;
	}
	constexpr value_type mod_(i64 x) {
		x %= mod; if (x < 0) x += mod;
		return static_cast<value_type>(x);
	}
};
}; // modint_n
using modint_n::ModInt;
namespace std {
template<modint_n::value_type N> struct is_integral<ModInt<N>> {
	static constexpr integral_constant<bool, true> value = integral_constant<bool, true>();
};
template<modint_n::value_type N> struct is_arithmetic<ModInt<N>> {
	static constexpr integral_constant<bool, true> value = integral_constant<bool, true>();
};
template<modint_n::value_type N> struct is_scalar<ModInt<N>> {
	static constexpr integral_constant<bool, true> value = integral_constant<bool, true>();
};
template<modint_n::value_type N> struct is_floating_point<ModInt<N>> {
	static constexpr integral_constant<bool, false> value = integral_constant<bool, false>();
};
template<modint_n::value_type N> struct is_signed<ModInt<N>> {
	static constexpr integral_constant<bool, false> value = integral_constant<bool, false>();
};
template<modint_n::value_type N> struct is_unsigned<ModInt<N>> {
	static constexpr integral_constant<bool, true> value = integral_constant<bool, true>();
};
} // namespace std
//using modint = ModInt<1000000007>;
//using modint = ModInt<998244353>;
#line 8 "test/aoj/ModComb_compiletime.test.cpp"
using modint = ModInt<100000007>;
#line 1 "test/aoj/../../math/ModComb_compiletime.cpp"
/**
 * @title コンパイル時前計算 Mod Combination
 * @brief 使用する際は N のサイズを適切に設定すること
 */
namespace modcomb_compiletime_n {
constexpr int N = 200000;
constexpr int mod = modint::get_mod();
struct Fact {
	int_fast32_t val[N+1];
	int_fast32_t vali[N+1];
	constexpr Fact() : val() , vali() {
		val[0] = 1;
		for (int_fast32_t i = 1; i <= N; i++) val[i] = static_cast<int_fast64_t>(val[i-1]) * i % mod;
		vali[N] = static_cast<int_fast32_t>(modint(val[N]).inv().x);
		for (int_fast32_t i = N; i; i--) vali[i-1] = static_cast<int_fast64_t>(vali[i]) * i % mod;
	}
};
constexpr auto fact = Fact();
constexpr modint nCr(int n, int r) {
	assert(n <= N+1);
	if(n < 0 || r < 0 || n < r) return 0;
	return modint(fact.val[n]) * fact.vali[r] * fact.vali[n-r];
}
constexpr modint nPr(int n, int r) {
	assert(n <= N+1);
	if(n < 0 || r < 0 || n < r) return 0;
	return modint(fact.val[n]) * fact.vali[n-r];
}
constexpr modint nHr(int n, int r) {
	if(n < 0 || r < 0) return 0;
	return nCr(n + r - 1, r);
}
} // namespace modcomb_compiletime_n
using namespace modcomb_compiletime_n;
#line 10 "test/aoj/ModComb_compiletime.test.cpp"


int main() {
	int r, c;
	cin >> r >> c;
	int r1, c1, r2, c2;
	cin >> r1 >> c1 >> r2 >> c2;
	int R = abs(r1 - r2);
	int C = abs(c1 - c2);
	int mi = INT_MAX;
	modint res = 0;
	for (int i = 0; i < 2; i++) {
		int a = i ? R : r - R;
		for (int j = 0; j < 2; j++) {
			int b = j ? C : c - C;
			if (a + b < mi) res = nCr(a + b, a);
			else if (a + b == mi) res += nCr(a + b, a);
			assert(nCr(a + b, a) == nHr(b + 1, a));
			assert(nCr(a + b, a) == nPr(a + b, a) / nPr(a, a));
			mi = min(mi, a + b);
		}
	}
	cout << res << endl;
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

