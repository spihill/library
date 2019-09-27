template<class NODE, class ASSIGN = NODE>
struct SegmentTree {
	int n;
	const NODE NODE_UNITY;
	vector<NODE> node;
	using M = function<NODE(NODE, NODE)>;
	using A = function<NODE(NODE, ASSIGN)>;
	M merge;
	A assign;
	SegmentTree (int n_, M m, A a, NODE node_unity) : n(calc_n(n_)), NODE_UNITY(node_unity), node(2*n-1, NODE_UNITY), merge(m), assign(a) {}
	SegmentTree (const vector<NODE>& v, M m, A a, NODE node_unity) : SegmentTree(v.size(), m, a, node_unity) {
		for (size_t i = 0; i < v.size(); i++) {
			node[i+n-1] = v[i];
		}
		for (int i = n - 2; i >= 0; i--){
			node[i] = merge(node[i*2+1], node[i*2+2]);
		}
	}
	void set(int p, NODE v) {
		p += n - 1;
		node[p] = assign(node[p], v);
		while (p) {
			p = (p-1) / 2;
			node[p] = merge(node[p*2+1] , node[p*2+2]);
		}
	}
	NODE get(int a, int b, int k, int l, int r) {
		if (a <= l && r <= b) {
			return node[k];
		} else if (b <= l || r <= a) {
			return NODE_UNITY;
		}
		return merge(get(a, b, k * 2 + 1, l, (l+r) / 2), get(a, b, k * 2 + 2, (l+r) / 2, r));
	}
	NODE get(int a, int b) {return get(a, b, 0, 0, n);}
	const NODE& operator[](int i) {
		return node[i+n-1];
	}
	int calc_n(int n_, int t = 1) {return n_ > t ? calc_n(n_, t << 1) : t;}
};