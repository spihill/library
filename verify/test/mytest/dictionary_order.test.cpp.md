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


# :x: test/mytest/dictionary_order.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/mytest/dictionary_order.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-14 17:23:24+09:00




## Depends on

* :x: <a href="../../../library/algorithm/dictionary_order.cpp.html">algorithm/dictionary_order.cpp</a>
* :x: <a href="../../../library/datastructure/BIT.cpp.html">datastructure/BIT.cpp</a>
* :heavy_check_mark: <a href="../../../library/math/ModInt.cpp.html">math/ModInt.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <bits/stdc++.h>

using namespace std;

#include "../../math/ModInt.cpp"
using modint = ModInt<1000000007>;
#include "../../algorithm/dictionary_order.cpp"

using namespace std;
using u64 = uint_fast64_t;
using u32 = uint_fast32_t;
using i64 = int_fast64_t;
using i32 = int_fast32_t;

struct has_il_impl {
	template <class T>
	static std::true_type check(decltype(T::il)*);
	template <class T>
	static std::false_type check(...);
};

template <class T>
class has_il :
	public decltype(has_il_impl::check<T>(nullptr)) {};

struct has_data_class_impl {
	template <class T>
	static std::true_type check(typename T::data_class_tag*);
	template <class T>
	static std::false_type check(...);
};

template <class T>
class has_data_class_tag :
	public decltype(has_data_class_impl::check<T>(nullptr)) {};

template<class T, class Enable = void>
struct base_data_class;

template<class T>
struct base_data_class<T, enable_if_t<is_arithmetic<T>::value>> {
	using value_type = T;
	struct data_class_tag {};
	T min_v, max_v;
	base_data_class(T min_value, T max_value) : min_v(min_value), max_v(max_value) {assert(min_v <= max_v);}
};

template<class T>
struct random_select_class : public base_data_class<size_t> {
	using data_type = T;
	vector<T> il;
	random_select_class(initializer_list<T> il_) : base_data_class(size_t(0), il_.size()-1), il{il_} {}
};

template<class T>
struct data_class : public base_data_class<T> {
	using data_type = T;
	template<class... Args>
	data_class(Args... args) : base_data_class<T>(args...) {}
};

u32 seed;

