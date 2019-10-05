template<class NODE>
struct SegmentTree {
	using NODE_T = typename NODE::NODE_T;
	using ASSIGN_T = typename NODE::ASSIGN_T;
	int n;
	vector<NODE> node;
	SegmentTree (int n_) {build(n_);}
	SegmentTree (const vector<NODE_T>& v) {build(v);}
	void build(int n_) {
		n = calc_n(n_);
		node.clear(); node.resize(2*n-1);
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
	void set(int p, ASSIGN_T v) {
		p += n - 1;
		node[p].assign(v);
		while (p) {
			p = (p-1) / 2;
			node[p] = node[p*2+1] + node[p*2+2];
		}
	}
	NODE get(int a, int b, int k, int l, int r) {
		if (a <= l && r <= b) {
			return node[k];
		} else if (b <= l || r <= a) {
			return NODE();
		}
		return get(a, b, k * 2 + 1, l, (l+r) / 2) + get(a, b, k * 2 + 2, (l+r) / 2, r);
	}
	NODE_T get(int a, int b) {return get(a, b, 0, 0, n).val;}
	const NODE_T& operator[](int i) {
		return node[i+n-1].val;
	}
	int calc_n(int n_, int t = 1) {return n_ > t ? calc_n(n_, t << 1) : t;}
};
