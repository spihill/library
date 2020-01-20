// @title セグ木のモノイドを作る (VSCode スニペット)
template<class T>
struct ${1:monoid} {
	using mono = ${1:monoid};
	${1:monoid}() : ${1:monoid}(${2:T}()) {}
	explicit ${1:monoid}(${2:T} x) : val(x) {}
	${2:T} val;
	mono operator+(const mono& rhs) const {
		return mono(${3:val + rhs.val});
	}
	friend istream& operator>>(istream& lhs, mono& rhs) {
		lhs >> rhs.val;
		return lhs;
	}
	friend ostream& operator<<(ostream& lhs, mono& rhs) {
		lhs << rhs.val;
		return lhs;
	}
	using monoid_type = ${2:T};
};