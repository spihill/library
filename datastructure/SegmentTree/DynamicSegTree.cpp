template<class NODE>
struct DynamicSegTree {
	using NODE_T = typename NODE::NODE_T;
	using ASSIGN_T = typename NODE::ASSIGN_T;
	using index_type = typename NODE::index_type;
	struct NODE_TREE {
		bool unity;
		NODE node;
		NODE_TREE *left = nullptr, *right = nullptr;
		explicit NODE_TREE(const NODE& x) : unity(false), node(x) {}
		explicit NODE_TREE() : unity(true), node() {}
		explicit NODE_TREE(index_type) : unity(true), node() {}
		NODE_TREE(const NODE_TREE& x) = default;
		inline void assign(ASSIGN_T x) {
			unity = false;
			node.assign(x);
		}
		inline NODE_TREE& operator=(const NODE_TREE& x) {
			node = x.node;
			unity = x.unity;
			return *this;
		}
		inline NODE_TREE operator+(const NODE_TREE& rhs) const {
			if (unity) return NODE_TREE(rhs);
			if (rhs.unity) return NODE_TREE(*this);
			return NODE_TREE(node + rhs.node);
		}
	};
	index_type min_index, max_index;
	NODE_TREE* root;
	vector<NODE_TREE> sum;
	DynamicSegTree (index_type l, index_type r, bool fill_monoid = true) {build(l, r+1, fill_monoid);}
	/* デストラクタで資源解放(基本使わない)
	~DynamicSegTree () {
		auto dfs = [](auto& f, NODE_TREE* nt) {
			if (!nt) return;
			f(f, nt->left);
			f(f, nt->right);
			delete nt;
		};
		dfs(dfs, root);
	}
	*/
	void build(index_type l, index_type r, bool fill_monoid) {
		min_index = l;
		max_index = l + calc_n(r - l);
		const index_type len = max_index - min_index;
		sum.clear(); sum.resize(__lg(len) + 1);
		if (!fill_monoid) {
			sum[0].unity = false;
			for (size_t i = 0; i + 1 < sum.size(); i++) {
				sum[i+1] = sum[i] + sum[i];
			}
		}
		root = new NODE_TREE(sum[__lg(len)]);
	}
	inline NODE_TREE sum_binary(index_type len) {
		NODE_TREE nt;
		for (int p = 0; len; p++, len >>= 1) {
			if (len & 1) {
				nt = nt + sum[p];
			}
		}
		return nt;
	}
	NODE_TREE set(index_type p, ASSIGN_T v, NODE_TREE* n, index_type l, index_type r, uint_fast32_t si) {
		if (r - l == 1) {
			n->assign(v);
			return *n;
		} else {
			if (p < (l+r) / 2) {
				if (!n->left) n->left = new NODE_TREE(sum[si-1]);
				if (!n->right) return *n = set(p, v, n->left, l, (l+r)/2, si-1) + sum[si-1];
				return *n = set(p, v, n->left, l, (l+r)/2, si-1) + *(n->right);
			} else {
				if (!n->right) n->right = new NODE_TREE(sum[si-1]);
				if (!n->left) return *n = sum[si-1] + set(p, v, n->right, (l+r)/2, r, si-1);
				return *n = *(n->left) + set(p, v, n->right, (l+r)/2, r, si-1);
			}
		}
	}
	void set(index_type p, ASSIGN_T v) {
		set(p, v, root, min_index, max_index, sum.size()-1);
	}
	NODE_TREE get(index_type a, index_type b, NODE_TREE* n, index_type l, index_type r, uint_fast32_t si) {
		if (a <= l && r <= b) {
			return *n;
		}
		if ((l+r) / 2 <= a) {
			if (!n->right) return sum_binary(min(r, b) - a);
			return get(a, b, n->right, (l+r) / 2, r, si-1);
		}
		if (b <= (l+r) / 2) {
			if (!n->left) return sum_binary(b - max(l, a));
			return get(a, b, n->left, l, (l+r) / 2, si-1);
		}
		return (!n->left ? sum_binary(min(b, (l+r) / 2) - max(a, l)) : get(a, b, n->left , l, (l+r) / 2, si-1)) +
			  (!n->right ? sum_binary(min(b, r) - max(a, (l+r) / 2)) : get(a, b, n->right, (l+r) / 2, r, si-1));
	}
	NODE_T get(index_type a, index_type b) {
		return get(a, b, root, min_index, max_index, sum.size()-1).node.val;
	}
	index_type calc_n(index_type n_, index_type t = 1) {return n_ > t ? calc_n(n_, t << 1) : t;}
};
template<class T, class U = T>
struct Node {
	using index_type = int_fast64_t;
	T val;
	explicit Node(T v) : val(v) {}
	explicit Node(); // 初期値設定
	inline Node operator+(const Node& rhs) const; // valとrhs.valの演算 
	inline void assign(const U v); // setクエリで代入する際の処理
	using NODE_T = T; using ASSIGN_T = U;
};