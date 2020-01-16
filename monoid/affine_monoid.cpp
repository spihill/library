template<class T>
struct affine_monoid {
	using mono = affine_monoid;
	affine_monoid() : affine_monoid(pair<T, T>(1, 0)) {}
	explicit affine_monoid(pair<T, T> x) : val(x) {}
	pair<T, T> val;
	mono operator+(const mono& rhs) const {
		return mono(pair<T, T>(rhs.val.first * val.first, rhs.val.first * val.second + rhs.val.second));
	}
	friend istream& operator>>(istream& lhs, mono& rhs) {
		lhs >> rhs.val.first >> rhs.val.second;
		return lhs;
	}
	friend ostream& operator<<(ostream& lhs, mono& rhs) {
		lhs << rhs.val.first << ' ' << rhs.val.second;
		return lhs;
	}
	using monoid_type = pair<T, T>;
};