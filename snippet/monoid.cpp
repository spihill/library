template<class T>
struct ${1:monoid} {
	using mono = ${1:monoid};
	${1:monoid}() : ${1:monoid}(T()) {}
	explicit ${1:monoid}(T x) : val(x) {}
	T val;
	mono operator+(const mono& rhs) const noexcept {
		return mono(val + rhs.val);
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