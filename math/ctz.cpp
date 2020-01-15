struct lower_bit {
	using u64 = uint_fast64_t;
	u64 val[65];
	constexpr lower_bit() : val() {
		val[0] = 0;
		val[1] = 1;
		for (size_t i = 2; i < 65; i++) {
			val[i] = (val[i-1] << 1) | 1;
		}
	}
};
/**
 * @brief __builtin_ctz の代用関数で、下位何ビット0が連続しているかを返す
 */
template<class T>
constexpr enable_if_t<is_integral<T>::value, int> ctz(T x) {
	static_assert(numeric_limits<T>::digits < 65);
	constexpr auto lb = lower_bit();
	int ok = 0, ng = numeric_limits<T>::digits + 1;
	while (ng - ok != 1) {
		int mid = (ok + ng) >> 1;
		(lb.val[mid] & x ? ng : ok) = mid;
	}
	return ok;
}