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


# :heavy_check_mark: uint128

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#5ff6b7301d4665da3fdb252aa08f6f6d">test/mytest</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/mytest/uint128.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-09 15:05:36+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/1/ITP1_1_A">https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/1/ITP1_1_A</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define IGNORE
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/1/ITP1_1_A"
/**
 * @title uint128
 * @brief 作成中
 */

#include<bits/stdc++.h>
using namespace std;


namespace uint128_n {
using u32 = uint32_t;
using u64 = uint64_t;

template<class T>
constexpr enable_if_t<is_unsigned<T>::value, u64> sign_bits(T x) {
	return 0;
}
template<class T>
constexpr enable_if_t<!is_unsigned<T>::value, u64> sign_bits(T x) {
	return (x < 0 ? numeric_limits<u64>::max() : 0);
}
constexpr u32 upper_bits(u64 x) {
	return static_cast<u32>(static_cast<u64>(x) >> 32);
}
constexpr u32 lower_bits(u64 x) {
	return x & numeric_limits<u32>::max();
}

struct uint128 {
	union {
		u64 val64[2];
		u32 val32[4];
	} x;
	constexpr uint128() : uint128(0) {}
	template<class T>
	constexpr uint128(T n) : x{{ static_cast<u64>(n), sign_bits(n) }} {
		static_assert(is_integral<T>::value, "");
	}
	constexpr uint128(u64 a, u64 b) : x {{b, a}} {}
	inline constexpr uint128& operator+=(const uint128& rhs) {
		u32 carry = 0;
		for (int i = 0; i < 4; i++) {
			u64 sum = static_cast<u64>(x.val32[i]) + rhs.x.val32[i] + carry;
			x.val32[i] = lower_bits(sum);
			carry = upper_bits(sum);
		}
		return *this;
	}
	inline constexpr uint128& operator-=(const uint128& rhs) {
		return *this += -rhs;
	}
	inline constexpr uint128 operator-() const {
		uint128 res{0};
		res.x.val64[0] = x.val64[0] ^ numeric_limits<u64>::max();
		res.x.val64[1] = x.val64[1] ^ numeric_limits<u64>::max();
		if (res.x.val64[0] == numeric_limits<u64>::max()) {
			res.x.val64[0] = 0;
			res.x.val64[1]++;
		} else {
			res.x.val64[0]++;
		}
		return res;
	}
	inline constexpr uint128& operator*=(const uint128& rhs) {
		u64 res[5] = {0, 0, 0, 0, 0};
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j + i < 4; j++) {
				u64 prod = static_cast<u64>(x.val32[i]) * rhs.x.val32[j];
				res[i+j] += lower_bits(prod);
				res[i+j+1] += upper_bits(prod);
			}
		}
		for (int i = 0; i < 3; i++) {
			x.val32[i] = lower_bits(res[i]);
			res[i+1] += upper_bits(res[i]);
		}
		x.val32[3] = lower_bits(res[3]);
		return *this;
	}
	inline constexpr bool operator==(const __uint128_t& rhs) const {
		return x.val64[0] == static_cast<u64>(rhs & numeric_limits<u64>::max()) && x.val64[1] == static_cast<u64>(rhs >> 64);
	}
	inline constexpr bool operator<(const __uint128_t& rhs) const {
		return x.val64[0] == static_cast<u64>(rhs & numeric_limits<u64>::max()) && x.val64[1] == static_cast<u64>(rhs >> 64);
	}
	explicit constexpr operator u64() const {return x.val64[0];}
};
}
using uint128_n::uint128;
namespace std {
template<> struct is_integral<uint128> {
	static constexpr integral_constant<bool, true> value = integral_constant<bool, true>();
};
template<> struct is_arithmetic<uint128> {
	static constexpr integral_constant<bool, true> value = integral_constant<bool, true>();
};
template<> struct is_scalar<uint128> {
	static constexpr integral_constant<bool, true> value = integral_constant<bool, true>();
};
template<> struct is_floating_point<uint128> {
	static constexpr integral_constant<bool, false> value = integral_constant<bool, false>();
};
template<> struct is_signed<uint128> {
	static constexpr integral_constant<bool, false> value = integral_constant<bool, false>();
};
template<> struct is_unsigned<uint128> {
	static constexpr integral_constant<bool, true> value = integral_constant<bool, true>();
};
} // namespace std
template<> struct std::numeric_limits<uint128> {
	using u64 = uint64_t;
	static constexpr uint128 min() {return 0;}
	static constexpr uint128 max() {return uint128(numeric_limits<u64>::max(), numeric_limits<u64>::max());}
	static constexpr int digits = 128;
};

