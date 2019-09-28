template<class NODE, class LAZY>
struct LazySegmentTree {
	int n;
	const NODE NODE_UNITY;
	const LAZY LAZY_UNITY;
	vector<NODE> node;
	vector<LAZY> lazy;
	using M = function<NODE(NODE, NODE)>;
	using R = function<NODE(NODE, LAZY)>;
	using A = function<LAZY(LAZY, LAZY)>;
	using P = function<LAZY(LAZY, int)>;
	M merge;
	R reflect;
	A add;
	P propagate;
	// n_ : size
	// m : NODE merge(NODE, NODE) 要素と要素をマージする
	// r : NODE reflect(NODE, LAZY) 要素に作用素を作用させる
	// a : LAZY add(LAZY, LAZY) 作用素と作用素をマージする
	// p : LAZY propagate(LAZY, int) 作用素を区間幅に合わせて変化させる e.g. return b; return a * b;
	// node_unity : 要素の単位元
	// lazy_unity : 作用素の単位元
	LazySegmentTree (M m, R r, A a, P p, NODE node_unity, LAZY lazy_unity) : NODE_UNITY(node_unity), LAZY_UNITY(lazy_unity), merge(m), reflect(r), add(a), propagate(p) {}
	void build(int n_) {
		n = calc_n(n_);
		node.clear(); node.resize(2*n-1, NODE_UNITY);
		lazy.clear(); lazy.resize(2*n-1, LAZY_UNITY);
	}
	void build(const vector<NODE>& v) {
		build(v.size());
		for (size_t i = 0; i < v.size(); i++) {
			node[i+n-1] = v[i];
		}
		for (int i = n - 2; i >= 0; i--){
			node[i] = merge(node[i*2+1], node[i*2+2]);
		}
	}
	void eval(int len, int k) {
		if (lazy[k] == LAZY_UNITY) return;
		if (2*k+1 < 2*n-1) {
			lazy[2*k+1] = add(lazy[2*k+1], lazy[k]);
			lazy[2*k+2] = add(lazy[2*k+2], lazy[k]);
		}
		node[k] = reflect(node[k], propagate(lazy[k], len));
		lazy[k] = LAZY_UNITY;
	}
	NODE set(int a, int b, LAZY x, int k, int l, int r) {
		eval(r-l, k);
		if (r <= a || b <= l) return node[k];
		if (a <= l && r <= b) {
			lazy[k] = add(lazy[k], x);
			return reflect(node[k], propagate(lazy[k], r-l));
		}
		return node[k] = merge(set(a, b, x, 2*k+1, l, (l+r) / 2), 
		                       set(a, b, x, 2*k+2, (l+r) / 2, r));
	}
	void set(int a, int b, LAZY x) {set(a, b, x, 0, 0, n);}
	NODE get(int a, int b, int k, int l, int r) {
		eval(r-l, k);
		if (a <= l && r <= b) {
			return node[k];
		} else if (b <= l || r <= a) {
			return NODE_UNITY;
		}
		return merge(get(a, b, 2*k+1, l, (l+r) / 2), 
		             get(a, b, 2*k+2, (l+r) / 2, r));
	}
	NODE get(int a, int b) {return get(a, b, 0, 0, n);}
	const NODE& operator[](int i) {
		return node[i+n-1];
	}
	int calc_n(int n_, int t = 1) {return n_ > t ? calc_n(n_, t << 1) : t;}
};