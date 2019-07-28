struct $1
{
	$2 $6;
	$3 $7;
	$4 $8;
	$5 $9; 
	$1($2 v1, $3 v2, $4 v3, $5 v4) : $6(v1), $7(v2), $8(v3) , $9(v4) {}
	$1() {}
	bool operator<(const $1 r) const {
		if ($6 == r.$6) {
			if ($7 == r.$7) {
				if ($8 == r.$8) {
					return $9 < r.$9;
				} else {
					return $8 < r.$8;
				}
			} else {
				return $7 < r.$7;
			}
		} else {
			return $6 < r.$6;
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