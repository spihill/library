struct $1
{
	$2 $7;
	$3 $8;
	$4 $9;
	$5 $10; 
	$6 $11;
	$1($2 v1, $3 v2, $4 v3, $5 v4, $6 v5) : $7(v1), $8(v2), $9(v3), $10(v4), $11(v5) {}
	$1() {}
	bool operator<(const $1 r) const {
		if ($7 == r.$7) {
			if ($8 == r.$8) {
				if ($9 == r.$9) {
					if ($10 == r.$10) {
						return $11 < r.$11;
					} else {
						return $10 < r.$10;
					}
				} else {
					return $9 < r.$9;
				}
			} else {
				return $8 < r.$8;
			}
		} else {
			return $7 < r.$7;
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