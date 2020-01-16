#include "../../math/msb_pos.cpp"
/**
 * @title 動的セグメント木
 * @brief 必要なノードだけを作るセグメント木。単位元以外で初期値を与えることもできる。
 */
template<class Monoid, class index_type = long long>
struct DynamicSegTree {
private:
	using Monoid_T = typename Monoid::monoid_type;
	struct Monoid_TREE {
		Monoid node;
		Monoid_TREE *left = nullptr, *right = nullptr;
		explicit Monoid_TREE(const Monoid& x) : node(x) {}
		explicit Monoid_TREE() : node() {}
		explicit Monoid_TREE(index_type) : node() {}
		Monoid_TREE(const Monoid_TREE& x) = default;
		inline Monoid_TREE& operator=(const Monoid_TREE& x) {
			node = x.node;
			return *this;
		}
		inline Monoid_TREE operator+(const Monoid_TREE& rhs) const {
			return Monoid_TREE(node + rhs.node);
		}
	};
	const index_type min_index, max_index;
	Monoid_TREE* root;
	vector<Monoid_TREE> sum;
public:
	// @brief 使う index の下限と上限、ノードの初期値を設定する。初期値の default は単位元 $O(\log N)$
	DynamicSegTree (index_type l, index_type r, Monoid_T x = Monoid().val) : min_index(l), max_index(l + calc_n(r - l + 1)) {build(x);}
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
	// @brief index p に v を代入 $O(\log N)$
	void set(index_type p, Monoid_T v) {
		 set(p, v, root, min_index, max_index, sum.size()-1);
	}
	// @brief [a, b) の値を取得。 $O(\log N)$
	Monoid_T get(index_type a, index_type b) {
		return get(a, b, root, min_index, max_index, sum.size()-1).node.val;
	}
	// @brief index p の値を取得 $O(\log N)$
	Monoid_T operator[](index_type p) {
		return get(p, p + 1, root, min_index, max_index, sum.size()-1).node.val;
	}
private:
	void build(Monoid_T x) {
		const index_type len = max_index - min_index;
		sum.clear(); sum.resize(msb_pos(len) + 1);
		sum[0].node.val = x;
		for (size_t i = 0; i + 1 < sum.size(); i++) {
			sum[i+1] = sum[i] + sum[i];
		}
		root = new Monoid_TREE(sum[msb_pos(len)]);
	}
	inline Monoid_TREE sum_binary(index_type len) {
		Monoid_TREE nt;
		for (int p = 0; len; p++, len >>= 1) {
			if (len & 1) nt = nt + sum[p];
		}
		return nt;
	}
	Monoid_TREE set(index_type p, Monoid_T v, Monoid_TREE* n, index_type l, index_type r, uint_fast32_t si) {
		if (r - l == 1) {
			n->node.val = v;
			return *n;
		} else {
			if (p < (l+r) / 2) {
				if (!n->left) n->left = new Monoid_TREE(sum[si-1]);
				if (!n->right) return *n = set(p, v, n->left, l, (l+r)/2, si-1) + sum[si-1];
				return *n = set(p, v, n->left, l, (l+r)/2, si-1) + *(n->right);
			} else {
				if (!n->right) n->right = new Monoid_TREE(sum[si-1]);
				if (!n->left) return *n = sum[si-1] + set(p, v, n->right, (l+r)/2, r, si-1);
				return *n = *(n->left) + set(p, v, n->right, (l+r)/2, r, si-1);
			}
		}
	}
	Monoid_TREE get(index_type a, index_type b, Monoid_TREE* n, index_type l, index_type r, uint_fast32_t si) {
		if (a <= l && r <= b) return *n;
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
	index_type calc_n(index_type n_, index_type t = 1) {return n_ > t ? calc_n(n_, t << 1) : t;}
};