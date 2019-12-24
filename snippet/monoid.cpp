template<class T, T UNITY>
struct monoid {
	monoid operator+(const monoid& rhs) const noexcept; // {return monoid(val + rhs.val);}
	monoid() : val(UNITY) {}
	explicit monoid(T x) : val(x) {}
	T val;
	bool operator<(const monoid& rhs) const noexcept {return val < rhs.val;}
	bool operator>(const monoid& rhs) const noexcept {return rhs < *this;}
	bool operator<=(const monoid& rhs) const noexcept {return !(rhs < *this);}
	bool operator>=(const monoid& rhs) const noexcept {return !(*this < rhs);}
	bool operator==(const monoid& rhs) const noexcept {return !(*this < rhs) && !(rhs < *this);}
	bool operator!=(const monoid& rhs) const noexcept {return *this < rhs || rhs < *this;}
	friend istream& operator>>(istream& lhs, monoid& rhs) {
		lhs >> rhs.val;
		return lhs;
	}
	friend ostream& operator<<(ostream& lhs, monoid& rhs) {
		lhs << rhs.val;
		return lhs;
	}
	using monoid_type = T;
};