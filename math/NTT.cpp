#include <bits/stdc++.h>

using namespace std;

namespace ntt_namespace {
long long mod_pow(long long a, long long p, long long mod) {
	a %= mod; if (a < 0) a += mod;
	long long res = 1;
	for (; p; p >>= 1) {
		if (p == -1) exit(1);
		if (p & 1) res = res * a % mod;
		a = a * a % mod;
	}
	return res;
}
long long mod_inv(long long a, long long mod) {
	return mod_pow(a, mod - 2, mod);
}
template<int mod_select>
struct NTT {
	const int NTT_PRIMES[18][2] = {
		{998244353, 3},  // 0  : 2^23 * 7 * 17 + 1
		{1224736769, 3}, // 1  : 2^24 * 73 + 1,
		{1053818881, 7}, // 2  : 2^20 * 3 * 5 * 67 + 1
		{1051721729, 6}, // 3  : 2^20 * 17 * 59 + 1
		{1045430273, 3}, // 4  : 2^20 * 997 + 1
		{1012924417, 5}, // 5  : 2^21 * 3 * 7 * 23 + 1
		{1007681537, 3}, // 6  : 2^20 * 31^2 + 1
		{1004535809, 3}, // 7  : 2^21 * 479 + 1
		{985661441, 3},  // 8  : 2^22 * 5 * 47 + 1
		{976224257, 3},  // 9  : 2^20 * 7^2 * 19 + 1
		{975175681, 17}, // 10 : 2^21 * 3 * 5 * 31 + 1
		{962592769, 7},  // 11 : 2^21 * 3^3 * 17 + 1
		{950009857, 7},  // 12 : 2^21 * 4 * 151 + 1
		{943718401, 7},  // 13 : 2^22 * 3^2 * 5^2 + 1
		{935329793, 3},  // 14 : 2^22 * 223 + 1
		{924844033, 5},  // 15 : 2^21 * 3^2 * 7^2 + 1
		{469762049, 3},  // 16 : 2^26 * 7 + 1
		{167772161, 3},  // 17 : 2^25 * 5 + 1
	};
	using ll = long long;
	const int mod;
	const int primitive_root;
	NTT() : mod(NTT_PRIMES[mod_select][0]), primitive_root(NTT_PRIMES[mod_select][1]) {} 
	inline void bit_reverse(vector<ll>& f) {
		const int n = f.size();
		int i = 0;
		for (int j = 1; j < n-1; j++) {
			for (int k = n >> 1; k > (i ^= k); k >>= 1);
			if (j < i) swap(f[i], f[j]);
		}
	}
	void _ntt(vector<ll>& f, int sign) {
		const int n = f.size();
		assert((n ^ (n&-n)) == 0);
		const int g = primitive_root;
		ll h = mod_pow(g, mod_inv(-n, mod), mod);
		if (sign == -1) h = mod_inv(h, mod);
		bit_reverse(f);
		for (int m = 1; m < n; m*= 2) {
			const int m2 = 2 * m;
			const ll base = mod_pow(h, n / m2, mod);
			ll w = 1;
			for (ll x = 0; x < m; x++) {
				for (ll s = x; s < n; s += m2) {
					ll u = f[s];
					ll d = f[s + m] * w % mod;
					f[s] = (u + d) % mod;
					f[s + m] = (u - d + mod) % mod;
				}
				w = w * base % mod;
			}
		}
		for (auto& x : f) if (x < 0) x += mod;
	}
	void ntt(vector<ll>& f) {
		_ntt(f, 1);
	}
	void intt(vector<ll>& f) {
		_ntt(f, -1);
		const long long n_inv = mod_inv(f.size(), mod);
		for (auto& x: f) x = x * n_inv % mod;
	}
	template<class T>
	vector<T> convolution(const vector<T>& f, const vector<T>& g) {
		ll sz = 1;
		while (sz < (ll) (f.size() + g.size())) sz *= 2;
		vector<ll> _f(f.begin(), f.end()), _g(g.begin(), g.end());
		_f.resize(sz); _g.resize(sz);
		for (auto& x : _f) x %= mod;
		for (auto& x : _g) x %= mod;
		ntt(_f); 
		ntt(_g);
		for (ll i = 0; i < sz; i++) _f[i] = _f[i] * _g[i] % mod;
		intt(_f);
		vector<T> res(_f.begin(), _f.end());
		return res;
	}
};

long long garner_(vector<long long>& hs, vector<int>& mods) {
	int M = hs.size();
	vector<long long> coeffs(M, 1), constants(M, 0);
	for (int i = 0; i < M-1; i++) {
		int mod_i = mods[i];
		long long v = (hs[i] - constants[i] + mod_i) % mod_i;
		v = (v * mod_inv(coeffs[i], mod_i)) % mod_i;
		for (int j = i+1; j < M; j++) {
			int mod_j = mods[j];
			constants[j] = (constants[j] + coeffs[j] * v) % mod_j;
			coeffs[j] = (coeffs[j] * mod_i) % mod_j;
		}
	}
	return constants.back();
}

vector<long long> mod_convolution(const vector<long long>& f, const vector<long long>& g, int mod) {
	NTT<1> ntt1;
	NTT<2> ntt2;
	NTT<3> ntt3;
	vector<long long> h1 = ntt1.convolution(f, g);
	vector<long long> h2 = ntt2.convolution(f, g);
	vector<long long> h3 = ntt3.convolution(f, g);
	vector<long long> res(h1.size());
	vector<int> mods{ntt1.mod, ntt2.mod, ntt3.mod, mod};
	for (int i = 0; i < (int) h1.size(); i++) {
		vector<long long> hs{h1[i], h2[i], h3[i], 0};
		res[i] = garner_(hs, mods);
	}
	return res;
}
}
using namespace ntt_namespace;