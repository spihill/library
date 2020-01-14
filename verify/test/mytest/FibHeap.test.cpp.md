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


# :x: test/mytest/FibHeap.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/mytest/FibHeap.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-15 01:52:18+09:00




## Depends on

* :heavy_check_mark: <a href="../../../library/datastructure/FibHeap.cpp.html">datastructure/FibHeap.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <bits/stdc++.h>

using namespace std;

#include "../../datastructure/FibHeap.cpp"

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
vector<type> make_random_vector(const u32 N, const i64 sup_value);
type make_random(const i64 sup_value);
template<class Compare> void compare_with_pqueue(const FibHeap<type, Compare>& F, const priority_queue<type, vector<type>, Compare>& Q);

int main() {
	check_small_size_queries(300, 100, less<type>(), 20);
	check_small_size_queries(300, 100, less<type>());
	check_small_size_queries(300, 100, greater<type>(), 20);
	check_small_size_queries(300, 100, greater<type>());
}

template<class Compare> void check_small_size_queries(const u32 N, const u32 Q, Compare C, const i64 sup_value) {
	FibHeap<type, Compare> F;
	for (u32 cnt = 0; cnt < Q; cnt++) {
		vector<type> r = make_random_vector(N, sup_value);
		priority_queue<type, vector<type>, Compare> Q;
		vector<int> query;
		{
			u32 in = N, out = N;
			for (u32 i = 0; i < 2 * N; i++) {
				if (in == out || make_random(in + out) < in) {
					in--;
					query.push_back(1);
				} else {
					query.push_back(0);
					out--;
				}
			}
		}
		for (u32 i = 0, in = 0; i < 2*N; i++) {
			compare_with_pqueue(F, Q);
			if (F.size()) assert(F.top() == Q.top());
			if (query[i]) {
				Q.push(r[in]);
				F.push(r[in++]);
			} else {
				Q.pop();
				F.pop();
			}
		}
		compare_with_pqueue(F, Q);
		assert(F.size() == 0);
	}
}

