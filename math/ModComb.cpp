template<int mod>
struct ModComb {
	using ll = long long;
	vector<ll> fact;
	vector<ll> facti;
	ModComb(int n) {
		init(n);
	}
	void init(int n) {
		fact.resize(n);
		facti.resize(n);
		fact[0] = 1;
		for (int i = 1; i < n; i++) {
			fact[i] = fact[i-1] * i % mod;
		}
		facti[n-1] = po(fact[n-1], mod - 2);
		for (int i = n-2; i >= 0; i--) {
			facti[i] = facti[i+1] * (i + 1) % mod;
		}
	}
	ll nCr(int a, int b) {
		return (fact[a] * facti[b] % mod) * facti[a-b] % mod;
	}
	ll po(ll next, int cnt) {
		ll res = 1;
		if (cnt == 0) return 1;
		if (cnt & 1) res = res * next % mod;
		return res * po(next * next % mod, cnt >> 1) % mod;
	}
};
using modcomb = ModComb<1000000007>;
//using modcomb = ModComb<998244353>;
