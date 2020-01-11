namespace mylib {
template<int mod>
struct ModInt {
	using i64 = int_fast64_t;
	int x;
	constexpr static int M = mod;
	constexpr ModInt(i64 x_) : x(mod_(x_)) {}
	constexpr ModInt() : ModInt(0) {}
	~ModInt() = default;
	inline ModInt& operator+=(const ModInt rhs) {
		i64 t = i64(x) + rhs.x;
		if (t >= mod) x = t - mod;
		else x = t;
		return (*this);
	}
	inline ModInt& operator-=(const ModInt rhs) {
		i64 t = i64(x) + mod - rhs.x;
		if (t >= mod) x = t - mod;
		else x = t;
		return *this;
	}
	inline ModInt& operator*=(const ModInt rhs) {
		x = i64(x) * rhs.x % mod;
		return *this;
	}
	inline ModInt& operator/=(ModInt rhs) {
		return *this *= rhs.inv();
	}
	inline ModInt power(i64 p) const {
		ModInt res = 1;
		ModInt a = x;
		for (; p; res = p & 1 ? res * a : res, a *= a, p >>= 1);
		return res;
	}
	inline ModInt inv() const {
		int z, w;
		extgcd(mod, x, z, w);
		return ModInt(w);
	}
	inline ModInt& operator=(const ModInt& rhs) {
		this->x = rhs.x;
		return *this;
	}
	inline int operator==(const ModInt& rhs) const {
		return this->x == rhs.x;
	}
	inline int operator!=(const ModInt& rhs) const {
		return !(*this == rhs);
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
private:
	int extgcd(int a, int b, int& x, int& y) const {
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
		return int(x);
	}
};
}; // mylib
using namespace mylib;
//using modint = ModInt<1000000007>;
//using modint = ModInt<998244353>;