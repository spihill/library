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


# :heavy_check_mark: test/mytest/ModInt.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/mytest/ModInt.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-20 02:36:38+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/1/ITP1_1_A">https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/1/ITP1_1_A</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/math/ModInt.cpp.html">ModInt</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/1/ITP1_1_A"
#include <bits/stdc++.h>

using namespace std;

#include "../../math/ModInt.cpp"

#define RANGE_CHECK(a) assert(0 <= (a).x && (a).x < (modint::get_mod()))

struct random_class {
	struct xorshift {
		using result_type = unsigned int;
		result_type x=123456789u,y=362436069u,z=521288629u,w;
		static constexpr result_type min() {return 0u;}
		static constexpr result_type max() {return UINT_MAX;}
		xorshift(result_type a) : w(a) {}
		result_type operator()() {
			result_type t;
			t = x ^ (x << 11);
			x = y; y = z; z = w;
			return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
		}
	};
	random_device rd;
	xorshift xor128;
	random_class() : rd(), xor128(rd()) {}
	long long make_random(long long min_v, long long max_v) { return uniform_int_distribution<long long>(min_v, max_v)(xor128);}
};

constexpr bool isprime(int m) {
	if (m < 2) return false;
	for (long long i = 2; i * i <= m; i++) {
		if (m % i == 0) return false;
	}
	return true;
}


template<class modint>
void test(modint a) {
	static_assert(isprime(modint::get_mod()), "a.M is not a prime number");
	random_class R;
	a = LLONG_MIN;
	RANGE_CHECK(a);
	a = LLONG_MAX;
	RANGE_CHECK(a);
	for (int i = 0; i < 100; i++) {
		a = R.make_random(LLONG_MIN, LLONG_MAX); RANGE_CHECK(a);
		modint b = R.make_random(LLONG_MIN, LLONG_MAX); RANGE_CHECK(b);
		modint c;
		modint d = a;
		c = a + b; RANGE_CHECK(c); assert((d += b) == c); assert(!(d != c)); d = a;
		c = a - b; RANGE_CHECK(c); assert((d -= b) == c); assert(!(d != c)); d = a;
		c = a / b; RANGE_CHECK(c); assert((d /= b) == c); assert(!(d != c)); d = a;
		c = a * b; RANGE_CHECK(c); assert((d *= b) == c); assert(!(d != c)); d = a;
		long long B = R.make_random(LLONG_MIN, LLONG_MAX);
		modint C;
		modint D = a; RANGE_CHECK(D);
		C = a + B; RANGE_CHECK(C); assert((D += B) == C); assert(!(D != C)); D = B;
		C = B + a; RANGE_CHECK(C); assert((D += a) == C); assert(!(D != C)); D = a;
		C = a - B; RANGE_CHECK(C); assert((D -= B) == C); assert(!(D != C)); D = B;
		C = B - a; RANGE_CHECK(C); assert((D -= a) == C); assert(!(D != C)); D = a;
		C = a * B; RANGE_CHECK(C); assert((D *= B) == C); assert(!(D != C)); D = B;
		C = B * a; RANGE_CHECK(C); assert((D *= a) == C); assert(!(D != C)); D = a;
		C = a / B; RANGE_CHECK(C); assert((D /= B) == C); assert(!(D != C)); D = B;
		C = B / a; RANGE_CHECK(C); assert((D /= a) == C); assert(!(D != C)); D = a;
	}
	for (int i = 0; i < 100; i++) {
		a = R.make_random(LLONG_MIN, LLONG_MAX);
		modint b = R.make_random(LLONG_MIN, LLONG_MAX);
		modint c;
		c = a + b - b; RANGE_CHECK(c); assert(c == a);
		c = b + a - a; RANGE_CHECK(c); assert(c == b);
		c = -a; RANGE_CHECK(c); assert(c == 0 - a);
		c = +a; RANGE_CHECK(c); assert(c == a);
		if (b != 0) {
			assert(a * b / b == a);
			assert(b / b == 1);
		}
		if (a != 0) {
			assert(b * a / a == b);
			assert(a / a == 1);
		}
		modint t = a; RANGE_CHECK(t);
		modint d;
		c = a++; d = t; RANGE_CHECK(c); RANGE_CHECK(d); assert(c == d);
		c = a; d = ++t; RANGE_CHECK(c); RANGE_CHECK(d); assert(c == d);
		c = a--; d = t; RANGE_CHECK(c); RANGE_CHECK(d); assert(c == d);
		c = a; d = --t; RANGE_CHECK(c); RANGE_CHECK(d); assert(c == d);
	}
}

