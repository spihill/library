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


# :heavy_check_mark: test/mytest/gcd.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/mytest/gcd.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-27 00:26:08+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/1/ITP1_1_A">https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/1/ITP1_1_A</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/math/Factorize.cpp.html">素因数分解</a>
* :heavy_check_mark: <a href="../../../library/math/ctz.cpp.html">__builtin_ctz の代用関数</a>
* :heavy_check_mark: <a href="../../../library/math/gcd.cpp.html">最大公約数</a>
* :heavy_check_mark: <a href="../../../library/tools/RandomClass.cpp.html">tools/RandomClass.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/1/ITP1_1_A"
#include<bits/stdc++.h>

using namespace std;

#include "../../tools/RandomClass.cpp"
#include "../../math/gcd.cpp"
#include "../../math/Factorize.cpp"

template<class T>
bool check(T a, T b) {
	T g = gcd(a, b);
	map<T, int> A, B;
	Factorize(a, A);
	Factorize(b, B);
	map<T, int> G = gcd(A, B);
	T g2 = 1;
	for (auto x : G) {
		while (x.second--) {
			g2 *= x.first;
		}
	}
	return g == g2;
}

int main() {
	random_class rd;
	cerr << "start gcd test" << endl;

	cerr << "small test" << endl;
	for (int i = 1; i < 1000; i++) {
		for (int j = 1; j < 1000; j++) {
			assert(check(i, j));
		}
	}

	cerr << "large test" << endl;
	for (int i = 1; i < 1000; i++) {
		long long a = rd.make_random<long long>(1, 100000000000000);
		long long b = rd.make_random<long long>(1, 100000000000000);
		assert(check(a, b));
	}
	cout << "Hello World" << endl;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/mytest/gcd.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/1/ITP1_1_A"
#include<bits/stdc++.h>

using namespace std;

#line 1 "test/mytest/../../tools/RandomClass.cpp"
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

/**
 * data_class と random_select_class について
 * 乱数生成する際に用いるクラス。
 *   auto X = make_data(3, 5)
 * などのように生成する。
 *   auto X = make_data(5, 8)
 *   auto X = make_data({5, 6, 7, 8})
 * はほぼ等価。(前者では data_class が生成され、後者では random_select_class が生成される。)
*/
#line 1 "test/mytest/../../math/ctz.cpp"
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
 * @title __builtin_ctz の代用関数
 * @brief __builtin_ctz の代用関数で、下位何ビット0が連続しているかを返す ($O(\log \log N)$)
 */
template<class T>
constexpr enable_if_t<is_integral<T>::value, int> ctz(T x) {
	static_assert(numeric_limits<make_unsigned_t<T>>::digits < 65, "");
	constexpr auto lb = lower_bit();
	int ok = 0, ng = numeric_limits<make_unsigned_t<T>>::digits + 1;
	while (ng - ok != 1) {
		int mid = (ok + ng) >> 1;
		(lb.val[mid] & x ? ng : ok) = mid;
	}
	return ok;
}
#line 3 "test/mytest/../../math/gcd.cpp"
/**
 * @title 最大公約数
 */

// @brief Binary GCD
template<class T>
constexpr enable_if_t<is_integral<T>::value, T> gcd(T a, T b) {
	if (a < 0) a = -a;
	if (b < 0) b = -b;
	if (a == 0) return b;
	if (b == 0) return a;
	const int k = ctz(a | b);
	a >>= k;
	b >>= k;
	while (a != b) {
		if (a > b) a ^= b ^= a ^= b;
		b -= a;
		b >>= ctz(b);
	}
	return a << k;
}

// @brief map<素数, 冪> の形の整数の gcd
template<class T>
enable_if_t<is_integral<T>::value, map<T, int>> gcd(const map<T, int>& a, const map<T, int>& b) {
	map<T, int> res;
	for (const auto& x : a) if (b.count(x.first)) res[x.first] = min(x.second, b.at(x.first));
	for (const auto& x : b) if (!a.count(x.first)) res.erase(x.first);
	return res;
}
#line 1 "test/mytest/../../math/Factorize.cpp"
// @title 素因数分解
template<class T>
void Factorize(T n, map<T, int>& res) {
	for (T i = 2; i * i <= n; i++) {
		while (n % i == 0) {
			res[i]++;
			n /= i;
		}
	}
	if (n != 1) res[n]++;
}
template<class T>
void Factorize(T n, vector<T>& res) {
	for (T i = 2; i * i <= n; i++) {
		while (n % i == 0) {
			res.push_back(i);
			n /= i;
		}
	}
	if (n != 1) res.push_back(n);
}
#line 9 "test/mytest/gcd.test.cpp"

template<class T>
bool check(T a, T b) {
	T g = gcd(a, b);
	map<T, int> A, B;
	Factorize(a, A);
	Factorize(b, B);
	map<T, int> G = gcd(A, B);
	T g2 = 1;
	for (auto x : G) {
		while (x.second--) {
			g2 *= x.first;
		}
	}
	return g == g2;
}

int main() {
	random_class rd;
	cerr << "start gcd test" << endl;

	cerr << "small test" << endl;
	for (int i = 1; i < 1000; i++) {
		for (int j = 1; j < 1000; j++) {
			assert(check(i, j));
		}
	}

	cerr << "large test" << endl;
	for (int i = 1; i < 1000; i++) {
		long long a = rd.make_random<long long>(1, 100000000000000);
		long long b = rd.make_random<long long>(1, 100000000000000);
		assert(check(a, b));
	}
	cout << "Hello World" << endl;
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

