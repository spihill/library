#include <bits/stdc++.h>

using namespace std;


namespace mylib {
template<int mod>
struct ModInt {
	using ll = long long;
	int x;
	constexpr static int M = mod;
	ModInt(ll x_) {
		x = x_ % mod;
		if (x < 0) x += mod;
	}
	ModInt() : ModInt(0) {}
	inline ModInt& operator+=(const ModInt rhs) {
		x += rhs.x;
		x %= mod;
		return (*this);
	}
	inline ModInt& operator-=(const ModInt rhs) {
		(*this) += -rhs;
		return *this;
	}
	inline ModInt& operator*=(const ModInt rhs) {
		x = ((ll) x * rhs.x) % mod;
		return *this;
	}
	inline ModInt& operator/=(ModInt rhs) {
		return *this *= rhs.power(mod - 2);
	}
	inline ModInt power(ll p) {
		ModInt res = 1;
		ModInt a = x;
		for (; p; res = p & 1 ? res * a : res, a *= a, p >>= 1);
		return res;
	}
	inline ModInt& operator=(const ModInt& rhs) {
		this->x = rhs.x;
		return *this;
	}
	inline int operator==(const ModInt& rhs) const {
		return this->x == rhs.x;
	}
	inline int operator!=(const ModInt& rhs) const {
		return !(*this != rhs);
	}
	inline ModInt operator++(signed unused) {
		ModInt res(*this);
		++(*this);
		return res;
	}
	inline ModInt& operator++() {
		(*this) += 1;
		return (*this);
	}
	inline ModInt operator--(signed unused) {
		ModInt res(*this);
		--(*this);
		return res;
	}
	inline ModInt& operator--() {
		(*this) -= 1;
		return (*this);
	}
	inline ModInt operator+() const {
		return (*this);
	}
	inline ModInt operator-() const {
		return (*this).x ? ModInt(mod - (*this).x) : ModInt(0);
	}
	friend const ModInt operator+(const ModInt& lhs, const ModInt& rhs) {return ModInt(lhs) += rhs;}
	friend const ModInt operator-(const ModInt& lhs, const ModInt& rhs) {return ModInt(lhs) -= rhs;}
	friend const ModInt operator*(const ModInt& lhs, const ModInt& rhs) {return ModInt(lhs) *= rhs;}
	friend const ModInt operator/(const ModInt& lhs, const ModInt& rhs) {return ModInt(lhs) /= rhs;}
	explicit operator int() const {return x;}
	friend ostream& operator<<(ostream& lhs, const ModInt& rhs) {
		lhs << rhs.x;
		return lhs;
	}
	friend istream& operator>>(istream& lhs, ModInt& rhs) {
		long long t;
		lhs >> t;
		rhs = ModInt(t);
		return lhs;
	}
};
using modint = ModInt<1000000007>;
//using modint = ModInt<998244353>;
modint operator"" _mi(unsigned long long lit) {
	return modint(lit % modint::M);
}
}; // mylib
using namespace mylib;