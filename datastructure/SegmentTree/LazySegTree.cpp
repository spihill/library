template <class NODE, class LAZY, NODE UNITY_NODE, LAZY UNITY_LAZY>
struct LazySegTree {
// edit start
	NODE merge(NODE a, NODE b) {
//		return a + b;
	}
	LAZY add(LAZY a, LAZY b) {
//		return a + b;
	}
	NODE reflect(NODE a, LAZY b) {
//		return a + b;
	}
	LAZY propagate(LAZY a, int len) {
//		return a;
//		return a * len;
	}
// edit end
	int n;
	vector<NODE> node;
	vector<LAZY> lazy;
	LazySegTree(int n_) {
		init(n_);
	}
	inline void eval(int len, int k) {
		if (lazy[k] == UNITY_LAZY) return;
		if (k*2 + 1 < n*2 - 1) {
			lazy[k*2+1] = add(lazy[k*2+1], lazy[k]);
			lazy[k*2+2] = add(lazy[k*2+2], lazy[k]);
		}
		node[k] = reflect(node[k], propagate(lazy[k], len));
		lazy[k] = UNITY_LAZY;
	}
	void init(int n_) {
		n = 1;
		while (n < n_) n *= 2;
		node.clear();
		lazy.clear();
		node.assign(2*n-1, UNITY_NODE);
		lazy.assign(2*n-1, UNITY_LAZY);
	}
	void build(vector<NODE>& v, int n_ = -1) {
		if (n_ == -1) n_ = v.size();
		for (int i = 0; i < n_; i++) node[i+n-1] = v[i];
		for (int i = n-2; i >= 0; i--) node[i] = merge(node[i*2+1], node[i*2+2]);
	}
	NODE set(int a, int b, LAZY x, int k, int l, int r) {
		eval(r-l, k);
		if (b <= l || r <= a) return node[k];
		if (a <= l && r <= b) {
			lazy[k] = add(lazy[k], x);
			return reflect(node[k], propagate(lazy[k], r-l));
		}
		return node[k] = merge(set(a, b, x, k*2+1, l, (l+r)/2),
		                       set(a, b, x, k*2+2, (l+r)/2, r));
	}
	NODE set(int a, int b, LAZY x) {
		return set(a, b, x, 0, 0, n);
	}
	NODE get(int a, int b, int k, int l, int r) {
		eval(r-l, k);
		if (b <= l || r <= a) return UNITY_NODE;
		if (a <= l && r <= b) return node[k];
		NODE vl = get(a, b, k*2+1, l, (l+r)/2);
		NODE vr = get(a, b, k*2+2, (l+r)/2, r);
		return merge(vl, vr);
	}
	NODE get(int a, int b) {
		return get(a, b, 0, 0, n);
	}
/* Debug
	void print() {
		int x = 0;
		int nx = 2;
		cerr << "NODE" << endl;
		for (int i = 0; i < 2 * n - 1; i++) {
			cerr << node[i] << " ";
			if (i == x) {
				x += nx;
				nx *= 2;
				cerr << endl;
			}
		}
		x = 0;
		nx = 2;
		cerr << endl << endl;;
		cerr << "LAZY" << endl;
		for (int i = 0; i < 2 * n - 1; i++) {
			cerr << lazy[i] << " ";
			if (i == x) {
				x += nx;
				nx *= 2;
				cerr << endl;
			}
		}
		cerr << endl << endl;
	}
*/
};