using u64 = uint64_t;
random_device rd;
mt19937 mt(rd());
uniform_int_distribution<u64> uni(numeric_limits<u64>::min(), numeric_limits<u64>::max());

void make_random(uint128& x, __uint128_t& y) {
	u64 a = uni(mt);
	u64 b = uni(mt);
	x = uint128{a, b};
	y = (static_cast<__int128_t>(a) << 64) | b;
}

void plus_test() {
	cerr << "plus_test" << endl;
	uint128 x{0};
	__uint128_t y{0};
	assert(x == y);
	for (int i = 0; i < 1000; i++) {
		uint128 x2;
		__uint128_t y2;
		make_random(x2, y2);
		x += x2;
		y += y2;
		assert(x == y);
	}
}

void minus_test() {
	cerr << "minus_test" << endl;
	uint128 x{0};
	__uint128_t y{0};
	assert(x == y);
	for (int i = 0; i < 1000; i++) {
		uint128 x2;
		__uint128_t y2;
		make_random(x2, y2);
		x -= x2;
		y -= y2;
		assert(x == y);
	}
}

void product_test() {
	cerr << "product_test" << endl;
	for (int i = 0; i < 1000; i++) {
		uint128 x1, x2;
		__uint128_t y1, y2;
		make_random(x1, y1);
		make_random(x2, y2); assert((x1 *= x2) == (y1 *= y2));
	}
}

bool is_prime(uint_fast64_t n) {
}

int main() {
	plus_test();
	minus_test();
	product_test();
	static_assert(numeric_limits<uint128>::digits == 128, "");
	static_assert(numeric_limits<uint128>::min() == 0, "");
	uint128 x = -10;
	uint128 y = 0;
	y = x;
	y += 10;
	cout << bitset<64>(y.x.val64[1]) << ' ' << bitset<64>(y.x.val64[0]) << endl;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/mytest/uint128.test.cpp"
#define IGNORE
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/1/ITP1_1_A"
/**
 * @title uint128
 * @brief 作成中
 */

#include<bits/stdc++.h>
using namespace std;


namespace uint128_n {
using u32 = uint32_t;
using u64 = uint64_t;

template<class T>
constexpr enable_if_t<is_unsigned<T>::value, u64> sign_bits(T x) {
	return 0;
}
template<class T>
constexpr enable_if_t<!is_unsigned<T>::value, u64> sign_bits(T x) {
	return (x < 0 ? numeric_limits<u64>::max() : 0);
}
constexpr u32 upper_bits(u64 x) {
	return static_cast<u32>(static_cast<u64>(x) >> 32);
}
constexpr u32 lower_bits(u64 x) {
	return x & numeric_limits<u32>::max();
}

struct uint128 {
	union {
		u64 val64[2];
		u32 val32[4];
	} x;
	constexpr uint128() : uint128(0) {}
	template<class T>
	constexpr uint128(T n) : x{{ static_cast<u64>(n), sign_bits(n) }} {
		static_assert(is_integral<T>::value, "");
	}
	constexpr uint128(u64 a, u64 b) : x {{b, a}} {}
	inline constexpr uint128& operator+=(const uint128& rhs) {
		u32 carry = 0;
		for (int i = 0; i < 4; i++) {
			u64 sum = static_cast<u64>(x.val32[i]) + rhs.x.val32[i] + carry;
			x.val32[i] = lower_bits(sum);
			carry = upper_bits(sum);
		}
		return *this;
	}
	inline constexpr uint128& operator-=(const uint128& rhs) {
		return *this += -rhs;
	}
	inline constexpr uint128 operator-() const {
		uint128 res{0};
		res.x.val64[0] = x.val64[0] ^ numeric_limits<u64>::max();
		res.x.val64[1] = x.val64[1] ^ numeric_limits<u64>::max();
		if (res.x.val64[0] == numeric_limits<u64>::max()) {
			res.x.val64[0] = 0;
			res.x.val64[1]++;
		} else {
			res.x.val64[0]++;
		}
		return res;
	}
	inline constexpr uint128& operator*=(const uint128& rhs) {
		u64 res[5] = {0, 0, 0, 0, 0};
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j + i < 4; j++) {
				u64 prod = static_cast<u64>(x.val32[i]) * rhs.x.val32[j];
				res[i+j] += lower_bits(prod);
				res[i+j+1] += upper_bits(prod);
			}
		}
		for (int i = 0; i < 3; i++) {
			x.val32[i] = lower_bits(res[i]);
			res[i+1] += upper_bits(res[i]);
		}
		x.val32[3] = lower_bits(res[3]);
		return *this;
	}
	inline constexpr bool operator==(const __uint128_t& rhs) const {
		return x.val64[0] == static_cast<u64>(rhs & numeric_limits<u64>::max()) && x.val64[1] == static_cast<u64>(rhs >> 64);
	}
	inline constexpr bool operator<(const __uint128_t& rhs) const {
		return x.val64[0] == static_cast<u64>(rhs & numeric_limits<u64>::max()) && x.val64[1] == static_cast<u64>(rhs >> 64);
	}
	explicit constexpr operator u64() const {return x.val64[0];}
};
}
using uint128_n::uint128;
namespace std {
template<> struct is_integral<uint128> {
	static constexpr integral_constant<bool, true> value = integral_constant<bool, true>();
};
template<> struct is_arithmetic<uint128> {
	static constexpr integral_constant<bool, true> value = integral_constant<bool, true>();
};
template<> struct is_scalar<uint128> {
	static constexpr integral_constant<bool, true> value = integral_constant<bool, true>();
};
template<> struct is_floating_point<uint128> {
	static constexpr integral_constant<bool, false> value = integral_constant<bool, false>();
};
template<> struct is_signed<uint128> {
	static constexpr integral_constant<bool, false> value = integral_constant<bool, false>();
};
template<> struct is_unsigned<uint128> {
	static constexpr integral_constant<bool, true> value = integral_constant<bool, true>();
};
} // namespace std
template<> struct std::numeric_limits<uint128> {
	using u64 = uint64_t;
	static constexpr uint128 min() {return 0;}
	static constexpr uint128 max() {return uint128(numeric_limits<u64>::max(), numeric_limits<u64>::max());}
	static constexpr int digits = 128;
};

