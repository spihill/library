#include "gcd.cpp"
/**
 * @brief 最小公倍数を求める。
 */
template<class T>
constexpr enable_if_t<is_integral<T>::value, T> lcm(T a, T b) {
	if (a < 0) a = -a;
	if (b < 0) b = -b;
	return a / gcd(a, b) * b;
}


