#include "ctz.cpp"
/**
 * @title 最大公約数
 * @brief Binary GCD
 */
template<class T>
constexpr enable_if_t<is_integral<T>::value, T> gcd(T a, T b) {
	if (a < 0) a = -a;
	if (b < 0) b = -b;
	if (a == 0) return b;
	if (b == 0) return a;
	const int k = ctz(a | b);
	a >>= k;
	b >>= k;
	while (a != b) {
		if (a > b) a ^= b ^= a ^= b;
		b -= a;
		b >>= ctz(b);
	}
	return a << k;
}


