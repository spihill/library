#include <bits/stdc++.h>

using namespace std;

struct random_class {
	struct xorshift {
		using result_type = unsigned int;
		result_type x=123456789u,y=362436069u,z=521288629u,w;
		static constexpr result_type min() {return 0u;}
		static constexpr result_type max() {return UINT_MAX;}
		xorshift(result_type a) : w(a) {}
		result_type operator()() {
			result_type t;
			t = x ^ (x << 11);
			x = y; y = z; z = w;
			return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
		}
	};
	random_device rd;
	xorshift xor128;
	ostream& os;
	random_class(ostream& o) : rd(), xor128(rd()), os(o) {}
	double make_random(double min_v, double max_v) { return uniform_real_distribution<double>(min_v, max_v)(xor128);}
};

random_class R(cout);

template<class T>
struct Treap {
	struct node {
		T val;
		double pri;
		unique_ptr<node> lch, rch;
		int cnt;
		node(T v) : val(v), lch(nullptr), rch(nullptr), cnt(1) {
			pri = R.make_random(DBL_MIN, DBL_MAX);
		}
	};
	node* top;
	Treap(node* t = nullptr) : top(t) {}
	node* update(node* n) {
		n->cnt = count(n->lch) + count(n->rch) + 1;
		return n;
	}
	inline int count(node* n) {
		return !n ? 0 : n->cnt;
	}
	inline int count(unique_ptr<node>& n) {
		return !n ? 0 : n->cnt;
	}
	Treap merge(node* l, node* r) {
		if (!l || !r) return l ? l : r;
		if (l->pri > r->pri) {
			l->rch = unique_ptr<node>(merge(l->rch.get(), r).top);
			return Treap(update(l));
		} else {
			r->lch = unique_ptr<node>(merge(l, r->lch.get()).top);
			return Treap(update(r));
		}
	}
	pair<Treap, Treap> split(node* t, int k) {
		if (!t) return make_pair(nullptr, nullptr);
		if (k <= count(t->lch)) {
			pair<Treap, Treap> s = split(t->lch.get(), k);
			t->lch = unique_ptr<node>(s.second.top);
			return make_pair(Treap(s.first.top), Treap(update(t)));
		} else {
			pair<Treap, Treap> s = split(t->rch.get(), k - count(t->lch) - 1);
			t->rch = unique_ptr<node>(s.first.top);
			return make_pair(Treap(update(t)), Treap(s.second.top));
		}
	}
	void insert(const T&& val) {
		int pos = 0;
		node* n = top;
		while (n) {
			if (n->val < val) n = n->lch.get();
			else pos += count(n->lch) + 1, n = n->rch.get();
		}
		auto t1 = split(top, pos);
		auto t2 = split(t1.second.top, 1);
		node new_node(val);
		Treap t(&new_node);
		node* t_top = merge(t1.first.top, t.top).top;
		top = merge(t_top, t2.second.top).top;
	}
};

int main() {
	Treap<int> T;
	T.insert(1);
	T.insert(2);
	T.insert(3);
	cout << T.top->rch->val << endl;
}