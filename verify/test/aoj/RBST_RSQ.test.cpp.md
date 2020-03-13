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


# :heavy_check_mark: test/aoj/RBST_RSQ.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#0d0c91c0cca30af9c1c9faef0cf04aa9">test/aoj</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/RBST_RSQ.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-13 21:37:20+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B">https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/datastructure/SegmentTree/RBST.cpp.html">RBST (Randomized Binary Search Tree)</a>
* :heavy_check_mark: <a href="../../../library/monoid/plus_monoid.cpp.html">monoid/plus_monoid.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/SegmentTree/RBST.cpp"
#include "../../monoid/plus_monoid.cpp"

int main() {
	int N, Q;
	scanf("%d %d", &N, &Q);
	RBST<long long, plus_monoid<long long>> R;
	while (Q--) {
		int q, x, y;
		scanf("%d %d %d", &q, &x, &y);
		if (q == 0) {
			x--;
			R.set(x, R.get(x, x+1) + y);
		} else {
			x--;
			y--;
			printf("%lld\n", R.get(x, y+1));
		}
	}
	return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj/RBST_RSQ.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B"

#include<bits/stdc++.h>

using namespace std;

#line 1 "test/aoj/../../datastructure/SegmentTree/RBST.cpp"
/**
 * @title RBST (Randomized Binary Search Tree)
 * @brief セグ木のようなことができる(座標圧縮不要)
 * @brief 最初は全区間に単位元があるように振る舞う
 * @brief 0-indexed 半開区間
 */
namespace rbst_n{
template<class KEY, class Node, class Compare = less<KEY>>
struct RBST {
	using u32 = uint_fast32_t;
	using i32 = int_fast32_t;
	using random_type = u32;
	using node_type = typename Node::monoid_type;
	struct node {
		KEY key;
		Node monoid;
		Node sum;
		node *lch, *rch, *par;
		u32 cnt;
		node(const KEY& k, const node_type& m) : key(k), monoid(m), sum(m), lch(nil), rch(nil), par(nil), cnt(1) {}
		node(const KEY& k, const node_type& m, const pair<node*, node*>& p) : key(k), monoid(m), sum(m), lch(p.first), rch(p.second), par(nil), cnt(1) {}
		node() : key(), monoid(), sum(), lch(this), rch(this), par(this), cnt(0) {}
		static node* const nil;
	};
	using np = node*;
	np top;
	RBST() : top(node::nil) {}
	void set(const KEY key, const node_type val) { 
		top = insert(key, val, top);
	}
	node_type get(const KEY l, const KEY r) const { return get(l, r, top).val;}
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
	Node get(const KEY& l, const KEY& r, np n) const {
		if (n == node::nil) return Node();
		if (Compare()(n->key, l)) return get(l, r, n->rch);
		if (!Compare()(n->key, r)) return get(l, r, n->lch);
		return Node::merge(get_left(l, n->lch), Node::merge(n->monoid, get_right(r, n->rch)));
	}
	Node get_left(const KEY& l, np n) const {
		if (n == node::nil) return Node();
		if (Compare()(n->key, l)) return get_left(l, n->rch);
		return Node::merge(get_left(l, n->lch), Node::merge(n->monoid, n->rch->sum));
	}
	Node get_right(const KEY& r, np n) const {
		if (n == node::nil) return Node();
		if (!Compare()(n->key, r)) return get_right(r, n->lch);
		return Node::merge(n->lch->sum, Node::merge(n->monoid, get_right(r, n->rch)));
	}
	bool is_left_node_smaller(np l, np r) const { return xor128(l->cnt + r->cnt) < r->cnt;}
	inline np update_sum(np n, np par) {
		for (; n != par->par; n = n->par) n->sum = Node::merge(n->lch->sum, Node::merge(n->monoid, n->rch->sum));
		return par;
	}
	inline np update(np n) {
		n->cnt = n->lch->cnt + n->rch->cnt + 1;
		n->sum = Node::merge(n->lch->sum, Node::merge(n->monoid, n->rch->sum));
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
	np insert(const KEY& key, const node_type& val, np n) {
		if (n == node::nil) return new node(key, val);
		if (xor128(n->cnt+1)) {
			if (Compare()(key, n->key)) {
				n->lch = insert(key, val, n->lch);
				return update_lch(n);
			} else if (Compare()(n->key, key)) {
				n->rch = insert(key, val, n->rch);
				return update_rch(n);
			} else {
				n->monoid = Node(val);
				return update(n);
			}
		} else {
			auto f = find_insert_pos_(key, n);
			if (f.second != node::nil) {
				f.second->monoid = Node(val);
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
using rbst_n::RBST;
#line 1 "test/aoj/../../monoid/plus_monoid.cpp"
namespace plus_monoid_n {
template<class T>
struct plus_monoid {
	using monoid_type = T;
	T val;
	plus_monoid(T v) : val(v) {}
	plus_monoid() : val(0) {}
	static plus_monoid merge(const plus_monoid& lhs, const plus_monoid& rhs) {
		return plus_monoid(lhs.val + rhs.val);
	}
};
}
using plus_monoid_n::plus_monoid;
#line 9 "test/aoj/RBST_RSQ.test.cpp"

int main() {
	int N, Q;
	scanf("%d %d", &N, &Q);
	RBST<long long, plus_monoid<long long>> R;
	while (Q--) {
		int q, x, y;
		scanf("%d %d %d", &q, &x, &y);
		if (q == 0) {
			x--;
			R.set(x, R.get(x, x+1) + y);
		} else {
			x--;
			y--;
			printf("%lld\n", R.get(x, y+1));
		}
	}
	return 0;
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