void check_literal() {
	cerr << "ModInt<1000000007> is literal_type" << endl;
	static_assert(is_literal_type<ModInt<2>>::value);
	using modint = ModInt<1000000007>;
	static_assert(modint(1) / 2 == 500000004);
	static_assert(modint(1) + 2 == 3);
	static_assert(modint(1) - 2 == 1000000006);
	static_assert(modint(1) * 2 == 2);
	static_assert(+modint(1) == 1);
	static_assert(-modint(1) == 1000000006);
	static_assert(++modint(1) == 2);
	static_assert(modint(1)++ == 1);
	static_assert(--modint(1) == 0);
	static_assert(modint(1)-- == 1);
	static_assert(modint(2) == (modint(1) = 2));
	static_assert(modint(2).power(2) == 4);
	static_assert(modint(2).inv() == 500000004);
	static_assert(modint(2) != 1);
	static_assert(modint(2) == 2);
	static_assert(static_cast<int>(modint(2)) == 2);

	static_assert(is_same<decltype(modint(1) + 1), modint>::value);
	static_assert(is_same<decltype(1 + modint(1)), modint>::value);
	static_assert(is_same<decltype(modint(1) + modint(1)), modint>::value);
	static_assert(is_same<decltype(+modint(1)), modint>::value);
	static_assert(is_same<decltype(modint(1) += 1), modint&>::value);
	static_assert(is_same<decltype(modint(1)++), modint>::value);
	static_assert(is_same<decltype(++modint(1)), modint&>::value);

	static_assert(is_same<decltype(modint(1) - 1), modint>::value);
	static_assert(is_same<decltype(1 - modint(1)), modint>::value);
	static_assert(is_same<decltype(modint(1) - modint(1)), modint>::value);
	static_assert(is_same<decltype(-modint(1)), modint>::value);
	static_assert(is_same<decltype(modint(1) -= 1), modint&>::value);
	static_assert(is_same<decltype(modint(1)--), modint>::value);
	static_assert(is_same<decltype(--modint(1)), modint&>::value);

	static_assert(is_same<decltype(modint(1) * 1), modint>::value);
	static_assert(is_same<decltype(1 * modint(1)), modint>::value);
	static_assert(is_same<decltype(modint(1) * modint(1)), modint>::value);
	static_assert(is_same<decltype(modint(1) *= 1), modint&>::value);

	static_assert(is_same<decltype(modint(1) / 1), modint>::value);
	static_assert(is_same<decltype(1 / modint(1)), modint>::value);
	static_assert(is_same<decltype(modint(1) / modint(1)), modint>::value);
	static_assert(is_same<decltype(modint(1) /= 1), modint&>::value);
}