using u64 = uint64_t;
random_device rd;
mt19937 mt(rd());
uniform_int_distribution<u64> uni(numeric_limits<u64>::min(), numeric_limits<u64>::max());

void make_random(uint128& x, __uint128_t& y) {
	u64 a = uni(mt);
	u64 b = uni(mt);
	x = uint128{a, b};
	y = (static_cast<__int128_t>(a) << 64) | b;
}

void plus_test() {
	cerr << "plus_test" << endl;
	uint128 x{0};
	__uint128_t y{0};
	assert(x == y);
	for (int i = 0; i < 1000; i++) {
		uint128 x2;
		__uint128_t y2;
		make_random(x2, y2);
		x += x2;
		y += y2;
		assert(x == y);
	}
}

void minus_test() {
	cerr << "minus_test" << endl;
	uint128 x{0};
	__uint128_t y{0};
	assert(x == y);
	for (int i = 0; i < 1000; i++) {
		uint128 x2;
		__uint128_t y2;
		make_random(x2, y2);
		x -= x2;
		y -= y2;
		assert(x == y);
	}
}

void product_test() {
	cerr << "product_test" << endl;
	for (int i = 0; i < 1000; i++) {
		uint128 x1, x2;
		__uint128_t y1, y2;
		make_random(x1, y1);
		make_random(x2, y2); assert((x1 *= x2) == (y1 *= y2));
	}
}

bool is_prime(uint_fast64_t n) {
}

int main() {
	plus_test();
	minus_test();
	product_test();
	static_assert(numeric_limits<uint128>::digits == 128, "");
	static_assert(numeric_limits<uint128>::min() == 0, "");
	uint128 x = -10;
	uint128 y = 0;
	y = x;
	y += 10;
	cout << bitset<64>(y.x.val64[1]) << ' ' << bitset<64>(y.x.val64[0]) << endl;
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

