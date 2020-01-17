/**
 * @title uint128
 * @brief 作成中
 */

#include<bits/stdc++.h>
using namespace std;

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

int main() {
	uint128 x(100000000);
	uint128 y(1000000);
	for (int i = 0; i < 4; i++) cout << x.x.val32[i] << endl;
	cout << endl;
	for (int i = 0; i < 4; i++) cout << y.x.val32[i] << endl;
	cout << endl;
	y *= x;
	for (int i = 0; i < 4; i++) cout << y.x.val32[i] << endl;
	cout << endl;
	for (int i = 0; i < 2; i++) cout << y.x.val64[i] << endl;
}