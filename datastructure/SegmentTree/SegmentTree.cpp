template<class NODE>
struct SegmentTree {
	using NODE_T = typename NODE::NODE_T;
	using ASSIGN_T = typename NODE::ASSIGN_T;
	using index_type = uint_fast32_t;
	index_type n;
	vector<NODE> node;
	SegmentTree (index_type n_) {build(n_);}
	SegmentTree (const vector<NODE_T>& v) {build(v);}
	void build(index_type n_) {
		n = calc_n(n_);
		node.clear(); node.resize(2*n-1);
	}
	void build(const vector<NODE_T>& v) {
		build(index_type(v.size()));
		for (size_t i = 0; i < v.size(); i++) {
			node[i+n-1].val = v[i];
		}
		for (int i = n - 2; i >= 0; i--){
			node[i] = node[i*2+1] + node[i*2+2];
		}
	}
	void set(index_type p, ASSIGN_T v) {
		p += n - 1;
		node[p].assign(v);
		while (p) {
			p = (p-1) / 2;
			node[p] = node[p*2+1] + node[p*2+2];
		}
	}
	NODE_T get(index_type l, index_type r) {
		NODE val_l, val_r;
		for (l += n-1, r += n-1; l < r; l /= 2, r = (r - 1) / 2) {
			if (l % 2 == 0) val_l = val_l + node[l];
			if (r % 2 == 0) val_r = node[r-1] + val_r;
		}
		return (val_l + val_r).val;
	}
	const NODE_T& operator[](index_type i) {
		return node[i+n-1].val;
	}
	index_type calc_n(index_type n_, index_type t = 1) {return n_ > t ? calc_n(n_, t << 1) : t;}
};
