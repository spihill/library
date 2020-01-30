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


# :heavy_check_mark: test/mytest/RBSTSet.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/mytest/RBSTSet.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-20 02:36:38+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/1/ITP1_1_A">https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/1/ITP1_1_A</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/datastructure/BinarySearchTree/develop/RBSTset.cpp.html">datastructure/BinarySearchTree/develop/RBSTset.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/1/ITP1_1_A"
#include <bits/stdc++.h>

using namespace std;

#include "../../datastructure/BinarySearchTree/develop/RBSTset.cpp"

struct xorshift {
	using result_type = uint_fast32_t;
	result_type x=123456789u,y=362436069u,z=521288629u,w = 88675123u;
	static constexpr result_type min() {return numeric_limits<result_type>::min();}
	static constexpr result_type max() {return numeric_limits<result_type>::max();}
	xorshift() {}
	result_type operator()() {
		result_type t;
		t = x ^ (x << 11);
		x = y; y = z; z = w;
		return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
	}
};

using u32 = uint_fast32_t;
using i32 = int_fast32_t;
using i64 = int_fast64_t;
using type = u32;

template<class Compare> void check_small_size_queries(const u32 N, const u32 Q, Compare C, const i64 sup_value = -1);
template<class Compare> void check_compare_with_multiset(const RBSTSet<type, Compare>& T, const multiset<type, Compare>& S);
vector<type> make_random_vector(const u32 N, const i64 sup_value);
type make_random(const i64 sup_value);

int main() {
	check_small_size_queries(300, 100, less<type>(), 20);
	check_small_size_queries(300, 100, less<type>());
	check_small_size_queries(300, 100, greater<type>(), 20);
	check_small_size_queries(300, 100, greater<type>());
	cout << "Hello World" << endl;
}

template<class Compare> void check_small_size_queries(const u32 N, const u32 Q, Compare C, const i64 sup_value) {
	RBSTSet<type, Compare> T;
	for (u32 cnt = 0; cnt < Q; cnt++) {
		vector<type> r = make_random_vector(N, sup_value);
		std::multiset<type, Compare> S;
		for (u32 i = 0; i < N; i++) {
			T.insert(r[i]);
			S.insert(r[i]);
			T.check();
			check_compare_with_multiset(T, S);
		}
		shuffle(r.begin(), r.end(), xorshift());
		for (u32 i = 0; i < N; i++) {
			T.erase(r[i]);
			S.erase(S.lower_bound(r[i]));
			T.check();
			check_compare_with_multiset(T, S);
		}
		assert(T.size() == 0);
	}
}

template<class Compare> void check_compare_with_multiset_pp1(const RBSTSet<type, Compare>& T, const multiset<type, Compare>& S);
template<class Compare> void check_compare_with_multiset_pp2(const RBSTSet<type, Compare>& T, const multiset<type, Compare>& S);
template<class Compare> void check_compare_with_multiset_mm1(const RBSTSet<type, Compare>& T, const multiset<type, Compare>& S);
template<class Compare> void check_compare_with_multiset_mm2(const RBSTSet<type, Compare>& T, const multiset<type, Compare>& S);

template<class Compare> void check_compare_with_multiset(const RBSTSet<type, Compare>& T, const multiset<type, Compare>& S) {
	assert(S.size() == T.size());
	if (T.size() == 0) {
		assert(T.begin() == T.end());
		return;
	}
	check_compare_with_multiset_pp1(T, S);
	check_compare_with_multiset_pp2(T, S);
	check_compare_with_multiset_mm1(T, S);
	check_compare_with_multiset_mm2(T, S);
}

