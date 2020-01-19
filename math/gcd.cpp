#pragma once
#include "ctz.cpp"
/**
 * @title 最大公約数
 */

// @brief Binary GCD
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

// @brief map<素数, 冪> の形の整数の gcd
template<class T>
enable_if_t<is_integral<T>::value, map<T, int>> gcd(const map<T, int>& a, const map<T, int>& b) {
	map<T, int> res;
	for (const auto& x : a) if (b.count(x.first)) res[x.first] = min(x.second, b.at(x.first));
	for (const auto& x : b) if (!a.count(x.first)) res.erase(x.first);
	return res;
}