int main() {
	check_literal();
	for (int i = 0; i < 100; i++) {
		test(ModInt<1811939329>(0));
		test(ModInt<1711276033>(0));
		test(ModInt<1000000007>(0));
		test(ModInt<1000000009>(0));
		test(ModInt<998244353>(0));
		test(ModInt<10007>(0));
		test(ModInt<10009>(0));
		test(ModInt<2>(0));
		test(ModInt<3>(0));
		test(ModInt<5>(0));
		test(ModInt<7>(0));
		test(ModInt<11>(0));
		test(ModInt<13>(0));
		test(ModInt<97>(0));
	}
	cout << "Hello World" << endl;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/mytest/ModInt.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/1/ITP1_1_A"
#include <bits/stdc++.h>

using namespace std;

#line 1 "test/mytest/../../math/ModInt.cpp"
/**
 * @title ModInt
 * @brief mod を取りながら計算する。リテラル型の要件を満たし、constexprに対応している。
 * @brief これでも Verify してます。 https://github.com/spihill/library/blob/master/test/mytest/ModInt.test.cpp
 */
namespace mylib {
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
}; // mylib
using namespace mylib;
//using modint = ModInt<1000000007>;
//using modint = ModInt<998244353>;#line 7 "test/mytest/ModInt.test.cpp"

#define RANGE_CHECK(a) assert(0 <= (a).x && (a).x < (modint::get_mod()))

struct random_class {
	struct xorshift {
		using result_type = unsigned int;
		result_type x=123456789u,y=362436069u,z=521288629u,w;
		static constexpr result_type min() {return 0u;}
		static constexpr result_type max() {return UINT_MAX;}
		xorshift(result_type a) : w(a) {}
		result_type operator()() {
			result_type t;
			t = x ^ (x << 11);
			x = y; y = z; z = w;
			return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
		}
	};
	random_device rd;
	xorshift xor128;
	random_class() : rd(), xor128(rd()) {}
	long long make_random(long long min_v, long long max_v) { return uniform_int_distribution<long long>(min_v, max_v)(xor128);}
};

constexpr bool isprime(int m) {
	if (m < 2) return false;
	for (long long i = 2; i * i <= m; i++) {
		if (m % i == 0) return false;
	}
	return true;
}


template<class modint>
void test(modint a) {
	static_assert(isprime(modint::get_mod()), "a.M is not a prime number");
	random_class R;
	a = LLONG_MIN;
	RANGE_CHECK(a);
	a = LLONG_MAX;
	RANGE_CHECK(a);
	for (int i = 0; i < 100; i++) {
		a = R.make_random(LLONG_MIN, LLONG_MAX); RANGE_CHECK(a);
		modint b = R.make_random(LLONG_MIN, LLONG_MAX); RANGE_CHECK(b);
		modint c;
		modint d = a;
		c = a + b; RANGE_CHECK(c); assert((d += b) == c); assert(!(d != c)); d = a;
		c = a - b; RANGE_CHECK(c); assert((d -= b) == c); assert(!(d != c)); d = a;
		c = a / b; RANGE_CHECK(c); assert((d /= b) == c); assert(!(d != c)); d = a;
		c = a * b; RANGE_CHECK(c); assert((d *= b) == c); assert(!(d != c)); d = a;
		long long B = R.make_random(LLONG_MIN, LLONG_MAX);
		modint C;
		modint D = a; RANGE_CHECK(D);
		C = a + B; RANGE_CHECK(C); assert((D += B) == C); assert(!(D != C)); D = B;
		C = B + a; RANGE_CHECK(C); assert((D += a) == C); assert(!(D != C)); D = a;
		C = a - B; RANGE_CHECK(C); assert((D -= B) == C); assert(!(D != C)); D = B;
		C = B - a; RANGE_CHECK(C); assert((D -= a) == C); assert(!(D != C)); D = a;
		C = a * B; RANGE_CHECK(C); assert((D *= B) == C); assert(!(D != C)); D = B;
		C = B * a; RANGE_CHECK(C); assert((D *= a) == C); assert(!(D != C)); D = a;
		C = a / B; RANGE_CHECK(C); assert((D /= B) == C); assert(!(D != C)); D = B;
		C = B / a; RANGE_CHECK(C); assert((D /= a) == C); assert(!(D != C)); D = a;
	}
	for (int i = 0; i < 100; i++) {
		a = R.make_random(LLONG_MIN, LLONG_MAX);
		modint b = R.make_random(LLONG_MIN, LLONG_MAX);
		modint c;
		c = a + b - b; RANGE_CHECK(c); assert(c == a);
		c = b + a - a; RANGE_CHECK(c); assert(c == b);
		c = -a; RANGE_CHECK(c); assert(c == 0 - a);
		c = +a; RANGE_CHECK(c); assert(c == a);
		if (b != 0) {
			assert(a * b / b == a);
			assert(b / b == 1);
		}
		if (a != 0) {
			assert(b * a / a == b);
			assert(a / a == 1);
		}
		modint t = a; RANGE_CHECK(t);
		modint d;
		c = a++; d = t; RANGE_CHECK(c); RANGE_CHECK(d); assert(c == d);
		c = a; d = ++t; RANGE_CHECK(c); RANGE_CHECK(d); assert(c == d);
		c = a--; d = t; RANGE_CHECK(c); RANGE_CHECK(d); assert(c == d);
		c = a; d = --t; RANGE_CHECK(c); RANGE_CHECK(d); assert(c == d);
	}
}

void check_literal() {
	cerr << "ModInt<1000000007> is literal_type" << endl;
	static_assert(is_literal_type<ModInt<2>>::value);
	using modint = ModInt<1000000007>;
	static_assert(modint(1) / 2 == 500000004);
	static_assert(modint(1) + 2 == 3);
	static_assert(modint(1) - 2 == 1000000006);
	static_assert(modint(1) * 2 == 2);
	static_assert(+modint(1) == 1);
	static_assert(-modint(1) == 1000000006);
	static_assert(++modint(1) == 2);
	static_assert(modint(1)++ == 1);
	static_assert(--modint(1) == 0);
	static_assert(modint(1)-- == 1);
	static_assert(modint(2) == (modint(1) = 2));
	static_assert(modint(2).power(2) == 4);
	static_assert(modint(2).inv() == 500000004);
	static_assert(modint(2) != 1);
	static_assert(modint(2) == 2);
	static_assert(static_cast<int>(modint(2)) == 2);

	static_assert(is_same<decltype(modint(1) + 1), modint>::value);
	static_assert(is_same<decltype(1 + modint(1)), modint>::value);
	static_assert(is_same<decltype(modint(1) + modint(1)), modint>::value);
	static_assert(is_same<decltype(+modint(1)), modint>::value);
	static_assert(is_same<decltype(modint(1) += 1), modint&>::value);
	static_assert(is_same<decltype(modint(1)++), modint>::value);
	static_assert(is_same<decltype(++modint(1)), modint&>::value);

	static_assert(is_same<decltype(modint(1) - 1), modint>::value);
	static_assert(is_same<decltype(1 - modint(1)), modint>::value);
	static_assert(is_same<decltype(modint(1) - modint(1)), modint>::value);
	static_assert(is_same<decltype(-modint(1)), modint>::value);
	static_assert(is_same<decltype(modint(1) -= 1), modint&>::value);
	static_assert(is_same<decltype(modint(1)--), modint>::value);
	static_assert(is_same<decltype(--modint(1)), modint&>::value);

	static_assert(is_same<decltype(modint(1) * 1), modint>::value);
	static_assert(is_same<decltype(1 * modint(1)), modint>::value);
	static_assert(is_same<decltype(modint(1) * modint(1)), modint>::value);
	static_assert(is_same<decltype(modint(1) *= 1), modint&>::value);

	static_assert(is_same<decltype(modint(1) / 1), modint>::value);
	static_assert(is_same<decltype(1 / modint(1)), modint>::value);
	static_assert(is_same<decltype(modint(1) / modint(1)), modint>::value);
	static_assert(is_same<decltype(modint(1) /= 1), modint&>::value);
}

int main() {
	check_literal();
	for (int i = 0; i < 100; i++) {
		test(ModInt<1811939329>(0));
		test(ModInt<1711276033>(0));
		test(ModInt<1000000007>(0));
		test(ModInt<1000000009>(0));
		test(ModInt<998244353>(0));
		test(ModInt<10007>(0));
		test(ModInt<10009>(0));
		test(ModInt<2>(0));
		test(ModInt<3>(0));
		test(ModInt<5>(0));
		test(ModInt<7>(0));
		test(ModInt<11>(0));
		test(ModInt<13>(0));
		test(ModInt<97>(0));
	}
	cout << "Hello World" << endl;
}
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