template<class Compare> void check_compare_with_multiset_pp1(const RBSTSet<type, Compare>& T, const multiset<type, Compare>& S) {
	auto Ti = T.begin();
	auto Ti2 = T.begin(); Ti2++;
	auto Si = S.begin();
	assert(*Ti == *Si);
	for (; Ti2 != T.end(); ++Ti2) assert(*(++Ti) == *(++Si));
	assert(T.end() == ++Ti);
	assert(S.end() == ++Si);
}
template<class Compare> void check_compare_with_multiset_pp2(const RBSTSet<type, Compare>& T, const multiset<type, Compare>& S) {
	auto Ti = T.begin();
	auto Si = S.begin();
	for (; Ti != T.end();) assert(*(Ti++) == *(Si++));
	assert(T.end() == Ti);
	assert(S.end() == Si);
}
template<class Compare> void check_compare_with_multiset_mm1(const RBSTSet<type, Compare>& T, const multiset<type, Compare>& S) {
	auto Ti = T.end();
	auto Si = S.end();
	for (; Ti != T.begin();) assert(*(--Ti) == *(--Si));
	assert(S.begin() == Si);
	assert(T.begin() == Ti);
}
template<class Compare> void check_compare_with_multiset_mm2(const RBSTSet<type, Compare>& T, const multiset<type, Compare>& S) {
	auto Ti = T.end(); Ti--;
	auto Si = S.end(); Si--;
	for (; Ti != T.begin();) assert(*(Ti--) == *(Si--));
	assert(S.begin() == Si);
	assert(T.begin() == Ti);
	assert(*Ti == *Si);
}

type make_random(const i64 sup_value) {
	static xorshift xor128;
	if (sup_value <= 0) return uniform_int_distribution<type>(numeric_limits<type>::min(), numeric_limits<type>::max())(xor128);
	else return uniform_int_distribution<type>(0, type(sup_value - 1))(xor128);
}

