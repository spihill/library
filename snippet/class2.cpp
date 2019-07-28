struct $1
{
	$2 $4;
	$3 $5;
	$1($2 v1, $3 v2) : $4(v1), $5(v2) {}
	$1() {}
	bool operator<(const $1 r) const {
		return $4 == r.$4 ? $5 < r.$5 : $4 < r.$4;
	}
	bool operator>(const $1 r) const {
		return r < *this;
	}
	bool operator>=(const $1 r) const {
		return !(*this < r);
	}
	bool operator<=(const $1 r) const {
		return !(r < *this);
	}
	bool operator==(const $1 r) const {
		return !(r < *this) && !(*this < r);
	}
	bool operator!=(const $1 r) const {
		return (r < *this) || (*this < r);
	}
};