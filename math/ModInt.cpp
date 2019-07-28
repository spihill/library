template<int mod> struct ModInt {
	using ll = long long;
	int x;
	template<class T>
	ModInt(T a) {
		x = a % mod;
		if (x < 0) {
			x += mod;
		}
	}
	ModInt() : x(0) {}
	inline ModInt& operator+=(const ModInt& rhs)
	{
		(*this) += rhs.x;
		return *this;
	}
	template<class T>
	inline ModInt& operator+=(const T rhs)
	{
		x += rhs % mod;
		if (x < 0) x += mod;
		x %= mod;
		return *this;
	}
	inline ModInt& operator-=(const ModInt& rhs)
	{
		(*this) -= rhs.x;
		return *this;
	}
	template<class T>
	inline ModInt& operator-=(const T rhs)
	{
		x -= rhs % mod;
		if (x < 0) x += mod;
		x %= mod;
		return *this;
	}
	inline ModInt& operator*=(const ModInt& rhs)
	{
		(*this) *= rhs.x;
		return *this;
	}
	template<class T>
	inline ModInt& operator*=(const T rhs)
	{
		ll res = (ll) x * (rhs % mod);
		x = res % mod;
		if (x < 0) x += mod;
		return *this;
	}
	inline ModInt& operator/=(const ModInt& rhs)
	{
		(*this) /= rhs.x;
		return *this;
	}
	template<class T>
	inline ModInt& operator/=(const T rhs)
	{
		int t = rhs % mod;
		if (t < 0) t += mod;
		ll res = modpow(t);
		(*this) *= res;
		return *this;
	}
	inline ModInt& operator=(const ModInt& rhs)
	{
		(*this) = rhs.x;
		return *this;
	}
	template<class T>
	inline ModInt& operator=(const T rhs)
	{
		x = rhs % mod;
		if (x < 0) x += mod;
		return *this;
	}
	inline int operator==(const ModInt& rhs) const
	{
		return (*this) == rhs.x;
	}
	template<class T>
	inline int operator==(const T rhs) const
	{
		ModInt t(rhs);
		return (*this).x == t.x;
	}
	inline int operator!=(const ModInt& rhs) const
	{
		return (*this) != rhs.x;
	}
	inline int operator!=(const int rhs) const
	{
		ModInt t(rhs);
		return (*this).x != t.x;
	}
	inline ModInt operator++(signed unused)
	{
		ModInt res((*this).x);
		++(*this);
		return res;
	}
	inline ModInt& operator++()
	{
		(*this) += 1;
		return (*this);
	}
	inline ModInt operator--(signed unused)
	{
		ModInt res((*this).x);
		--(*this);
		return res;
	}
	inline ModInt& operator--()
	{
		(*this) -= 1;
		return (*this);
	}
	inline ModInt operator+() const
	{
		return (*this);
	}
	inline ModInt operator-() const
	{
		return (*this).x ? ModInt(mod - (*this).x) : ModInt(0);
	}
	template<class T>
	int modpow(const T val, int p = mod - 2)
	{
		if (p == 0) return 1;
		if (p % 2) return (long long) val * modpow(val, p-1) % mod;
		long long t = modpow(val, p/2);
		int res = t * t % mod;
		return res;
	}
	operator int() const
	{
		return x;
	}
	friend ostream& operator<<(ostream& lhs, const ModInt& rhs)
	{
		lhs << rhs.x;
		return lhs;
	}
	friend istream& operator>>(istream& lhs, ModInt& rhs)
	{
		long long t;
		lhs >> t;
		rhs.x = t % mod;
		if (rhs.x < 0) rhs += mod;
		return lhs;
	}
	friend const ModInt operator+(const ModInt& lhs, const ModInt& rhs)  {return ModInt(lhs) += rhs;}
	template<class T>
	friend const ModInt operator+(const ModInt& lhs, const T rhs)        {return ModInt(lhs) += rhs;}
	template<class T>
	friend const ModInt operator+(T lhs, const ModInt& rhs)              {return ModInt(lhs) += rhs;}
	friend const ModInt operator-(const ModInt& lhs, const ModInt& rhs)  {return ModInt(lhs) -= rhs;}
	template<class T>
	friend const ModInt operator-(const ModInt& lhs, const T rhs)        {return ModInt(lhs) -= rhs;}
	template<class T>
	friend const ModInt operator-(T lhs, const ModInt& rhs)              {return ModInt(lhs) -= rhs;}
	friend const ModInt operator*(const ModInt& lhs, const ModInt& rhs)  {return ModInt(lhs) *= rhs;}
	template<class T>
	friend const ModInt operator*(const ModInt& lhs, const T rhs)        {return ModInt(lhs) *= rhs;}
	template<class T>
	friend const ModInt operator*(T lhs, const ModInt& rhs)              {return ModInt(lhs) *= rhs;}
	friend const ModInt operator/(const ModInt& lhs, const ModInt& rhs)  {return ModInt(lhs) /= rhs;}
	template<class T>
	friend const ModInt operator/(const ModInt& lhs, const T rhs)        {return ModInt(lhs) /= rhs;}
	template<class T>
	friend const ModInt operator/(T lhs, const ModInt& rhs)              {return ModInt(lhs) /= rhs;}
	template<class T>
	friend const int    operator==(T lhs, const ModInt& rhs)             {return ModInt(lhs) == rhs;}
	template<class T>
	friend const int    operator!=(T lhs, const ModInt& rhs)             {return ModInt(lhs) != rhs;}
};
using modint = ModInt<1000000007>;
//using modint = ModInt<998244353>;
