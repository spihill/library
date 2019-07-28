struct $1
{
	$2 $5;
	$3 $6;
	$4 $7;
	$1($2 v1, $3 v2, $4 v3) : $5(v1), $6(v2), $7(v3) {}
	$1() {}
	bool operator<(const $1 r) const {
		if ($5 == r.$5) {
			if ($6 == r.$6) {
				return $7 < r.$7;
			} else {
				return $6 < r.$6;
			}
		} else {
			return $5 < r.$5;
		}
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