struct random_class {
private:
	mt19937 engine;
public:
	random_class() : engine(seed++) {}
	// min_v : 生成する乱数の最小値
	// max_v : 生成する乱数の最大値
	template<class T>
	enable_if_t<is_arithmetic<T>::value, T> make_random(T min_v, T max_v) {
		return make_random_number(min_v, max_v);
	}
	// dc : data_class
	template<class T>
	enable_if_t<has_data_class_tag<T>::value && has_il<T>::value, typename T::data_type> make_random(const T& dc) {
		return dc.il[make_random_number(dc.min_v, dc.max_v)];
	}
	// dc : data_class
	template<class T>
	enable_if_t<has_data_class_tag<T>::value && !has_il<T>::value && is_arithmetic<typename T::value_type>::value, typename T::value_type> make_random(const T& dc) {
		return make_random_number(dc.min_v, dc.max_v);
	}
	// vector_size : 生成するvectorの長さ
	// dc : data_class
	// dup : 要素の重複を許容するならtrue (default : true)
	// inc : 昇順にソートするならtrue (default : false)
	// dec : 降順にソートするならtrue (default : false)
	template<class T, class D = typename T::data_type>
	enable_if_t<has_data_class_tag<T>::value, vector<D>> make_random_vector(size_t vector_size, T& dc, bool dup = true, bool inc = false, bool dec = false) {
		vector<D> v;
		assert(!(inc && dec));
		set<D> s;
		for (size_t i = 0; i < vector_size; i++) {
			D t = make_random(dc);
			if (!dup && s.count(t)) i--;
			else v.push_back(t), s.insert(t);
		}
		if (inc) sort(v.begin(), v.end());
		if (dec) sort(v.rbegin(), v.rend());
		return v;
	}
	// dc : data_class
	// data_class が持つ値域を参照し、値域に含まれるすべての要素の random な permutation を生成する。
	template<class T, class U = typename T::data_type>
	enable_if_t<has_data_class_tag<T>::value && is_integral<typename T::value_type>::value, vector<U>> make_random_permutation(const T& dc) {
		uint32_t vector_size = dc.max_v - dc.min_v + 1;
		vector<size_t> perm = make_random_permutation_sub(vector_size);
		vector<U> res(vector_size);
		for (size_t i = 0; i < vector_size; i++) {
			res[i] = get_nth_element(perm[i], dc);
		}
		return res;
	}
	// V : 頂点数
	// E : 辺の数
	// connected : 連結なグラフを生成させるか (default : true)
	// dag : DAG を生成する場合は true (default : true)
	// randomize : 頂点番号をシャッフルする場合は true (default : true)
	// 0-indexed で生成
	vector<vector<size_t>> make_random_graph(size_t V, size_t E, bool connected = true, bool dag = true, bool randomize = true) {
		assert(V > 0);
		assert(!connected || V - 1 <= E);
		u64 MAX_E = dag ? (u64(V) * (V - 1) / 2) : (u64(V) * (V-1));
		assert(E <= MAX_E);
		size_t e = size_t(min<u64>(MAX_E - E, E));
		vector<unordered_set<size_t>> vs_origin = connected ? make_random_tree_sub(V) : vector<unordered_set<size_t>>(V);
		auto vs = vs_origin;
		e -= (connected && E == e) ? V - 1 : 0;
		make_random_graph_sub(V, e, vs, dag);
		vector<vector<size_t>> res(V);
		if (E <= MAX_E - E) {
			for (size_t i = 0; i < V; i++) {
				for (auto x : vs[i]) {
					res[i].push_back(x);
				}
			}
		} else {
			for (size_t i = 0; i < V; i++) {
				for (size_t j = dag ? (i+1) : 0; j < V; j++) {
					if (i == j) continue;
					if (!vs[i].count(j)) res[i].push_back(j);
				}
			}
			for (size_t i = 0; i < V; i++) {
				for (auto x : vs_origin[i]) {
					res[i].push_back(x);
				}
			}
		}
		if (randomize) return make_graph_randomize(res, dag);
		return res;
	}
	// g が from から to へ到達可能であることを保証する。
	// g の形は保持したまま、頂点番号を変える。
	void ensure_reach(vector<vector<size_t>>& g, size_t from, size_t to) {
		assert(0 <= from && from < g.size());
		assert(0 <= to && to < g.size());
		vector<size_t> random_perm = make_random_permutation_sub(g.size());
		for (size_t i = 0; i < g.size(); i++) {
			size_t g_from = random_perm[i];
			if (g[g_from].size() == 0) continue;
			vector<size_t> perm(g.size()); iota(perm.begin(), perm.end(), 0);
			size_t g_to = random_select_from_vector(can_reach_vertexes(g, g_from));
			if (g_from == from && g_to == to) {
				return;
			}else if (g_from == to && g_to == from) {
				swap(perm[g_from], perm[from]);
			} else if (g_to == from) {
				swap(perm[g_from], perm[from]);
				swap(perm[g_to], perm[to]);
			} else {
				swap(perm[g_to], perm[to]);
				swap(perm[g_from], perm[from]);
			}
			vector<vector<size_t>> g2(g.size());
			for (size_t i = 0; i < g.size(); i++) {
				for (auto x : g[i]) {
					g2[perm[i]].push_back(perm[x]);
				}
			}
			g = g2;
			return;
		}
		cerr << "Cannot ensure_reach (Maybe g doesn\'t have any edges)" << endl;
		abort();
	}
	template<class T>
	enable_if_t<is_integral<T>::value, vector<T>> make_random_divide(u32 len, T sum, T min_v = 0) {
		assert(len);
		if (min_v) {
			assert(static_cast<i64>(min_v) * static_cast<i64>(len) <= static_cast<i64>(sum));
			auto res = make_random_divide(len, static_cast<T>(sum - static_cast<i64>(min_v) * len));
			for (auto& x : res) x += min_v;
			return res;
		}
		assert(0 <= sum);
		u64 N = sum + len - 1;
		vector<u64> pos{0, N+1};
		unordered_set<u64> s;
		for (size_t i = 1; i < len; i++) {
			u64 t = make_random<u64>(1, N);
			if (s.count(t)) i--;
			else pos.push_back(t), s.insert(t);
		}
		sort(pos.begin(), pos.end());
		vector<T> res(len);
		for (size_t i = 0; i < len; i++) {
			res[i] = pos[i+1] - pos[i] - 1;
		}
		return res;
	}
private:
	vector<size_t> can_reach_vertexes(const vector<vector<size_t>>& g, int from) {
		vector<char> vis(g.size());
		vector<size_t> res;
		auto dfs = [&](auto& f, int n) -> void {
			if (vis[n]) return;
			if (n != from) res.push_back(n);
			vis[n] = true;
			for (auto x : g[n]) f(f, x);
		};
		dfs(dfs, from);
		return res;
	}
	template<class T>
	T random_select_from_vector(const vector<T>& v) {
		assert(v.size());
		return v[make_random<size_t>(0, v.size()-1)];
	}
	vector<unordered_set<size_t>> make_random_tree_sub(size_t V) {
		vector<unordered_set<size_t>> g(V);
		for (size_t i = 1; i < V; i++) {
			g[make_random<size_t>(0, i-1)].insert(i);
		}
		return g;
	}
	void make_random_graph_sub(size_t V, size_t E, vector<unordered_set<size_t>>& used, bool dag) {
		size_t from, to;
		for (size_t i = 0; i < E; i++) {
			make_random_simple_edge_(V, from, to);
			if (dag && from > to) swap(from, to);
			if (used[from].count(to)) i--;
			else used[from].insert(to);
		}
	}
	vector<vector<size_t>> make_graph_randomize(const vector<vector<size_t>>& g, bool dag) {
		vector<vector<size_t>> res(g.size());
		vector<size_t> perm = make_random_permutation_sub(g.size());
		vector<set<size_t>> ls(g.size());
		if (!dag) {
			for (size_t i = 0; i < g.size(); i++) {
				for (auto x : g[i]) ls[i].insert(x);
			}
		}
		for (size_t i = 0; i < g.size(); i++) {
			for (auto x : g[i]) {
				if (dag || ls[x].count(i) || make_random(0, 1)) res[perm[i]].push_back(perm[x]);
				else res[perm[x]].push_back(perm[i]);
			}
		}
		return res;
	}
	template<class T>
	T make_random_number(T min_v, T max_v) { return uniform_int_distribution<T>(min_v, max_v)(engine);}
	void make_random_simple_edge_(size_t V, size_t& from, size_t& to) {
		from = make_random<size_t>(0, V-1);
		while ((to = make_random<size_t>(0, V-1)) == from);
	}
	vector<size_t> make_random_permutation_sub(size_t len) {
		assert(len);
		vector<size_t> res(len); iota(res.begin(), res.end(), 0);
		for (size_t i = 0; i < len-1; i++) {
			swap(res[i], res[make_random<size_t>(i, len-1)]);
		}
		return res;
	}
	template<class T, class U = typename T::data_type>
	enable_if_t<has_data_class_tag<T>::value && has_il<T>::value, U> get_nth_element(size_t n, const T& dc) {
		return dc.il[n];
	}
	template<class T, class U = typename T::data_type>
	enable_if_t<has_data_class_tag<T>::value && !has_il<T>::value && is_arithmetic<typename T::value_type>::value, U> get_nth_element(size_t n, const T& dc) {
		return dc.min_v + static_cast<U>(n);
	}
};
template<> double random_class::make_random_number<double>(double min_v, double max_v) { return uniform_real_distribution<double>(min_v, max_v)(engine);}
template<> long double random_class::make_random_number<long double>(long double min_v, long double max_v) { return uniform_real_distribution<long double>(min_v, max_v)(engine);}
template<> float random_class::make_random_number<float>(float min_v, float max_v) { return uniform_real_distribution<float>(min_v, max_v)(engine);}


