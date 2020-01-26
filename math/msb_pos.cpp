struct upper_bit {
	using u64 = uint_fast64_t;
	u64 val[65];
	constexpr upper_bit() : val() {
		val[64] = 0;
		val[63] = u64(1) << 63;
		for (size_t i = 62; ~i; i--) {
			val[i] = (val[i+1] >> 1) | val[63];
		}
	}
};
/**
 * @title msb の位置を調べる
 * @brief __lg の代用関数で、msb が何桁目かを返す (0-indexed で msb が無い場合は -1) ($O(\log \log N)$)
 */
template<class T>
constexpr enable_if_t<is_integral<T>::value, int> msb_pos(T x) {
	static_assert(numeric_limits<make_unsigned_t<T>>::digits < 65, "");
	constexpr auto ub = upper_bit();
	int ok = numeric_limits<make_unsigned_t<T>>::digits, ng = -1;
	while (ok - ng != 1) {
		int mid = (ok + ng) >> 1;
		(ub.val[mid] & x ? ng : ok) = mid;
	}
	return ok - 1;
}