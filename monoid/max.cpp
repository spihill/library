template<class T>
struct max_monoid {
	using mono = max_monoid;
	max_monoid() : max_monoid(numeric_limits<T>::min()) {}
	explicit max_monoid(T x) : val(x) {}
	T val;
	mono operator+(const mono& rhs) const noexcept {
		return mono(max(val, rhs.val));
	}
	friend istream& operator>>(istream& lhs, mono& rhs) {
		lhs >> rhs.val;
		return lhs;
	}
	friend ostream& operator<<(ostream& lhs, mono& rhs) {
		lhs << rhs.val;
		return lhs;
	}
	using monoid_type = T;
};