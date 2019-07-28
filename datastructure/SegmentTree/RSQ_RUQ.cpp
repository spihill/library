/*
	UNITY_NODE sumの単位元
	UNITY_LAZY updateの単位元
	nodeの初期値に注意(init)
	addの呼び出し元に注意(区間の長さに比例する)
	上の関係でUNITY_LAZY / 2も単位元とみなしている
*/
template <class NODE, class LAZY, NODE UNITY_NODE, LAZY UNITY_LAZY>
struct LazySegTree {
// edit start
	void add(LAZY &a, LAZY b) {
		if (b == UNITY_LAZY || b == UNITY_LAZY / 2) return;
		a = b;
	}
	void reflect(NODE& a, LAZY b, int l, int r) {
		if (b == UNITY_LAZY || b == UNITY_LAZY / 2) return;
		a = b;
	}
	NODE merge(NODE a, NODE b) {
		return a + b;
	}
// end
	int n;
	vector<NODE> node;
	vector<LAZY> lazy;
	LazySegTree(int sz) {
		init(sz);
	}
	void init(int sz) {
		n = 1;
		while (n < sz) n *= 2;
		node.assign(2*n-1, 0);
		lazy.assign(2*n-1, UNITY_LAZY);
	}
	void eval(int l, int r, int k) {
		reflect(node[k], lazy[k], l, r);
		if (r - l > 1) {
			add(lazy[k*2+1], lazy[k] / 2);
			add(lazy[k*2+2], lazy[k] / 2);
		}
		lazy[k] = UNITY_LAZY;
	}
	void renode(int k) {
		node[k] = merge(node[k*2+1], node[k*2+2]);
	}
	void set(int a, int b, LAZY x, int k=0, int l=0, int r=-1) {
		if (r < 0) r = n;
		if (b <= l || r <= a) {
			eval(l, r, k);
		} else if (a <= l && r <= b) {
			add(lazy[k], x * (r - l));
			eval(l, r, k);
		} else {
			eval(l, r, k);
			set(a, b, x, k*2+1, l, (l+r) / 2);
			set(a, b, x, k*2+2, (l+r) / 2, r);
			renode(k);
		}
	}
	NODE get(int a, int b, int k=0, int l=0, int r=-1) {
		if (r < 0) r = n;
		eval(l, r, k);
		if (b <= l || r <= a) {
			return UNITY_NODE;
		} else if (a <= l && r <= b) {
			return node[k];
		} else {
			NODE t1 = get(a, b, 2*k+1, l, (l+r) / 2);
			NODE t2 = get(a, b, 2*k+2, (l+r) / 2, r);
			renode(k);
			return merge(t1, t2);
		}
	}
};
