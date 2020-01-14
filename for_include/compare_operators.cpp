	inline bool operator>(const type& rhs) const { return rhs < *this; }
	inline bool operator>=(const type& rhs) const { return !(*this < rhs); }
	inline bool operator<=(const type& rhs) const { return !(rhs < *this); }
	inline bool operator==(const type& rhs) const { return !(*this < rhs) && !(rhs < *this); }
	inline bool operator!=(const type& rhs) const { return (*this < rhs) || (rhs < *this); }