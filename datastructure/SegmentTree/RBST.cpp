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