template<class T>
random_select_class<T> make_data(initializer_list<T> il) {
	return random_select_class<T>(il);
}

template<class T>
enable_if_t<is_arithmetic<T>::value, data_class<T>> make_data(T min_v, T max_v) {
	return data_class<T>(min_v, max_v);
}

/* data_class と random_select_class について
  乱数生成する際に用いるクラス。
    auto X = make_data(3, 5)
  などのように生成する。
    auto X = make_data(5, 8)
    auto X = make_data({5, 6, 7, 8})
  はほぼ等価。(前者では data_class が生成され、後者では random_select_class が生成される。)
*/

template<class T>
void test_sub(T v) {
	int i = 0;
	do {
		assert(i++ == dictionary_order(v).x);
	} while (next_permutation(v.begin(), v.end()));
}

void test(int N) {
	random_class rd;
	auto dc = make_data(INT_MIN, INT_MAX);
	auto dc2 = make_data(1, N);
	auto dc3 = make_data(1, 1);
	vector<int> v = rd.make_random_vector(N, dc, true, true);
	vector<int> v2 = rd.make_random_vector(N, dc2, true, true);
	vector<int> v3 = rd.make_random_vector(N, dc3, true, true);
	test_sub(v);
	test_sub(v2);
	test_sub(v3);
}

