/**
 * @title ModInt
 * @brief mod を取りながら計算する。リテラル型の要件を満たし、constexprに対応している。
 * @brief これでも Verify してます。 https://github.com/spihill/library/blob/master/test/mytest/ModInt.test.cpp
 */
namespace modint_n {
template<int mod>
struct ModInt {
	using i64 = int_fast64_t;
	int x;
	constexpr static int get_mod() {
		return mod;
	}
	constexpr ModInt(i64 x_) : x(mod_(x_)) {}
	constexpr ModInt() : ModInt(0) {}
	~ModInt() = default;
	inline constexpr ModInt& operator+=(const ModInt rhs) {
		i64 t = static_cast<i64>(x) + rhs.x;
		if (t >= mod) x = t - mod;
		else x = t;
		return (*this);
	}
	inline constexpr ModInt& operator-=(const ModInt rhs) {
		i64 t = static_cast<i64>(x) + mod - rhs.x;
		if (t >= mod) x = t - mod;
		else x = t;
		return *this;
	}
	inline constexpr ModInt& operator*=(const ModInt rhs) {
		x = static_cast<i64>(x) * rhs.x % mod;
		return *this;
	}
	inline constexpr ModInt& operator/=(ModInt rhs) {
		return *this *= rhs.inv();
	}
	inline constexpr ModInt power(i64 p) const {
		ModInt res = 1;
		ModInt a = x;
		for (; p; res = p & 1 ? res * a : res, a *= a, p >>= 1);
		return res;
	}
	inline constexpr ModInt inv() const {
		int z = 0, w = 0;
		extgcd(mod, x, z, w);
		return ModInt(w);
	}
	inline constexpr ModInt& operator=(const ModInt& rhs) {
		this->x = rhs.x;
		return *this;
	}
	inline constexpr int operator==(const ModInt& rhs) const {
		return this->x == rhs.x;
	}
	inline constexpr int operator!=(const ModInt& rhs) const {
		return !(*this == rhs);
	}
	inline constexpr ModInt operator++(signed unused) {
		ModInt res(*this);
		++(*this);
		return res;
	}
	inline constexpr ModInt& operator++() {
		(*this) += 1;
		return (*this);
	}
	inline constexpr ModInt operator--(signed unused) {
		ModInt res(*this);
		--(*this);
		return res;
	}
	inline constexpr ModInt& operator--() {
		(*this) -= 1;
		return (*this);
	}
	inline constexpr ModInt operator+() const {
		return (*this);
	}
	inline constexpr ModInt operator-() const {
		return (*this).x ? ModInt(mod - (*this).x) : ModInt(0);
	}
	friend constexpr ModInt operator+(const ModInt& lhs, const ModInt& rhs) {return ModInt(lhs) += rhs;}
	friend constexpr ModInt operator-(const ModInt& lhs, const ModInt& rhs) {return ModInt(lhs) -= rhs;}
	friend constexpr ModInt operator*(const ModInt& lhs, const ModInt& rhs) {return ModInt(lhs) *= rhs;}
	friend constexpr ModInt operator/(const ModInt& lhs, const ModInt& rhs) {return ModInt(lhs) /= rhs;}
	explicit constexpr operator int() const {return x;}
	friend ostream& operator<<(ostream& lhs, const ModInt& rhs) {
		lhs << rhs.x;
		return lhs;
	}
	friend istream& operator>>(istream& lhs, ModInt& rhs) {
		i64 t;
		lhs >> t;
		rhs = ModInt(t);
		return lhs;
	}
private:
	constexpr int extgcd(int a, int b, int& x, int& y) const {
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
		return static_cast<int>(x);
	}
};
}; // modint_n
using namespace modint_n;
namespace std {
template<int N> struct is_integral<ModInt<N>> {
	static constexpr integral_constant<bool, true> value = integral_constant<bool, true>();
};
template<int N> struct is_arithmetic<ModInt<N>> {
	static constexpr integral_constant<bool, true> value = integral_constant<bool, true>();
};
template<int N> struct is_scalar<ModInt<N>> {
	static constexpr integral_constant<bool, true> value = integral_constant<bool, true>();
};
template<int N> struct is_floating_point<ModInt<N>> {
	static constexpr integral_constant<bool, false> value = integral_constant<bool, false>();
};
template<int N> struct is_signed<ModInt<N>> {
	static constexpr integral_constant<bool, false> value = integral_constant<bool, false>();
};
template<int N> struct is_unsigned<ModInt<N>> {
	static constexpr integral_constant<bool, true> value = integral_constant<bool, true>();
};
} // namespace std
//using modint = ModInt<1000000007>;
//using modint = ModInt<998244353>;