template<class Compare> void compare_with_pqueue(const FibHeap<type, Compare>& F, const priority_queue<type, vector<type>, Compare>& Q) {
	assert(F.size() == Q.size());
	if (F.size()) assert(F.top() == Q.top());
	F.check();
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
#line 1 "test/mytest/FibHeap.test.cpp"
#include <bits/stdc++.h>

using namespace std;

#line 1 "test/mytest/../../datastructure/FibHeap.cpp"
template<class Key, class Compare = less<Key>>
struct FibHeap {
	struct node; using np = node*;
	using u32 = uint_fast32_t;
	struct node {
		Key key;
		np left, right;
		np par, child;
		u32 degree;
		bool mark;
		node(Key k) : key(k), left(this), right(this), par(nullptr), child(nullptr), degree(0), mark(false) {}
		node() : key(), left(this), right(this), par(nullptr), child(nullptr), degree(0), mark(false) {}
	};
	np maximum;
	np roots;
	u32 n;
	FibHeap() : maximum(nullptr), n(0) {
		roots = new node();
	}
	np push(Key k) {
		n++;
		return push(new node(move(k)));
	}
	template<class... Args> np emplace(Args... args) {
		return push(move(Key(args...)));
	}
	inline np push(np x) {
		insert_node_to_roots(x);
		if (!maximum) maximum = x;
		update_maximum(x);
		return x;
	}
	np pop() {
		np z = maximum;
		if (z) {
			if (np x = z->child) do {
				np next = x->right;
				insert_node_to_roots(x);
				x = next;
			} while (x != z->child);
			cut_par(z); cut_list_sub(z);
			if (roots == roots->right) maximum = nullptr;
			else Consolidate();
			n--;
		}
		return z;
	}
	const Key& top() const {
		return maximum->key;
	}
	void check() const {
		bool f = roots == roots->right;
		for (np x = roots->right; x != roots; x = x->right) {
			assert(!x->par);
			f = f || x == maximum;
		}
		assert(f);
		check_dfs(roots);
	}
	u32 size() const {return n;}
	np increase_key(np x, Key k) {
		assert(!Compare()(k, x->key));
		x->key = move(k);
		np y = x->par;
		if (y && Compare()(y->key, x->key)) {
			cut(x, y);
			cascading_cut(y);
		}
		update_maximum(x);
		return x;
	}
	template<class... Args> np increase_key_emplace(np x, Args... args) {
		return increase_key(move(x), move(Key(args...)));
	}
	bool empty() const {
		return n == 0;
	}
private:
	void cut(np child, np par) {
		par->degree--;
		if (par->child == child) {
			if (child->right == child) par->child = nullptr;
			else par->child = child->right;
		}
		cut_list_sub(child);
		insert_node_to_roots(child);
		child->mark = false;
	}
	void cascading_cut(np y) {
		if (np z = y->par) {
			if (y->mark) {
				cut(y, z);
				cascading_cut(z);
			}
			else y->mark = true;
		}
	}
	int check_dfs(np n) const {
		if (!n) return 0;
		if (n != roots) assert(!Compare()(maximum->key, n->key));
		vector<np> ls = make_list_vector(n);
		int d = ls.size();
		for (auto x : ls) {
			assert(x->left->right == x);
			assert(x->degree == u32(check_dfs(x->child)));
			if (x->child) assert(x->child->par == x);
		}
		return d;
	}
	inline void cut_par(np x) {
		if (!x->par) return;
		x->par->degree--;
		if (x->par->child == x) {
			if (x->right == x) x->par->child = nullptr;
			else x->par->child = x->right;
		}
	}
	inline void insert_node_to_roots(np x) {
		x->par = nullptr;
		x->left = roots;
		x->right = roots->right;
		roots->right = roots->right->left = x;
	}
	inline void insert_node_to_list(np& list, np n) {
		if (!list) list = n->left = n->right = n;
		else {
			n->left = list;
			n->right = list->right;
			list->right = list->right->left = n;
		}
	}
	inline void update_maximum(np x) {
		if (Compare()(maximum->key, x->key)) maximum = x;
	}
	inline void cut_list_sub(np x) {
		x->left->right = x->right;
		x->right->left = x->left;
	}
	inline vector<np> make_list_vector(np n) const {
		if (!n) return move(vector<np>(0));
		vector<np> res(1, n);
		for (np nn = n->right; nn != n; nn = nn->right) {
			res.push_back(nn);
		}
		return move(res);
	}
	inline void Consolidate() {
		const double phi = (1 + sqrt(5)) / 2;
		int sz = 2;
		for (double p = phi; p < n; p *= phi, sz++);
		vector<np> A(sz, nullptr);
		for (np x = roots->right; x != roots;) {
			np next = x->right;
			u32 d = x->degree;
			while (np y = A[d]) {
				if (Compare()(x->key, y->key)) swap(x, y);
				Link(y, x);
				A[d] = nullptr;
				d++;
			}
			A[d] = x;
			x = next;
		}
		maximum = roots->right;
		for (np x = roots->right->right; x != roots; x = x->right) update_maximum(x);
	}
	inline void Link(np child, np par) {
		cut_list_sub(child);
		insert_node_to_list(par->child, child);
		child->par = par;
		par->degree++;
		child->mark = false;
	}
};#line 6 "test/mytest/FibHeap.test.cpp"

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
vector<type> make_random_vector(const u32 N, const i64 sup_value);
type make_random(const i64 sup_value);
template<class Compare> void compare_with_pqueue(const FibHeap<type, Compare>& F, const priority_queue<type, vector<type>, Compare>& Q);

int main() {
	check_small_size_queries(300, 100, less<type>(), 20);
	check_small_size_queries(300, 100, less<type>());
	check_small_size_queries(300, 100, greater<type>(), 20);
	check_small_size_queries(300, 100, greater<type>());
}

template<class Compare> void check_small_size_queries(const u32 N, const u32 Q, Compare C, const i64 sup_value) {
	FibHeap<type, Compare> F;
	for (u32 cnt = 0; cnt < Q; cnt++) {
		vector<type> r = make_random_vector(N, sup_value);
		priority_queue<type, vector<type>, Compare> Q;
		vector<int> query;
		{
			u32 in = N, out = N;
			for (u32 i = 0; i < 2 * N; i++) {
				if (in == out || make_random(in + out) < in) {
					in--;
					query.push_back(1);
				} else {
					query.push_back(0);
					out--;
				}
			}
		}
		for (u32 i = 0, in = 0; i < 2*N; i++) {
			compare_with_pqueue(F, Q);
			if (F.size()) assert(F.top() == Q.top());
			if (query[i]) {
				Q.push(r[in]);
				F.push(r[in++]);
			} else {
				Q.pop();
				F.pop();
			}
		}
		compare_with_pqueue(F, Q);
		assert(F.size() == 0);
	}
}

template<class Compare> void compare_with_pqueue(const FibHeap<type, Compare>& F, const priority_queue<type, vector<type>, Compare>& Q) {
	assert(F.size() == Q.size());
	if (F.size()) assert(F.top() == Q.top());
	F.check();
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

