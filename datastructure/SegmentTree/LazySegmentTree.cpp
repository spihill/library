#include <bits/stdc++.h>
using namespace std;

template<class MonoidPair>
struct LazySegmentTree {
	int n;
	using NODE = typename MonoidPair::NODE; using NODE_T = typename MonoidPair::NODE_T;
	using LAZY = typename MonoidPair::LAZY; using LAZY_T = typename MonoidPair::LAZY_T;
	vector<NODE> node;
	vector<LAZY> lazy;
	LazySegmentTree (int n_) {build(n_);}
	LazySegmentTree (const vector<NODE_T>& v) {build(v);}
	LazySegmentTree () {}
	void build(int n_) {
		n = calc_n(n_);
		node.clear(); node.resize(2*n-1);
		lazy.clear(); lazy.resize(2*n-1);
	}
	void build(const vector<NODE_T>& v) {
		build(v.size());
		for (size_t i = 0; i < v.size(); i++) {
			node[i+n-1].val = v[i];
		}
		for (int i = n - 2; i >= 0; i--){
			node[i] = node[i*2+1] + node[i*2+2];
		}
	}
	void eval(int len, int k) {
		if (lazy[k].val == LAZY::UNITY) return;
		if (2*k+1 < 2*n-1) {
			lazy[2*k+1] = lazy[2*k+1] + lazy[k];
			lazy[2*k+2] = lazy[2*k+2] + lazy[k];
		}
		node[k] = node[k] + lazy[k] * len;
		lazy[k].val = LAZY::UNITY;
	}
	NODE set(int a, int b, LAZY_T x, int k, int l, int r) {
		eval(r-l, k);
		if (r <= a || b <= l) return node[k];
		if (a <= l && r <= b) {
			lazy[k] = lazy[k] + LAZY(x);
			return node[k] + lazy[k] * (r-l);
		}
		return node[k] = set(a, b, x, 2*k+1, l, (l+r) / 2) + set(a, b, x, 2*k+2, (l+r) / 2, r);
	}
	void set(int a, int b, LAZY_T x) {set(a, b, x, 0, 0, n);}
	NODE get(int a, int b, int k, int l, int r) {
		eval(r-l, k);
		if (a <= l && r <= b) {
			return node[k];
		} else if (b <= l || r <= a) {
			return NODE();
		}
		return get(a, b, 2*k+1, l, (l+r) / 2) + get(a, b, 2*k+2, (l+r) / 2, r);
	}
	NODE_T get(int a, int b) {return get(a, b, 0, 0, n).val;}
	const NODE_T& operator[](int i) {
		return node[i+n-1].val;
	}
	int calc_n(int n_, int t = 1) {return n_ > t ? calc_n(n_, t << 1) : t;}
};