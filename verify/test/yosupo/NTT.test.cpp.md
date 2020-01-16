---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :heavy_check_mark: test/yosupo/NTT.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/yosupo/NTT.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-17 01:32:20+09:00


* see: <a href="https://judge.yosupo.jp/problem/convolution_mod">https://judge.yosupo.jp/problem/convolution_mod</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/math/NTT.cpp.html">Number Theoretic Transform (NTT)</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include<bits/stdc++.h>

using namespace std;

#include "../../math/NTT.cpp"

int main() {
	int N, M;
	cin >> N >> M;
	vector<long long> a(N), b(M);
	for (int i = 0; i < N; i++) cin >> a[i];
	for (int i = 0; i < M; i++) cin >> b[i];
	NTT<0> ntt;
	auto c = ntt.convolution(a, b);
	for (int i = 0; i < N + M - 1; i++) {
		if (i) cout << " ";
		cout << c[i];
	}
	cout << endl;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yosupo/NTT.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include<bits/stdc++.h>

using namespace std;

#line 1 "test/yosupo/../../math/NTT.cpp"
/**
 * @title Number Theoretic Transform (NTT)
 * @brief 参考 https://math314.hateblo.jp/entry/2015/05/07/014908 https://lumakernel.github.io/ecasdqina/math/FFT/NTT https://ei1333.github.io/luzhiled/snippets/math/fast-fourier-transform.html
 */
namespace ntt_namespace {
struct NTT_PRIMES {
	int arr[25][2] = {
		{ 998244353,  3}, // 0  : 2^23 * 7 * 17 + 1
		{1811939329, 13}, // 1  : 2^26 * 27 + 1
		{ 469762049,  3}, // 2  : 2^26 * 7 + 1
		{ 167772161,  3}, // 3  : 2^25 * 5 + 1
		{1107296257, 10}, // 4  : 2^25 * 3 * 11 + 1
		{1711276033, 29}, // 5  : 2^25 * 3 * 17 + 1
		{ 754974721, 11}, // 6  : 2^24 * 11 + 1
		{1224736769,  3}, // 7  : 2^24 * 73 + 1
		{ 377487361,  7}, // 8  : 2^23 * 3^2 * 5 + 1
		{ 595591169,  3}, // 9  : 2^23 * 71 + 1
		{ 645922817,  3}, // 10 : 2^23 * 7 * 11 + 1
		{ 985661441,  3}, // 11 : 2^22 * 5 * 47 + 1
		{ 943718401,  7}, // 12 : 2^22 * 3^2 * 5^2 + 1
		{ 935329793,  3}, // 13 : 2^22 * 223 + 1
		{1012924417,  5}, // 14 : 2^21 * 3 * 7 * 23 + 1
		{1004535809,  3}, // 15 : 2^21 * 479 + 1
		{ 975175681, 17}, // 16 : 2^21 * 3 * 5 * 31 + 1
		{ 962592769,  7}, // 17 : 2^21 * 3^3 * 17 + 1
		{ 950009857,  7}, // 18 : 2^21 * 4 * 151 + 1
		{ 924844033,  5}, // 19 : 2^21 * 3^2 * 7^2 + 1
		{1053818881,  7}, // 20 : 2^20 * 3 * 5 * 67 + 1
		{1051721729,  6}, // 21 : 2^20 * 17 * 59 + 1
		{1045430273,  3}, // 22 : 2^20 * 997 + 1
		{1007681537,  3}, // 23 : 2^20 * 31^2 + 1
		{ 976224257,  3}, // 24 : 2^20 * 7^2 * 19 + 1
	};
	constexpr NTT_PRIMES() {}
};
template<int mod, int primitive_root>
struct NTT_ {
	using ll = long long;
	vector<int> rev, rts;
	int base;
	const int max_base, root;
	long long mod_pow(long long a, long long p) {
		a %= mod; if (a < 0) a += mod;
		long long res = 1;
		for (; p; p >>= 1) {
			if (p & 1) res = res * a % mod;
			a = a * a % mod;
		}
		return res;
	}
	constexpr int calc_max_base() {
		int tmp = mod - 1;
		int r = 0;
		while ((tmp & 1) == 0) tmp >>= 1, r++;
		return r;
	}
	constexpr int calc_root(const int mb) {
		int r = 2;
		while (mod_pow(r, (mod - 1) >> 1) == 1) ++r;
		assert(mod_pow(r, mod - 1) == 1);
		return mod_pow(r, (mod - 1) >> mb);
	}
	NTT_() : rev{0, 1}, rts{0, 1}, base(1), max_base(calc_max_base()), root(calc_root(max_base)) {
		assert(mod >= 3 && mod % 2 == 1);
	} 
	void ensure_base(int nbase) {
		if (nbase <= base) return;
		assert(nbase <= max_base);
		rev.resize(1 << nbase);
		rts.resize(1 << nbase);
		for (int i = 0; i < (1 << nbase); i++) {
			rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));
		}
		while (base < nbase) {
			ll z = mod_pow(root, 1 << (max_base - 1 - base));
			for(int i = 1 << (base - 1); i < (1 << base); i++) {
				rts[i << 1] = rts[i];
				rts[(i << 1) + 1] = rts[i] * z % mod;
			}
			++base;
		}
	}
	long long mod_inv(long long a) {
		long long b = mod, u = 1, v = 0;
		while (b) {
			long long t = a / b;
			a -= t * b; swap(a, b);
			u -= t * v; swap(u, v);
		}
		u %= mod; 
		if (u < 0) u += mod;
		return u;
	}
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
		ll h = mod_pow(primitive_root, mod_inv(-n));
		if (sign == -1) h = mod_inv(h);
		bit_reverse(f);
		for (int m = 1; m < n; m*= 2) {
			const int m2 = 2 * m;
			const ll base = mod_pow(h, n / m2);
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
		const long long n_inv = mod_inv(f.size());
		for (auto& x: f) x = x * n_inv % mod;
	}
	template<class T>
	inline vector<ll> convolution(const vector<T>& f, const vector<T>& g) {
		vector<ll> res;
		convolution(f, g, res);
		return res;
	}
	template<class T>
	inline void convolution(const vector<T>& f, const vector<T>& g, vector<ll>& res) {
		int need = f.size() + g.size() - 1;
		int nbase = 1;
		while((1 << nbase) < need) nbase++;
		ensure_base(nbase);
		int sz = 1 << nbase;
 		vector<ll> f_(f.begin(), f.end()), g_(g.begin(), g.end());
 		f_.resize(sz); g_.resize(sz); res.clear(); res.resize(sz);
		for (auto& x : f_) x %= mod;
		for (auto& x : g_) x %= mod;
		ntt(f_);
		ntt(g_);
		int inv_sz = mod_inv(sz);
		for(int i = 0; i < sz; i++) {
			res[i] = f_[i] * (g_[i] * inv_sz % mod) % mod;
		}
		reverse(res.begin() + 1, res.end());
		ntt(res);
		res.resize(need);
	}
};
constexpr long long mod_inv(long long a, const int M) {
	long long res = 1;
	for (int p = M - 2; p; p >>= 1, a = a * a % M) {
		if (p & 1) res = res * a % M;
	}
	return res;
}
template<int mod_select>
struct NTT : NTT_<NTT_PRIMES().arr[mod_select][0], NTT_PRIMES().arr[mod_select][1]> {};

