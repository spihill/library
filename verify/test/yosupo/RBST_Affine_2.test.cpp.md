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


# :heavy_check_mark: test/yosupo/RBST_Affine_2.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/yosupo/RBST_Affine_2.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-24 15:18:23+09:00


* see: <a href="https://judge.yosupo.jp/problem/point_set_range_composite">https://judge.yosupo.jp/problem/point_set_range_composite</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/datastructure/SegmentTree/RBST.cpp.html">RBST (Randomized Binary Search Tree)</a>
* :heavy_check_mark: <a href="../../../library/math/ModInt.cpp.html">ModInt</a>
* :heavy_check_mark: <a href="../../../library/monoid/affine_monoid.cpp.html">monoid/affine_monoid.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/SegmentTree/RBST.cpp"
#include "../../monoid/affine_monoid.cpp"
#include "../../math/ModInt.cpp"

using modint = ModInt<998244353>;
using monoid = affine_monoid<modint>;

int main() {
	int N, Q; cin >> N >> Q;
	RBST<long long, monoid, greater<>> R;
	for (int i = 0; i < N; i++) {
		int a, b; cin >> a >> b;
		R.set(-i, {a, b});
	}
	for (int i = 0; i < Q; i++) {
		int q; cin >> q;
		if (q == 0) {
			int p, c, d; cin >> p >> c >> d;
			R.set(-p, {c, d});
		} else {
			int l, r;
			modint x;
			cin >> l >> r >> x;
			auto t = R.get(-l, -r);
			cout << t.first * x + t.second << endl;
		}
	}
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yosupo/RBST_Affine_2.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"

#include<bits/stdc++.h>

using namespace std;

#line 1 "test/yosupo/../../datastructure/SegmentTree/RBST.cpp"
/**
 * @title RBST (Randomized Binary Search Tree)
 * @brief セグ木のようなことができる(座標圧縮不要)
 * @brief 最初は全区間に単位元があるように振る舞う
 * @brief 0-indexed 半開区間
 */
namespace rbst_n{
template<class KEY, class Monoid, class Compare = less<KEY>>
struct RBST {
	using u32 = uint_fast32_t;
	using i32 = int_fast32_t;
	using random_type = u32;
	using Monoid_T = typename Monoid::monoid_type;
	struct node {
		KEY key;
		Monoid monoid;
		Monoid sum;
		node *lch, *rch, *par;
		u32 cnt;
		node(const KEY& k, const Monoid_T& m) : key(k), monoid(m), sum(m), lch(nil), rch(nil), par(nil), cnt(1) {}
		node(const KEY& k, const Monoid_T& m, const pair<node*, node*>& p) : key(k), monoid(m), sum(m), lch(p.first), rch(p.second), par(nil), cnt(1) {}
		node() : key(), monoid(), sum(), lch(this), rch(this), par(this), cnt(0) {}
		static node* const nil;
	};
	using np = node*;
	np top;
	RBST() : top(node::nil) {}
	void set(const KEY key, const Monoid_T val) { 
		top = insert(key, val, top);
	}
	Monoid_T get(const KEY l, const KEY r) const { return get(l, r, top).val;}
	inline const u32 size() const { return top->cnt;}
	void check(bool print_node = false) const {
		if (print_node) cerr << "nil " << node::nil << " ";
		if (print_node) cerr << "par " << node::nil->par << " ";
		if (print_node) cerr << "lch " << node::nil->lch << " ";
		if (print_node) cerr << "rch " << node::nil->rch << " ";
		if (print_node) cerr << endl;
		assert(top->par == node::nil);
		check_dfs(top, print_node);
	}
private:
	inline random_type xor128() {
		static random_type x = 123456789u, y = 362436069u, z = 521288629u, w = 88675123u;
		random_type t = x ^ (x << 11);
		x = y; y = z; z = w;
		return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
	}
	inline random_type xor128(const random_type sup_value) { return xor128() % sup_value;}
	Monoid get(const KEY& l, const KEY& r, np n) const {
		if (n == node::nil) return Monoid();
		if (Compare()(n->key, l)) return get(l, r, n->rch);
		if (!Compare()(n->key, r)) return get(l, r, n->lch);
		return get_left(l, n->lch) + n->monoid + get_right(r, n->rch);
	}
	Monoid get_left(const KEY& l, np n) const {
		if (n == node::nil) return Monoid();
		if (Compare()(n->key, l)) return get_left(l, n->rch);
		return get_left(l, n->lch) + n->monoid + n->rch->sum;
	}
	Monoid get_right(const KEY& r, np n) const {
		if (n == node::nil) return Monoid();
		if (!Compare()(n->key, r)) return get_right(r, n->lch);
		return n->lch->sum + n->monoid + get_right(r, n->rch);
	}
	bool is_left_node_smaller(np l, np r) const { return xor128(l->cnt + r->cnt) < r->cnt;}
	inline np update_sum(np n, np par) {
		for (; n != par->par; n = n->par) n->sum = n->lch->sum + n->monoid + n->rch->sum;
		return par;
	}
	inline np update(np n) {
		n->cnt = n->lch->cnt + n->rch->cnt + 1;
		n->sum = n->lch->sum + n->monoid + n->rch->sum;
		return n;
	}
	inline void update_lch_sub(np n) {
		if (n->lch != node::nil) n->lch->par = n;
	}
	inline void update_rch_sub(np n) {
		if (n->rch != node::nil) n->rch->par = n;
	}
	inline np update_lch(np n) { update_lch_sub(n); return update(n);}
	inline np update_rch(np n) { update_rch_sub(n); return update(n);}
	inline np update_lr_ch(np n) { update_lch_sub(n); return update_rch(n);}
	np merge(np l, np r) {
		if (l == node::nil || r == node::nil) return l == node::nil ? r : l;
		if (is_left_node_smaller(l, r)) {
			r->lch = merge(l, r->lch);
			return update_lch(r);
		} else {
			l->rch = merge(l->rch, r);
			return update_rch(l);
		}
	}
	pair<np, np> split(np t, u32 k) {
		if (t == node::nil) return make_pair(node::nil, node::nil);
		if (k <= t->lch->cnt) {
			pair<np, np> s = split(t->lch, k);
			t->lch = s.second;
			return make_pair(s.first, update_lch(t));
		} else {
			pair<np, np> s = split(t->rch, k - t->lch->cnt - 1);
			t->rch = s.first;
			return make_pair(update_rch(t), s.second);
		}
	}
	pair<u32, np> find_insert_pos_(const KEY& key, np n) const {
		u32 pos = 0;
		while (n != node::nil) {
			if (Compare()(key, n->key)) n = n->lch;
			else if (Compare()(n->key, key)) pos += n->lch->cnt + 1, n = n->rch;
			else break;
		}
		return make_pair(pos, n);
	}
	np insert(const KEY& key, const Monoid_T& val, np n) {
		if (n == node::nil) return new node(key, val);
		if (xor128(n->cnt+1)) {
			if (Compare()(key, n->key)) {
				n->lch = insert(key, val, n->lch);
				return update_lch(n);
			} else if (Compare()(n->key, key)) {
				n->rch = insert(key, val, n->rch);
				return update_rch(n);
			} else {
				n->monoid = Monoid(val);
				return update(n);
			}
		} else {
			auto f = find_insert_pos_(key, n);
			if (f.second != node::nil) {
				f.second->monoid = Monoid(val);
				return update_sum(f.second, n);
			}
			np new_node = new node(key, val, move(split(n, f.first)));
			return update_lr_ch(new_node);
		}
	}
	void check_dfs(np n, bool print_node) const {
		if (n == node::nil) return;
		if (print_node) cerr << "np " << n << " ";
		if (print_node) cerr << "par " << n->par << " ";
		if (print_node) cerr << "key " << n->key << " ";
		if (print_node) cerr << "mon " << n->monoid.val << " ";
		if (print_node) cerr << "sum " << n->sum.val << " ";
		if (n->lch != node::nil) {
			if (print_node) cerr << "left : " << n->lch->key << " ";
			if (print_node) cerr << "lch : " << n->lch << " ";
			assert(n->lch->par == n);
		}
		if (n->rch != node::nil) {
			if (print_node) cerr << "right : " << n->rch->key << " ";
			if (print_node) cerr << "rch : " << n->rch << " ";
			assert(n->rch->par == n);
		}
		if (print_node) cerr << endl;
		check_dfs(n->lch, print_node);
		check_dfs(n->rch, print_node);
	}
};
	template<class T, class U, class V> typename RBST<T, U, V>::node* const RBST<T, U, V>::node::nil = new node();
} // rbst_n
using rbst_n::RBST;#line 1 "test/yosupo/../../monoid/affine_monoid.cpp"
template<class T>
struct affine_monoid {
	using mono = affine_monoid;
	affine_monoid() : affine_monoid(pair<T, T>(1, 0)) {}
	explicit affine_monoid(pair<T, T> x) : val(x) {}
	pair<T, T> val;
	mono operator+(const mono& rhs) const {
		return mono(pair<T, T>(rhs.val.first * val.first, rhs.val.first * val.second + rhs.val.second));
	}
	friend istream& operator>>(istream& lhs, mono& rhs) {
		lhs >> rhs.val.first >> rhs.val.second;
		return lhs;
	}
	friend ostream& operator<<(ostream& lhs, mono& rhs) {
		lhs << rhs.val.first << ' ' << rhs.val.second;
		return lhs;
	}
	using monoid_type = pair<T, T>;
};#line 1 "test/yosupo/../../math/ModInt.cpp"
/**
 * @title ModInt
 * @brief mod を取りながら計算する。リテラル型の要件を満たし、constexprに対応している。
 * @brief これでも Verify してます。 https://github.com/spihill/library/blob/master/test/mytest/ModInt.test.cpp
 */
namespace mylib {
template<int mod>
struct ModInt {
	using i64 = int_fast64_t;
	int x;
	constexpr static int get_mod() {
		return mod;
	}
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
		i64 t;
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
//using modint = ModInt<998244353>;#line 10 "test/yosupo/RBST_Affine_2.test.cpp"

using modint = ModInt<998244353>;
using monoid = affine_monoid<modint>;

int main() {
	int N, Q; cin >> N >> Q;
	RBST<long long, monoid, greater<>> R;
	for (int i = 0; i < N; i++) {
		int a, b; cin >> a >> b;
		R.set(-i, {a, b});
	}
	for (int i = 0; i < Q; i++) {
		int q; cin >> q;
		if (q == 0) {
			int p, c, d; cin >> p >> c >> d;
			R.set(-p, {c, d});
		} else {
			int l, r;
			modint x;
			cin >> l >> r >> x;
			auto t = R.get(-l, -r);
			cout << t.first * x + t.second << endl;
		}
	}
}
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