vector<type> make_random_vector(const u32 N, const i64 sup_value) {
	vector<type> res(N);
	for (u32 i = 0; i < N; i++) res[i] = make_random(sup_value);
	return res;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/mytest/RBSTSet.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/1/ITP1_1_A"
#include <bits/stdc++.h>

using namespace std;

#line 1 "test/mytest/../../datastructure/BinarySearchTree/develop/RBSTset.cpp"
#include <bits/stdc++.h>

using namespace std;

namespace rbst_n{
template<class KEY, class Compare>
class RBSTSetIterator;
template<class KEY, class Compare = less<KEY>>
struct RBSTSet {
	using u32 = uint_fast32_t;
	using i32 = int_fast32_t;
	using random_type = u32;
	friend RBSTSetIterator<KEY, Compare>;
	using iterator = RBSTSetIterator<KEY, Compare>;
	inline random_type xor128() {
		static random_type x = 123456789u, y = 362436069u, z = 521288629u, w = 88675123u;
		random_type t = x ^ (x << 11);
		x = y; y = z; z = w;
		return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
	}
	inline random_type xor128(const random_type sup_value) { return xor128() % sup_value;}
	struct node {
		KEY key;
		node *lch, *rch, *par;
		u32 cnt;
		node(KEY k) : key(k), lch(nil), rch(nil), par(nil), cnt(1) {}
		node() : key(), lch(this), rch(this), par(this), cnt(0) {}
		static node* const nil;
	};
	using np = node*;
	np top;
	RBSTSet() : top(node::nil) {}
	void insert(const KEY&& key) { top = insert(new node(key), top);}
	void insert(const KEY& key) { insert((KEY&&)key);}
	void erase(const KEY&& key) { top = erase(key, top);}
	void erase(const KEY& key) { top = erase(key, top);}
	const KEY& kth_element(u32 idx) {
		assert(idx < size());
		np n = top;
		for (u32 sz = n->lch->cnt + 1; sz != idx + 1; sz = n->lch->cnt + 1) {
			if (sz <= idx) idx -= sz, n = n->rch;
			else n = n->lch;
		}
		return n->key;
	}
	inline const u32 size() const {
		return top->cnt;
	}
	inline iterator begin() const { 
		np n = most_lch(top);
		return iterator(n, n->par);
	}
	inline iterator end() const { return iterator(node::nil, most_rch(top)); }
	void check(bool print_node = false) {
		if (print_node) cerr << "nil " << node::nil << " ";
		if (print_node) cerr << "par " << node::nil->par << " ";
		if (print_node) cerr << "lch " << node::nil->lch << " ";
		if (print_node) cerr << "rch " << node::nil->rch << " ";
		if (print_node) cerr << endl;
		assert(top->par == node::nil);
		check_dfs(top, print_node);
	}
private:
	np erase(const KEY& key, np n) {
		assert(n != node::nil);
		if (Compare()(key, n->key)) {
			n->lch = erase(key, n->lch);
			return update_lch(n);
		} else if (Compare()(n->key, key)) {
			n->rch = erase(key, n->rch);
			return update_rch(n);
		} else {
			np dn = n;
			n = merge(n->lch, n->rch);
			if (n->par == dn) n->par = node::nil;
			delete dn;
			return n;
		}
	}
	bool is_left_node_smaller(np l, np r) { return xor128(l->cnt + r->cnt) < r->cnt;}
	inline np update(np n) {
		n->cnt = n->lch->cnt + n->rch->cnt + 1;
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
	u32 find_insert_pos_(np new_node, np n) {
		u32 pos = 0;
		while (n != node::nil) {
			if (Compare()(new_node->key, n->key)) n = n->lch;
			else pos += n->lch->cnt + 1, n = n->rch;
		}
		return pos;
	}
	np insert(np new_node, np n) {
		if (n == node::nil) return new_node;
		if (xor128(n->cnt+1)) {
			if (Compare()(new_node->key, n->key)) {
				n->lch = insert(new_node, n->lch);
				return update_lch(n);
			} else {
				n->rch = insert(new_node, n->rch);
				return update_rch(n);
			}
		} else {
			auto p = split(n, find_insert_pos_(new_node, n));
			new_node->lch = p.first;
			new_node->rch = p.second;
			return update_lr_ch(new_node);
		}
	}
	void check_dfs(np n, bool print_node) {
		if (n == node::nil) return;
		if (print_node) cerr << "np " << n << " ";
		if (print_node) cerr << "par " << n->par << " ";
		if (print_node) cerr << "key " << n->key << " ";
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
	inline static np next_par(np n) {
		for (; n->par->rch == n; n = n->par);
		return n->par;
	}
	inline static np prev_par(np n) {
		for (; n->par->lch == n; n = n->par);
		return n->par;
	}
	inline static np most_lch(np n) {
		for (; n->lch != node::nil; n = n->lch);
		return n;
	}
	inline static np most_rch(np n) {
		for (; n->rch != node::nil; n = n->rch);
		return n;
	}
	inline static iterator next(np n) {
		if (n == node::nil) throw out_of_range("Error at RBSTSet::iterator next(np n)");
		if (n->rch == node::nil) {
			const np n_par = next_par(n);
			if (n_par == node::nil) return iterator(node::nil, n);
			else return iterator(n_par, n_par->par);
		}
		else {
			const np n_lch = most_lch(n->rch);
			return iterator(n_lch, n_lch->par);
		}
	}
	inline static iterator prev(const iterator& i) {
		if (i.node_ptr == node::nil) return iterator(i.par, i.par->par);
		if (i.node_ptr->lch == node::nil) {
			const np n_par = prev_par(i.node_ptr);
			if (n_par == node::nil) return iterator(node::nil, i.node_ptr);
			return iterator(n_par, n_par->par);
		}
		else {
			const np n_rch = most_rch(i.node_ptr->lch);
			return iterator(n_rch, n_rch->par);
		}
	}
};
	template<class T, class U> typename RBSTSet<T, U>::node* const RBSTSet<T, U>::node::nil = new node();
template<class KEY, class Compare>
class RBSTSetIterator {
	friend RBSTSet<KEY, Compare>;
	using node = typename RBSTSet<KEY, Compare>::node;
	using np = node*;
	np node_ptr;
	np par;
public:
	RBSTSetIterator(np n, np p) : node_ptr(n), par(p) {}
	RBSTSetIterator(const RBSTSetIterator& I) : node_ptr(I.node_ptr), par(I.par) {}
	RBSTSetIterator& operator++() {
		return *this = RBSTSet<KEY, Compare>::next(node_ptr);
	}
	RBSTSetIterator operator++(int unused) {
		RBSTSetIterator result = *this;
		*this = RBSTSet<KEY, Compare>::next(node_ptr);
		return result;
	}
	RBSTSetIterator& operator--() {
		return *this = RBSTSet<KEY, Compare>::prev(*this);
	}
	RBSTSetIterator operator--(int unused) {
		RBSTSetIterator result = *this;
		*this = RBSTSet<KEY, Compare>::prev(*this);
		return result;
	}
	// int operator-(const RBSTSetIterator& R) {
	// 	node::return list_ptr->get_position() - R.list_ptr->get_position();
	// }
	const KEY& operator*() const {
		assert(node_ptr != node::nil);
		return node_ptr->key;
	}
	bool operator==(const RBSTSetIterator& T) {
		return this->node_ptr == T.node_ptr;
	}
	bool operator!=(const RBSTSetIterator& R) {
		return !(*this == R);
	}
};
} // rbst_n
using namespace rbst_n;

// int main() {
// 	int Q;
// 	scanf("%d", &Q);
// 	RBSTSet<int, greater<int>> T;
// 	while (Q--) {
// 		int t, x; scanf("%d%d", &t, &x);
// 		if (t == 1) {
// 			T.insert(-x);
// 		} else {
// 			int r = -T.kth_element(x-1);
// 			cout << r << endl;
// 			T.erase(-r);
// 		}
// 	}
// }
// 	T.check();
// }


// void check_insert(const int);
// void check_erase(const int);
// bool check(RBSTSet<int>& R, multiset<int>& S);

// int main()
// {
	// cout << "START INSERT TEST" << endl;
	// check_insert(100000);
	// cout << "PASSED" << endl;
	// cout << "START ERASE TEST" << endl;
	// check_erase(100000);
	// cout << "PASSED" << endl;
// 	RBSTSet<int> T;
// 	T.insert(1);
// 	return 0;
// }


// void check_insert(const int MAX)
// {
// 	RBSTSet<int> T_random_big;
// 	RBSTSet<int> T_random_small;
// 	RBSTSet<int> T_increase;
// 	RBSTSet<int> T_decrease;

// 	multiset<int> S_random_big;
// 	multiset<int> S_random_small;
// 	multiset<int> S_increase;
// 	multiset<int> S_decrease;

// 	std::random_device seed_gen;
// 	std::mt19937 engine(seed_gen());

// 	std::uniform_real_distribution<> dist1(-1.0, 1.0);

// 	for (int i = -MAX; i < MAX; i++) {
// 		int big = 1000000000 * dist1(engine);
// 		int small = 100 * dist1(engine);
// 		T_random_big.insert(big);
// 		T_random_small.insert(small);
// 		T_increase.insert(i);
// 		T_decrease.insert(-i);
// 		S_random_big.insert(big);
// 		S_random_small.insert(small);
// 		S_increase.insert(i);
// 		S_decrease.insert(-i);
// 	}
// 	auto T_copy(T_random_big);
// 	auto S_copy = S_random_big;
// 	RBSTSet<int> T_assign;
// 	T_assign = T_random_big;
// 	for (int i = -MAX; i < MAX; i++) {
// 		int big = 1000000000 * dist1(engine);
// 		T_copy.insert(big);
// 		T_assign.insert(big);
// 		S_copy.insert(big);
// 	}
// 	assert(check(T_increase, S_increase));
// 	assert(check(T_decrease, S_decrease));
// 	assert(check(T_random_big, S_random_big));
// 	assert(check(T_random_small, S_random_small));
// 	assert(check(T_copy, S_copy));
// 	assert(check(T_assign, S_copy));
// 	// assert(T_increase.is_balanced());
// 	// assert(T_decrease.is_balanced());
// 	// assert(T_random_big.is_balanced());
// 	// assert(T_copy.is_balanced());
// 	// assert(T_assign.is_balanced());
// 	// assert(T_random_small.is_balanced());
// 	return;
// }

// void check_erase(const int MAX)
// {
// 	RBSTSet<int> R_random_small;
// 	RBSTSet<int> R_increase;
// 	RBSTSet<int> R_decrease;
// 	RBSTSet<int> R_nothing;

// 	multiset<int> S_random_small;
// 	multiset<int> S_increase;
// 	multiset<int> S_decrease;
// 	multiset<int> S_nothing;

// 	std::random_device seed_gen;
// 	std::mt19937 engine(seed_gen());

// 	std::uniform_real_distribution<> dist1(-1.0, 1.0);

// 	for (int i = -MAX; i < MAX; i++) {
// 		int big = 1000000000 * dist1(engine);
// 		int small = 100 * dist1(engine);
// 		R_random_small.insert(small);
// 		R_increase.insert(i);
// 		R_decrease.insert(i);
// 		R_nothing.insert(big);
// 		S_random_small.insert(small);
// 		S_increase.insert(i);
// 		S_decrease.insert(i);
// 	}
// 	for (int i = 0; i < MAX; i++) {
// 		R_increase.erase(-i - 1);
// 		R_decrease.erase(i);
// 		S_increase.erase(-i - 1);
// 		S_decrease.erase(i);
// 	}

// 	for (int i = -100; i <= 100; i++) {
// 		assert(R_random_small.count(i) == (int) S_random_small.count(i));
// 		assert((int) S_random_small.count(i) == R_random_small.upper_bound(i) - R_random_small.lower_bound(i));
// 	}

// 	for (int i = 0; i < 10; i++) {
// 		int small = 100 * dist1(engine);
// 		while (R_random_small.erase(small) != R_random_small.end());
// 		S_random_small.erase(small);
// 	}

// 	for (int i = -100; i <= 100; i++) {
// 		assert(R_random_small.count(i) == (int) S_random_small.count(i));
// 		assert((int) S_random_small.count(i) == R_random_small.upper_bound(i) - R_random_small.lower_bound(i));
// 	}

// 	while (R_nothing.erase(*(R_nothing.begin())) != R_nothing.end());

// 	assert(check(R_increase, S_increase));
// 	assert(check(R_decrease, S_decrease));
// 	assert(check(R_random_small, S_random_small));
// 	assert(check(R_nothing, S_nothing));
// 	assert(R_increase.is_balanced());
// 	assert(R_decrease.is_balanced());
// 	assert(R_random_small.is_balanced());
// 	return;
// }

// bool check(RBSTSet<int>& R, multiset<int>& S)
// {
// 	auto itr_S = S.begin();
// 	auto itr_R = R.begin();
// 	if ((int) S.size() != R.size()) {
// 		cerr << "S.size() != R.size()" << endl;
// 		return false;
// 	}
// 	for (; itr_R != R.end(); itr_R++, itr_S++) {
// 		if (*itr_R != *itr_S) return false;
// 	}
// 	return itr_S == S.end();
// }
#line 7 "test/mytest/RBSTSet.test.cpp"

struct xorshift {
	using result_type = uint_fast32_t;
	result_type x=123456789u,y=362436069u,z=521288629u,w = 88675123u;
	static constexpr result_type min() {return numeric_limits<result_type>::min();}
	static constexpr result_type max() {return numeric_limits<result_type>::max();}
	xorshift() {}
	result_type operator()() {
		result_type t;
		t = x ^ (x << 11);
		x = y; y = z; z = w;
		return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
	}
};

using u32 = uint_fast32_t;
using i32 = int_fast32_t;
using i64 = int_fast64_t;
using type = u32;

template<class Compare> void check_small_size_queries(const u32 N, const u32 Q, Compare C, const i64 sup_value = -1);
template<class Compare> void check_compare_with_multiset(const RBSTSet<type, Compare>& T, const multiset<type, Compare>& S);
vector<type> make_random_vector(const u32 N, const i64 sup_value);
type make_random(const i64 sup_value);

int main() {
	check_small_size_queries(300, 100, less<type>(), 20);
	check_small_size_queries(300, 100, less<type>());
	check_small_size_queries(300, 100, greater<type>(), 20);
	check_small_size_queries(300, 100, greater<type>());
	cout << "Hello World" << endl;
}

template<class Compare> void check_small_size_queries(const u32 N, const u32 Q, Compare C, const i64 sup_value) {
	RBSTSet<type, Compare> T;
	for (u32 cnt = 0; cnt < Q; cnt++) {
		vector<type> r = make_random_vector(N, sup_value);
		std::multiset<type, Compare> S;
		for (u32 i = 0; i < N; i++) {
			T.insert(r[i]);
			S.insert(r[i]);
			T.check();
			check_compare_with_multiset(T, S);
		}
		shuffle(r.begin(), r.end(), xorshift());
		for (u32 i = 0; i < N; i++) {
			T.erase(r[i]);
			S.erase(S.lower_bound(r[i]));
			T.check();
			check_compare_with_multiset(T, S);
		}
		assert(T.size() == 0);
	}
}

template<class Compare> void check_compare_with_multiset_pp1(const RBSTSet<type, Compare>& T, const multiset<type, Compare>& S);
template<class Compare> void check_compare_with_multiset_pp2(const RBSTSet<type, Compare>& T, const multiset<type, Compare>& S);
template<class Compare> void check_compare_with_multiset_mm1(const RBSTSet<type, Compare>& T, const multiset<type, Compare>& S);
template<class Compare> void check_compare_with_multiset_mm2(const RBSTSet<type, Compare>& T, const multiset<type, Compare>& S);

template<class Compare> void check_compare_with_multiset(const RBSTSet<type, Compare>& T, const multiset<type, Compare>& S) {
	assert(S.size() == T.size());
	if (T.size() == 0) {
		assert(T.begin() == T.end());
		return;
	}
	check_compare_with_multiset_pp1(T, S);
	check_compare_with_multiset_pp2(T, S);
	check_compare_with_multiset_mm1(T, S);
	check_compare_with_multiset_mm2(T, S);
}

template<class Compare> void check_compare_with_multiset_pp1(const RBSTSet<type, Compare>& T, const multiset<type, Compare>& S) {
	auto Ti = T.begin();
	auto Ti2 = T.begin(); Ti2++;
	auto Si = S.begin();
	assert(*Ti == *Si);
	for (; Ti2 != T.end(); ++Ti2) assert(*(++Ti) == *(++Si));
	assert(T.end() == ++Ti);
	assert(S.end() == ++Si);
}
template<class Compare> void check_compare_with_multiset_pp2(const RBSTSet<type, Compare>& T, const multiset<type, Compare>& S) {
	auto Ti = T.begin();
	auto Si = S.begin();
	for (; Ti != T.end();) assert(*(Ti++) == *(Si++));
	assert(T.end() == Ti);
	assert(S.end() == Si);
}
template<class Compare> void check_compare_with_multiset_mm1(const RBSTSet<type, Compare>& T, const multiset<type, Compare>& S) {
	auto Ti = T.end();
	auto Si = S.end();
	for (; Ti != T.begin();) assert(*(--Ti) == *(--Si));
	assert(S.begin() == Si);
	assert(T.begin() == Ti);
}
template<class Compare> void check_compare_with_multiset_mm2(const RBSTSet<type, Compare>& T, const multiset<type, Compare>& S) {
	auto Ti = T.end(); Ti--;
	auto Si = S.end(); Si--;
	for (; Ti != T.begin();) assert(*(Ti--) == *(Si--));
	assert(S.begin() == Si);
	assert(T.begin() == Ti);
	assert(*Ti == *Si);
}

type make_random(const i64 sup_value) {
	static xorshift xor128;
	if (sup_value <= 0) return uniform_int_distribution<type>(numeric_limits<type>::min(), numeric_limits<type>::max())(xor128);
	else return uniform_int_distribution<type>(0, type(sup_value - 1))(xor128);
}

vector<type> make_random_vector(const u32 N, const i64 sup_value) {
	vector<type> res(N);
	for (u32 i = 0; i < N; i++) res[i] = make_random(sup_value);
	return res;
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

