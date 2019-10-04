#include <bits/stdc++.h>

using namespace std;

namespace convs {
template<class T=complex<double>>
struct FFT {
	vector<vector<T>> power;
	FFT(int N) {
		int x = 1, B = 1;
		while (x < N) x <<= 1, B++;
		power.resize(B+1);
		for (int i = 0; i < B+1; i++) {
			int sz = 1 << i;
			power[i].resize(sz);
			for (int j = 0; j < sz; j++) power[i][j] = polar(1.0, 2*M_PI*j/sz);
		}
	}
	void DFT(typename vector<T>::iterator F, typename vector<T>::iterator t, int p) {
		if (p == 0) return;
		const int n = power[p].size();
		const int half = power[p-1].size();
		for (int i = 0; i < half; i++) {
			t[i] = F[2*i]; t[i+half] = F[2*i+1];
		}
		DFT(t, F, p-1); DFT(t+half, F, p-1);
		for (int i = 0; i < half; i++) {
			F[i] = t[i] + power[p][i] * t[i+half];
		}
		for (int i = half, j = 0; i < n; i++, j++) {
			F[i] = t[j] + power[p][i] * t[j+half];
		}
	}
	template<class U>
	vector<U> convolution(const vector<U>& f, const vector<U>& g) {
		int n = f.size() + g.size() - 1;
		int sz = 1;
		int p = 0;
		while (sz < n) sz <<= 1, p++;
		vector<T> cf(f.begin(), f.end());
		vector<T> cg(g.begin(), g.end());
		cf.resize(sz);
		cg.resize(sz);
		vector<T> tmp(sz);
		DFT(cf.begin(), tmp.begin(), p);
		DFT(cg.begin(), tmp.begin(), p);
		for (int i = 0; i < sz; i++) cf[i] = conj(cf[i] * cg[i]) / (double) sz;
		DFT(cf.begin(), tmp.begin(), p);
		vector<U> res(sz);
		for (int i = 0; i < sz; i++) res[i] = (int) (cf[i].real() + 0.5);
		return res;
	}
};
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
		{1224736769, 3}, // 0  : 2^24 * 73 + 1,
		{1053818881, 7}, // 1  : 2^20 * 3 * 5 * 67 + 1
		{1051721729, 6}, // 2  : 2^20 * 17 * 59 + 1
		{1045430273, 3}, // 3  : 2^20 * 997 + 1
		{1012924417, 5}, // 4  : 2^21 * 3 * 7 * 23 + 1
		{1007681537, 3}, // 5  : 2^20 * 31^2 + 1
		{1004535809, 3}, // 6  : 2^21 * 479 + 1
		{998244353, 3},  // 7  : 2^23 * 7 * 17 + 1
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
		while (sz < f.size() + g.size()) sz *= 2;
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
	NTT<0> ntt1;
	NTT<1> ntt2;
	NTT<2> ntt3;
	vector<long long> h1 = ntt1.convolution(f, g);
	vector<long long> h2 = ntt2.convolution(f, g);
	vector<long long> h3 = ntt3.convolution(f, g);
	vector<long long> res(h1.size());
	vector<int> mods{ntt1.mod, ntt2.mod, ntt3.mod, mod};
	for (int i = 0; i < h1.size(); i++) {
		vector<long long> hs{h1[i], h2[i], h3[i], 0};
		res[i] = garner_(hs, mods);
	}
	return res;
}
}
using namespace convs;

int main() {
	int N, M;
	cin >> N >> M;
	vector<long long> a(N), b(M);
	for (int i = 0; i < N; i++) cin >> a[i];
	for (int i = 0; i < M; i++) cin >> b[i];
	NTT<7> ntt;
	auto c = ntt.convolution(a, b);
	for (int i = 0; i < N + M - 1; i++) {
		if (i) cout << " ";
		cout << c[i];
	}
	cout << endl;
}