template<class NODE>
struct SegmentTree_slow {
	using NODE_T = typename NODE::NODE_T;
	using ASSIGN_T = typename NODE::ASSIGN_T;
	struct NODE_BOOL {
		bool unity = true;
		NODE node;
		explicit NODE_BOOL(const NODE& x) : unity(false), node(x) {}
		explicit NODE_BOOL() : unity(true), node() {}
		inline NODE_BOOL& operator=(const NODE_T& x) {
			unity = false;
			node.val = x;
		}
		inline void assign(ASSIGN_T x) {
			unity = false;
			node.assign(x);
		}
		inline NODE_BOOL operator+(const NODE_BOOL& rhs) const {
			if (unity) return NODE_BOOL(rhs);
			if (rhs.unity) return NODE_BOOL(*this);
			return NODE_BOOL(node + rhs.node);
		}
	};
	int n;
	vector<NODE_BOOL> node_bool;
	SegmentTree_slow (int n_) : n(calc_n(n_)), node_bool(2*n-1) {}
	SegmentTree_slow (const vector<NODE_T>& v) : SegmentTree_slow(v.size()) {
		for (size_t i = 0; i < v.size(); i++) {
			node_bool[i+n-1] = v[i];
		}
		for (int i = n - 2; i >= 0; i--){
			node_bool[i] = node_bool[i*2+1] + node_bool[i*2+2];
		}
	}
	void set(int p, ASSIGN_T v) {
		p += n - 1;
		node_bool[p].assign(v);
		while (p) {
			p = (p-1) / 2;
			node_bool[p] = node_bool[p*2+1] + node_bool[p*2+2];
		}
	}
	NODE_BOOL get(int a, int b, int k, int l, int r) {
		if (a <= l && r <= b) {
			return node_bool[k];
		} else if (b <= l || r <= a) {
			return NODE_BOOL();
		}
		return get(a, b, k * 2 + 1, l, (l+r) / 2) + get(a, b, k * 2 + 2, (l+r) / 2, r);
	}
	NODE_T get(int a, int b) {return get(a, b, 0, 0, n).node.val;}
	const NODE_T& operator[](int i) {
		return node_bool[i+n-1].node.val;
	}
	int calc_n(int n_, int t = 1) {return n_ > t ? calc_n(n_, t << 1) : t;}
};
