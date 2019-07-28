#include<bits/stdc++.h>

using namespace std;

namespace mylib {
template<int mod>
struct ModInt {
	using ll = long long;
	int x;
	const static int M = mod;
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
		x += -rhs;
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

template<class T>
struct ModComb {
	vector<T> fact;
	vector<T> facti;
	ModComb(int n) : fact(n+1), facti(n+1) {
		fact[0] = 1;
		for (int i = 1; i < n + 1; i++) {
			fact[i] = fact[i-1] * i;
		}
		facti[n] = 1 / fact[n];
		for (int i = n-1; i >= 0; i--) {
			facti[i] = facti[i+1] * (i + 1);
		}
	}
	T C(int n, int r) const {
		if(n < 0 || r < 0 || n < r) return 0;
		return fact[n] * facti[r] * facti[n-r];
	}
	T P(int n, int r) const {
		if(n < 0 || r < 0 || n < r) return 0;
		return fact[n] * facti[n-r];
	}
	T H(int n, int r) const {
		if(n < 0 || r < 0) return 0;
		return C(n + r - 1, r);
	}
};

using modcomb = ModComb<modint>;

int main() {
	modint res = 0;
	int H, W, A, B;
	cin >> H >> W >> A >> B;
	modcomb m(max(H, W) - 1);
	int r = H - A - 1;
	int c = B;
	for (; r >= 0 && c < W; r--, c++) {
		int C = W - c - 1;
		int R = H - r - 1;
		res += m.C(r + c, r) * m.C(R + C, R);
	}
	cout << res << endl;
}