int main() {
	random_class rd;
	for (size_t i = 0; i < 100; i++) {
		test(rd.make_random(1, 8));
		test(8);
	}
	test_sub(string("abcdefgh"));
	test_sub(string("aabcccde"));
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/mytest/dictionary_order.test.cpp"
#include <bits/stdc++.h>

using namespace std;

#line 1 "test/mytest/../../math/ModInt.cpp"
namespace mylib {
template<int mod>
struct ModInt {
	using i64 = int_fast64_t;
	int x;
	constexpr static int M = mod;
	constexpr ModInt(i64 x_) : x(mod_(x_)) {}
	constexpr ModInt() : ModInt(0) {}
	~ModInt() = default;
	inline constexpr ModInt& operator+=(const ModInt rhs) {
		i64 t = static_cast<i64>(x) + rhs.x;
		if (t >= mod) x = t - mod;
		else x = t;
		return (*this);
	}
	inline constexpr ModInt& operator-=(const ModInt rhs) {
		i64 t = static_cast<i64>(x) + mod - rhs.x;
		if (t >= mod) x = t - mod;
		else x = t;
		return *this;
	}
	inline constexpr ModInt& operator*=(const ModInt rhs) {
		x = static_cast<i64>(x) * rhs.x % mod;
		return *this;
	}
	inline constexpr ModInt& operator/=(ModInt rhs) {
		return *this *= rhs.inv();
	}
	inline constexpr ModInt power(i64 p) const {
		ModInt res = 1;
		ModInt a = x;
		for (; p; res = p & 1 ? res * a : res, a *= a, p >>= 1);
		return res;
	}
	inline constexpr ModInt inv() const {
		int z = 0, w = 0;
		extgcd(mod, x, z, w);
		return ModInt(w);
	}
	inline constexpr ModInt& operator=(const ModInt& rhs) {
		this->x = rhs.x;
		return *this;
	}
	inline constexpr int operator==(const ModInt& rhs) const {
		return this->x == rhs.x;
	}
	inline constexpr int operator!=(const ModInt& rhs) const {
		return !(*this == rhs);
	}
	inline constexpr ModInt operator++(signed unused) {
		ModInt res(*this);
		++(*this);
		return res;
	}
	inline constexpr ModInt& operator++() {
		(*this) += 1;
		return (*this);
	}
	inline constexpr ModInt operator--(signed unused) {
		ModInt res(*this);
		--(*this);
		return res;
	}
	inline constexpr ModInt& operator--() {
		(*this) -= 1;
		return (*this);
	}
	inline constexpr ModInt operator+() const {
		return (*this);
	}
	inline constexpr ModInt operator-() const {
		return (*this).x ? ModInt(mod - (*this).x) : ModInt(0);
	}
	friend constexpr ModInt operator+(const ModInt& lhs, const ModInt& rhs) {return ModInt(lhs) += rhs;}
	friend constexpr ModInt operator-(const ModInt& lhs, const ModInt& rhs) {return ModInt(lhs) -= rhs;}
	friend constexpr ModInt operator*(const ModInt& lhs, const ModInt& rhs) {return ModInt(lhs) *= rhs;}
	friend constexpr ModInt operator/(const ModInt& lhs, const ModInt& rhs) {return ModInt(lhs) /= rhs;}
	explicit constexpr operator int() const {return x;}
	friend ostream& operator<<(ostream& lhs, const ModInt& rhs) {
		lhs << rhs.x;
		return lhs;
	}
	friend istream& operator>>(istream& lhs, ModInt& rhs) {
		long long t;
		lhs >> t;
		rhs = ModInt(t);
		return lhs;
	}
private:
	constexpr int extgcd(int a, int b, int& x, int& y) const {
		int d = a;
		if (b == 0) {
			x = 1;
			y = 0;
		} else {
			d = extgcd(b, a%b, y, x);
			y -= a / b * x;
		}
		return d;
	}
	constexpr int mod_(i64 x) {
		x %= mod; if (x < 0) x += mod;
		return static_cast<int>(x);
	}
};
}; // mylib
using namespace mylib;
//using modint = ModInt<1000000007>;
//using modint = ModInt<998244353>;#line 6 "test/mytest/dictionary_order.test.cpp"
using modint = ModInt<1000000007>;
#line 1 "test/mytest/../../algorithm/../datastructure/BIT.cpp"
template<class T>
struct BIT {
	int n;
	vector<T> bit;
	BIT(int n_) : n(n_), bit(n) {}
	BIT(const vector<T>& v) : BIT(v.size()) {
		for (int i = 0; i < n; i++) bit[i] = v[i];
		for (int i = 0; i < n-1; i++) if ((i | (i + 1)) < n) bit[i | (i + 1)] += bit[i];
	}
	// bit[i] += v
	void add(int i, T v) {
		for (; i < n; i |= i + 1) bit[i] += v;
	}
	// sum of [0, i)
	T get(int i) {
		T res = 0;
		for (i--; i >= 0; i = (i & (i + 1)) - 1) res += bit[i];
		return res;
	}
	// sum of [i, j)
	T get(int i, int j) {
		return get(j) - get(i);
	}
};#line 2 "test/mytest/../../algorithm/dictionary_order.cpp"
// 辞書順で何番目かを返す。(0-indexed)
// O(Nlog(N) + log(mod))
template<class T, class mint = modint>
mint dictionary_order(const vector<T>& vec) {
	size_t n = vec.size();
	if (n <= 1) return mint(0);
	vector<size_t> ord(n);
	vector<size_t> cnt(n);
	vector<size_t> cnt_sum(n+1);
	{
		map<T, size_t> ord_m;
		for (auto x : vec) ord_m[x] = 1;
		size_t index = 0;
		for (auto& p : ord_m) p.second = index++;
		for (size_t i = 0; i < n; i++) ord[i] = ord_m[vec[i]];
		for (size_t i = 0; i < n; i++) cnt[ord[i]]++;
		for (size_t i = 0; i < n; i++) cnt_sum[i+1] = cnt_sum[i] + cnt[i];
	}
	vector<mint> fact(n+1, 1);
	vector<mint> facti(n+1, 1);
	for (size_t i = 1; i <= n; i++) fact[i] = fact[i-1] * i;
	facti.back() = 1 / fact.back();
	for (size_t i = n-1; i > 0; i--) facti[i] = facti[i+1] * (i+1);
	BIT<int> bit(n+1);
	mint res = 0;
	mint inv = 1;
	for (size_t i = 0; i < n; i++) {
		inv *= facti[cnt[i]];
	}
	for (size_t i = 0; i < n-1; i++) {
		res += fact[n-i-1] * (mint(cnt_sum[ord[i]]) - bit.get(ord[i])) * inv;
		inv *= cnt[ord[i]]--;
		bit.add(ord[i], 1);
	}
	return res;
}
template<class mint = modint>
mint dictionary_order(const string& s) {
	vector<char> vs(s.begin(), s.end());
	return dictionary_order(vs);
}#line 8 "test/mytest/dictionary_order.test.cpp"

using namespace std;
using u64 = uint_fast64_t;
using u32 = uint_fast32_t;
using i64 = int_fast64_t;
using i32 = int_fast32_t;

struct has_il_impl {
	template <class T>
	static std::true_type check(decltype(T::il)*);
	template <class T>
	static std::false_type check(...);
};

template <class T>
class has_il :
	public decltype(has_il_impl::check<T>(nullptr)) {};

struct has_data_class_impl {
	template <class T>
	static std::true_type check(typename T::data_class_tag*);
	template <class T>
	static std::false_type check(...);
};

template <class T>
class has_data_class_tag :
	public decltype(has_data_class_impl::check<T>(nullptr)) {};

template<class T, class Enable = void>
struct base_data_class;

template<class T>
struct base_data_class<T, enable_if_t<is_arithmetic<T>::value>> {
	using value_type = T;
	struct data_class_tag {};
	T min_v, max_v;
	base_data_class(T min_value, T max_value) : min_v(min_value), max_v(max_value) {assert(min_v <= max_v);}
};

template<class T>
struct random_select_class : public base_data_class<size_t> {
	using data_type = T;
	vector<T> il;
	random_select_class(initializer_list<T> il_) : base_data_class(size_t(0), il_.size()-1), il{il_} {}
};

template<class T>
struct data_class : public base_data_class<T> {
	using data_type = T;
	template<class... Args>
	data_class(Args... args) : base_data_class<T>(args...) {}
};

u32 seed;

struct random_class {
private:
	mt19937 engine;
public:
	random_class() : engine(seed++) {}
	// min_v : 生成する乱数の最小値
	// max_v : 生成する乱数の最大値
	template<class T>
	enable_if_t<is_arithmetic<T>::value, T> make_random(T min_v, T max_v) {
		return make_random_number(min_v, max_v);
	}
	// dc : data_class
	template<class T>
	enable_if_t<has_data_class_tag<T>::value && has_il<T>::value, typename T::data_type> make_random(const T& dc) {
		return dc.il[make_random_number(dc.min_v, dc.max_v)];
	}
	// dc : data_class
	template<class T>
	enable_if_t<has_data_class_tag<T>::value && !has_il<T>::value && is_arithmetic<typename T::value_type>::value, typename T::value_type> make_random(const T& dc) {
		return make_random_number(dc.min_v, dc.max_v);
	}
	// vector_size : 生成するvectorの長さ
	// dc : data_class
	// dup : 要素の重複を許容するならtrue (default : true)
	// inc : 昇順にソートするならtrue (default : false)
	// dec : 降順にソートするならtrue (default : false)
	template<class T, class D = typename T::data_type>
	enable_if_t<has_data_class_tag<T>::value, vector<D>> make_random_vector(size_t vector_size, T& dc, bool dup = true, bool inc = false, bool dec = false) {
		vector<D> v;
		assert(!(inc && dec));
		set<D> s;
		for (size_t i = 0; i < vector_size; i++) {
			D t = make_random(dc);
			if (!dup && s.count(t)) i--;
			else v.push_back(t), s.insert(t);
		}
		if (inc) sort(v.begin(), v.end());
		if (dec) sort(v.rbegin(), v.rend());
		return v;
	}
	// dc : data_class
	// data_class が持つ値域を参照し、値域に含まれるすべての要素の random な permutation を生成する。
	template<class T, class U = typename T::data_type>
	enable_if_t<has_data_class_tag<T>::value && is_integral<typename T::value_type>::value, vector<U>> make_random_permutation(const T& dc) {
		uint32_t vector_size = dc.max_v - dc.min_v + 1;
		vector<size_t> perm = make_random_permutation_sub(vector_size);
		vector<U> res(vector_size);
		for (size_t i = 0; i < vector_size; i++) {
			res[i] = get_nth_element(perm[i], dc);
		}
		return res;
	}
	// V : 頂点数
	// E : 辺の数
	// connected : 連結なグラフを生成させるか (default : true)
	// dag : DAG を生成する場合は true (default : true)
	// randomize : 頂点番号をシャッフルする場合は true (default : true)
	// 0-indexed で生成
	vector<vector<size_t>> make_random_graph(size_t V, size_t E, bool connected = true, bool dag = true, bool randomize = true) {
		assert(V > 0);
		assert(!connected || V - 1 <= E);
		u64 MAX_E = dag ? (u64(V) * (V - 1) / 2) : (u64(V) * (V-1));
		assert(E <= MAX_E);
		size_t e = size_t(min<u64>(MAX_E - E, E));
		vector<unordered_set<size_t>> vs_origin = connected ? make_random_tree_sub(V) : vector<unordered_set<size_t>>(V);
		auto vs = vs_origin;
		e -= (connected && E == e) ? V - 1 : 0;
		make_random_graph_sub(V, e, vs, dag);
		vector<vector<size_t>> res(V);
		if (E <= MAX_E - E) {
			for (size_t i = 0; i < V; i++) {
				for (auto x : vs[i]) {
					res[i].push_back(x);
				}
			}
		} else {
			for (size_t i = 0; i < V; i++) {
				for (size_t j = dag ? (i+1) : 0; j < V; j++) {
					if (i == j) continue;
					if (!vs[i].count(j)) res[i].push_back(j);
				}
			}
			for (size_t i = 0; i < V; i++) {
				for (auto x : vs_origin[i]) {
					res[i].push_back(x);
				}
			}
		}
		if (randomize) return make_graph_randomize(res, dag);
		return res;
	}
	// g が from から to へ到達可能であることを保証する。
	// g の形は保持したまま、頂点番号を変える。
	void ensure_reach(vector<vector<size_t>>& g, size_t from, size_t to) {
		assert(0 <= from && from < g.size());
		assert(0 <= to && to < g.size());
		vector<size_t> random_perm = make_random_permutation_sub(g.size());
		for (size_t i = 0; i < g.size(); i++) {
			size_t g_from = random_perm[i];
			if (g[g_from].size() == 0) continue;
			vector<size_t> perm(g.size()); iota(perm.begin(), perm.end(), 0);
			size_t g_to = random_select_from_vector(can_reach_vertexes(g, g_from));
			if (g_from == from && g_to == to) {
				return;
			}else if (g_from == to && g_to == from) {
				swap(perm[g_from], perm[from]);
			} else if (g_to == from) {
				swap(perm[g_from], perm[from]);
				swap(perm[g_to], perm[to]);
			} else {
				swap(perm[g_to], perm[to]);
				swap(perm[g_from], perm[from]);
			}
			vector<vector<size_t>> g2(g.size());
			for (size_t i = 0; i < g.size(); i++) {
				for (auto x : g[i]) {
					g2[perm[i]].push_back(perm[x]);
				}
			}
			g = g2;
			return;
		}
		cerr << "Cannot ensure_reach (Maybe g doesn\'t have any edges)" << endl;
		abort();
	}
	template<class T>
	enable_if_t<is_integral<T>::value, vector<T>> make_random_divide(u32 len, T sum, T min_v = 0) {
		assert(len);
		if (min_v) {
			assert(static_cast<i64>(min_v) * static_cast<i64>(len) <= static_cast<i64>(sum));
			auto res = make_random_divide(len, static_cast<T>(sum - static_cast<i64>(min_v) * len));
			for (auto& x : res) x += min_v;
			return res;
		}
		assert(0 <= sum);
		u64 N = sum + len - 1;
		vector<u64> pos{0, N+1};
		unordered_set<u64> s;
		for (size_t i = 1; i < len; i++) {
			u64 t = make_random<u64>(1, N);
			if (s.count(t)) i--;
			else pos.push_back(t), s.insert(t);
		}
		sort(pos.begin(), pos.end());
		vector<T> res(len);
		for (size_t i = 0; i < len; i++) {
			res[i] = pos[i+1] - pos[i] - 1;
		}
		return res;
	}
private:
	vector<size_t> can_reach_vertexes(const vector<vector<size_t>>& g, int from) {
		vector<char> vis(g.size());
		vector<size_t> res;
		auto dfs = [&](auto& f, int n) -> void {
			if (vis[n]) return;
			if (n != from) res.push_back(n);
			vis[n] = true;
			for (auto x : g[n]) f(f, x);
		};
		dfs(dfs, from);
		return res;
	}
	template<class T>
	T random_select_from_vector(const vector<T>& v) {
		assert(v.size());
		return v[make_random<size_t>(0, v.size()-1)];
	}
	vector<unordered_set<size_t>> make_random_tree_sub(size_t V) {
		vector<unordered_set<size_t>> g(V);
		for (size_t i = 1; i < V; i++) {
			g[make_random<size_t>(0, i-1)].insert(i);
		}
		return g;
	}
	void make_random_graph_sub(size_t V, size_t E, vector<unordered_set<size_t>>& used, bool dag) {
		size_t from, to;
		for (size_t i = 0; i < E; i++) {
			make_random_simple_edge_(V, from, to);
			if (dag && from > to) swap(from, to);
			if (used[from].count(to)) i--;
			else used[from].insert(to);
		}
	}
	vector<vector<size_t>> make_graph_randomize(const vector<vector<size_t>>& g, bool dag) {
		vector<vector<size_t>> res(g.size());
		vector<size_t> perm = make_random_permutation_sub(g.size());
		vector<set<size_t>> ls(g.size());
		if (!dag) {
			for (size_t i = 0; i < g.size(); i++) {
				for (auto x : g[i]) ls[i].insert(x);
			}
		}
		for (size_t i = 0; i < g.size(); i++) {
			for (auto x : g[i]) {
				if (dag || ls[x].count(i) || make_random(0, 1)) res[perm[i]].push_back(perm[x]);
				else res[perm[x]].push_back(perm[i]);
			}
		}
		return res;
	}
	template<class T>
	T make_random_number(T min_v, T max_v) { return uniform_int_distribution<T>(min_v, max_v)(engine);}
	void make_random_simple_edge_(size_t V, size_t& from, size_t& to) {
		from = make_random<size_t>(0, V-1);
		while ((to = make_random<size_t>(0, V-1)) == from);
	}
	vector<size_t> make_random_permutation_sub(size_t len) {
		assert(len);
		vector<size_t> res(len); iota(res.begin(), res.end(), 0);
		for (size_t i = 0; i < len-1; i++) {
			swap(res[i], res[make_random<size_t>(i, len-1)]);
		}
		return res;
	}
	template<class T, class U = typename T::data_type>
	enable_if_t<has_data_class_tag<T>::value && has_il<T>::value, U> get_nth_element(size_t n, const T& dc) {
		return dc.il[n];
	}
	template<class T, class U = typename T::data_type>
	enable_if_t<has_data_class_tag<T>::value && !has_il<T>::value && is_arithmetic<typename T::value_type>::value, U> get_nth_element(size_t n, const T& dc) {
		return dc.min_v + static_cast<U>(n);
	}
};
template<> double random_class::make_random_number<double>(double min_v, double max_v) { return uniform_real_distribution<double>(min_v, max_v)(engine);}
template<> long double random_class::make_random_number<long double>(long double min_v, long double max_v) { return uniform_real_distribution<long double>(min_v, max_v)(engine);}
template<> float random_class::make_random_number<float>(float min_v, float max_v) { return uniform_real_distribution<float>(min_v, max_v)(engine);}


template<class T>
random_select_class<T> make_data(initializer_list<T> il) {
	return random_select_class<T>(il);
}

template<class T>
enable_if_t<is_arithmetic<T>::value, data_class<T>> make_data(T min_v, T max_v) {
	return data_class<T>(min_v, max_v);
}

/* data_class と random_select_class について
  乱数生成する際に用いるクラス。
    auto X = make_data(3, 5)
  などのように生成する。
    auto X = make_data(5, 8)
    auto X = make_data({5, 6, 7, 8})
  はほぼ等価。(前者では data_class が生成され、後者では random_select_class が生成される。)
*/

template<class T>
void test_sub(T v) {
	int i = 0;
	do {
		assert(i++ == dictionary_order(v).x);
	} while (next_permutation(v.begin(), v.end()));
}

void test(int N) {
	random_class rd;
	auto dc = make_data(INT_MIN, INT_MAX);
	auto dc2 = make_data(1, N);
	auto dc3 = make_data(1, 1);
	vector<int> v = rd.make_random_vector(N, dc, true, true);
	vector<int> v2 = rd.make_random_vector(N, dc2, true, true);
	vector<int> v3 = rd.make_random_vector(N, dc3, true, true);
	test_sub(v);
	test_sub(v2);
	test_sub(v3);
}

int main() {
	random_class rd;
	for (size_t i = 0; i < 100; i++) {
		test(rd.make_random(1, 8));
		test(8);
	}
	test_sub(string("abcdefgh"));
	test_sub(string("aabcccde"));
}
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

