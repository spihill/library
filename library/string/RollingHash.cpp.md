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
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: string/RollingHash.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#b45cffe084dd3d20d928bee85e7b0f21">string</a>
* <a href="{{ site.github.repository_url }}/blob/master/string/RollingHash.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-27 00:45:39+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/RollingHash.test.cpp.html">test/aoj/RollingHash.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
namespace rolling_hash {
struct Random_CompileTime {
	using result_type = uint_fast64_t;
	result_type x;
	static constexpr result_type min() {return 0u;}
	static constexpr result_type max() {return UINT64_MAX;}
	constexpr Random_CompileTime(result_type a) : x(a) {}
	constexpr Random_CompileTime(const char* s) : x(hash(s)) {}
	constexpr result_type hash(const char* s) {
		result_type res = 12892336203476015591u;
		result_type mul = 8106227557068529123u;
		result_type bit = 9599045418537513223u;
		const result_type prime = (1UL << 61) - 1;
		for (int i = 0; s[i] != '\0'; i++) {
			res += (result_type(s[i]) * mul) ^ bit;
			mul = (mul * prime) ^ 12664609216090335137u;
			bit = (bit * prime) ^ mul;
		}
		return res;
	}
	constexpr uint_fast32_t get_base() {
		x = x ^ (x << 13); x = x ^ (x >> 7);
		return uint_fast32_t(((x ^ (x << 17)) & ((1 << 27) - 1)) + 7647103u);
	}
};
template<uint_fast32_t max_len, uint_fast32_t base = Random_CompileTime(__TIME__).get_base(), uint_fast64_t mod = (1UL << 61) - 1, uint_fast64_t MASK30 = (1UL << 30) - 1, uint_fast64_t MASK31 = (1UL << 31) - 1>
struct RollingHash {
	using hash_type = uint_fast64_t;
	int sz;
	vector<hash_type> hash;
	static array<hash_type, max_len+1> power;
	RollingHash(const string& s) : sz(s.length()), hash(sz + 1, 0) {
		static_assert(218810 <= base, "");
		for (int i = 0; i < sz; i++) {
			hash[i+1] = calc_mod(mul(hash[i], base) + s[i]);
		}
	}
	inline hash_type mul(hash_type a, hash_type b) {
		hash_type au = a >> 31;
		hash_type ad = a & MASK31;
		hash_type bu = b >> 31;
		hash_type bd = b & MASK31;
		hash_type mid = ad * bu + au * bd;
		return ((au * bu) << 1) + ad * bd + ((mid & MASK30) << 31) + (mid >> 30);
	}
	inline hash_type calc_mod(hash_type a) {
		a = (a & mod) + (a >> 61);
		if (a >= mod) a -= mod;
		return a;
	}
	inline hash_type get(int l, int r) {
		return calc_mod(hash[r] + mod * 7 - mul(hash[l], power[r-l]));
	}
	inline hash_type connect(hash_type h1, hash_type h2, int h2_len) {
		return calc_mod(mul(h1, power[h2_len]) + h2);
	}
	inline hash_type connect(int l1, int r1, int l2, int r2) {
		return connect(get(l1, r1), get(l2, r2), r2 - l2);
	}
};
template<uint_fast32_t max_len, uint_fast32_t base, uint_fast64_t mod, uint_fast64_t MASK30, uint_fast64_t MASK31>
struct PowCalc {
	using hash_type = typename RollingHash<max_len, base, mod, MASK30, MASK31>::hash_type;
	array<hash_type, max_len+1> power;
	constexpr hash_type mul(hash_type a, hash_type b) {
		hash_type au = a >> 31;
		hash_type ad = a & MASK31;
		hash_type bu = b >> 31;
		hash_type bd = b & MASK31;
		hash_type mid = ad * bu + au * bd;
		return ((au * bu) << 1) + ad * bd + ((mid & MASK30) << 31) + (mid >> 30);
	}
	constexpr hash_type calc_mod(hash_type a) {
		a = (a & mod) + (a >> 61);
		if (a >= mod) a -= mod;
		return a;
	}
	constexpr PowCalc() {
		power[0] = 1;
		for (uint_fast32_t i = 0; i < max_len; i++) {
			power[i+1] = calc_mod(mul(power[i], base));
		}
	}
};
template<uint_fast32_t a, uint_fast32_t b, uint_fast64_t c, uint_fast64_t d, uint_fast64_t e>
array<typename RollingHash<a, b, c, d, e>::hash_type, a+1> RollingHash<a, b, c, d, e>::power = PowCalc<a, b, c, d, e>().power;
} 
using namespace rolling_hash;
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "string/RollingHash.cpp"
namespace rolling_hash {
struct Random_CompileTime {
	using result_type = uint_fast64_t;
	result_type x;
	static constexpr result_type min() {return 0u;}
	static constexpr result_type max() {return UINT64_MAX;}
	constexpr Random_CompileTime(result_type a) : x(a) {}
	constexpr Random_CompileTime(const char* s) : x(hash(s)) {}
	constexpr result_type hash(const char* s) {
		result_type res = 12892336203476015591u;
		result_type mul = 8106227557068529123u;
		result_type bit = 9599045418537513223u;
		const result_type prime = (1UL << 61) - 1;
		for (int i = 0; s[i] != '\0'; i++) {
			res += (result_type(s[i]) * mul) ^ bit;
			mul = (mul * prime) ^ 12664609216090335137u;
			bit = (bit * prime) ^ mul;
		}
		return res;
	}
	constexpr uint_fast32_t get_base() {
		x = x ^ (x << 13); x = x ^ (x >> 7);
		return uint_fast32_t(((x ^ (x << 17)) & ((1 << 27) - 1)) + 7647103u);
	}
};
template<uint_fast32_t max_len, uint_fast32_t base = Random_CompileTime(__TIME__).get_base(), uint_fast64_t mod = (1UL << 61) - 1, uint_fast64_t MASK30 = (1UL << 30) - 1, uint_fast64_t MASK31 = (1UL << 31) - 1>
struct RollingHash {
	using hash_type = uint_fast64_t;
	int sz;
	vector<hash_type> hash;
	static array<hash_type, max_len+1> power;
	RollingHash(const string& s) : sz(s.length()), hash(sz + 1, 0) {
		static_assert(218810 <= base, "");
		for (int i = 0; i < sz; i++) {
			hash[i+1] = calc_mod(mul(hash[i], base) + s[i]);
		}
	}
	inline hash_type mul(hash_type a, hash_type b) {
		hash_type au = a >> 31;
		hash_type ad = a & MASK31;
		hash_type bu = b >> 31;
		hash_type bd = b & MASK31;
		hash_type mid = ad * bu + au * bd;
		return ((au * bu) << 1) + ad * bd + ((mid & MASK30) << 31) + (mid >> 30);
	}
	inline hash_type calc_mod(hash_type a) {
		a = (a & mod) + (a >> 61);
		if (a >= mod) a -= mod;
		return a;
	}
	inline hash_type get(int l, int r) {
		return calc_mod(hash[r] + mod * 7 - mul(hash[l], power[r-l]));
	}
	inline hash_type connect(hash_type h1, hash_type h2, int h2_len) {
		return calc_mod(mul(h1, power[h2_len]) + h2);
	}
	inline hash_type connect(int l1, int r1, int l2, int r2) {
		return connect(get(l1, r1), get(l2, r2), r2 - l2);
	}
};
template<uint_fast32_t max_len, uint_fast32_t base, uint_fast64_t mod, uint_fast64_t MASK30, uint_fast64_t MASK31>
struct PowCalc {
	using hash_type = typename RollingHash<max_len, base, mod, MASK30, MASK31>::hash_type;
	array<hash_type, max_len+1> power;
	constexpr hash_type mul(hash_type a, hash_type b) {
		hash_type au = a >> 31;
		hash_type ad = a & MASK31;
		hash_type bu = b >> 31;
		hash_type bd = b & MASK31;
		hash_type mid = ad * bu + au * bd;
		return ((au * bu) << 1) + ad * bd + ((mid & MASK30) << 31) + (mid >> 30);
	}
	constexpr hash_type calc_mod(hash_type a) {
		a = (a & mod) + (a >> 61);
		if (a >= mod) a -= mod;
		return a;
	}
	constexpr PowCalc() {
		power[0] = 1;
		for (uint_fast32_t i = 0; i < max_len; i++) {
			power[i+1] = calc_mod(mul(power[i], base));
		}
	}
};
template<uint_fast32_t a, uint_fast32_t b, uint_fast64_t c, uint_fast64_t d, uint_fast64_t e>
array<typename RollingHash<a, b, c, d, e>::hash_type, a+1> RollingHash<a, b, c, d, e>::power = PowCalc<a, b, c, d, e>().power;
} 
using namespace rolling_hash;
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

