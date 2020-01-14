namespace modcomb_compiletime_n {
constexpr int N = 200000;
constexpr int mod = modint::M;
struct Fact {
	int_fast32_t val[N+1];
	int_fast32_t vali[N+1];
	constexpr Fact() : val() , vali() {
		val[0] = 1;
		for (int_fast32_t i = 1; i <= N; i++) val[i] = static_cast<int_fast64_t>(val[i-1]) * i % mod;
		vali[N] = static_cast<int_fast32_t>(modint(val[N]).inv().x);
		for (int_fast32_t i = N; i; i--) vali[i-1] = static_cast<int_fast64_t>(vali[i]) * i % mod;
	}
};
constexpr auto fact = Fact();
constexpr modint nCr(int n, int r) {
	assert(n <= N+1);
	if(n < 0 || r < 0 || n < r) return 0;
	return modint(fact.val[n]) * fact.vali[r] * fact.vali[n-r];
}
constexpr modint nPr(int n, int r) {
	assert(n <= N+1);
	if(n < 0 || r < 0 || n < r) return 0;
	return modint(fact.val[n]) * fact.vali[n-r];
}
constexpr modint nHr(int n, int r) {
	if(n < 0 || r < 0) return 0;
	return nCr(n + r - 1, r);
}
} // namespace modcomb_compiletime_n
using namespace modcomb_compiletime_n;