template<int mod>
struct ANY_MOD_NTT {
	using ll = long long;
	template<class T, int np1 = 3, int np2 = 8, int np3 = 9>
	inline vector<ll> convolution(const vector<T>& f, const vector<T>& g) {
		vector<ll> res;
		convolution(f, g, res);
		return res;
	}
	template<class T, int np1 = 3, int np2 = 8, int np3 = 9>
	inline void convolution(const vector<T>& f, const vector<T>& g, vector<ll>& res) {
		NTT<np1> ntt1;
		NTT<np2> ntt2;
		NTT<np3> ntt3;
		vector<T> f_(f), g_(g);
		for (auto& x : f_) { x %= mod; if (x < 0) x += mod; }
		for (auto& x : g_) { x %= mod; if (x < 0) x += mod; }
		vector<ll> h1; ntt1.convolution(f_, g_, h1);
		vector<ll> h2; ntt2.convolution(f_, g_, h2);
		vector<ll> h3; ntt3.convolution(f_, g_, h3);
		constexpr ll m1 = NTT_PRIMES().arr[np1][0];
		constexpr ll m2 = NTT_PRIMES().arr[np2][0];
		constexpr ll m3 = NTT_PRIMES().arr[np3][0];
		constexpr ll m1_inv_m2 = mod_inv(m1, m2);
		constexpr ll m12_inv_m3 = mod_inv(m1 * m2 % m3, m3);
		constexpr ll m12_mod = m1 * m2 % mod;
		const int sz = f.size() + g.size() - 1;
		res.clear(); res.resize(sz);
		for (int i = 0; i < sz; i++) {
			ll v1 = (h2[i] - h1[i]) * m1_inv_m2 % m2;
			if (v1 < 0) v1 += m2;
			ll v2 = (h3[i] - (h1[i] + m1 * v1) % m3) * m12_inv_m3 % m3;
			if (v2 < 0) v2 += m3;
			res[i] = (h1[i] + m1 * v1 + m12_mod * v2) % mod;
		}
	}
};
}
using namespace ntt_namespace;#line 8 "test/yosupo/NTT.test.cpp"

int main() {
	int N, M;
	cin >> N >> M;
	vector<long long> a(N), b(M);
	for (int i = 0; i < N; i++) cin >> a[i];
	for (int i = 0; i < M; i++) cin >> b[i];
	NTT<0> ntt;
	auto c = ntt.convolution(a, b);
	for (int i = 0; i < N + M - 1; i++) {
		if (i) cout << " ";
		cout << c[i];
	}
	cout << endl;
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

