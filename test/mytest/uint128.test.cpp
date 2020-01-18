#define IGNORE
/**
 * @title uint128
 * @brief 作成中
 */

#include<bits/stdc++.h>
using namespace std;

// class uint128;

struct uint128 {
	using u32 = uint32_t;
	using u64 = uint64_t;
	union {
		u32 val32[4];
		u64 val64[2];
	} x;
	constexpr uint128() : uint128(0) {}
	template<class T, class U = enable_if_t<is_integral<T>::value>, class V = enable_if_t<numeric_limits<T>::digits <= 64>>
	constexpr uint128(T n) : x{lower_bits(n), upper_bits(n), sign_bits(n), sign_bits(n)} {}
	constexpr uint128(u64 a, u64 b) : x{lower_bits(b), upper_bits(b), lower_bits(a), upper_bits(a)} {}
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
private:
	template<class T>
	constexpr enable_if_t<is_unsigned<T>::value, u32> sign_bits(T x) {
		return 0;
	}
	template<class T>
	constexpr enable_if_t<is_signed<T>::value, u32> sign_bits(T x) {
		return (x < 0 ? numeric_limits<u32>::max() : 0);
	}
	template<class T>
	constexpr enable_if_t<is_integral<T>::value, u32> upper_bits(T x) {
		return static_cast<u32>(static_cast<u64>(x) >> 32);
	}
	template<class T>
	constexpr enable_if_t<is_integral<T>::value, u32> lower_bits(T x) {
		return x & numeric_limits<u32>::max();
	}
};
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
	cout << "plus_test" << endl;
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
	cout << "minus_test" << endl;
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
	cout << "product_test" << endl;
	for (int i = 0; i < 1000; i++) {
		uint128 x1, x2;
		__uint128_t y1, y2;
		make_random(x1, y1);
		make_random(x2, y2);
		assert((x1 *= x2) == (y1 *= y2));
	}
}

int main() {
	plus_test();
	minus_test();
	product_test();
	cout << numeric_limits<__uint128_t>::digits << endl;
	static_assert(numeric_limits<uint128>::digits == 128);
	// static_assert(numeric_limits<uint128>::min() == 0); fail
}