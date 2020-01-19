#include "gcd.cpp"
// @title 最小公倍数

// @brief 最小公倍数を求める。(Binary GCD を利用)
template<class T>
constexpr enable_if_t<is_integral<T>::value, T> lcm(T a, T b) {
	if (a < 0) a = -a;
	if (b < 0) b = -b;
	return a / gcd(a, b) * b;
}

// @brief map<素数, 冪> の形の整数の lcm
template<class T>
enable_if_t<is_integral<T>::value, map<T, int>> lcm(const map<T, int>& a, const map<T, int>& b) {
	map<T, int> res = a;
	for (const auto& x : b) res[x.first] = max(res[x.first], x.second);
	return res;
}