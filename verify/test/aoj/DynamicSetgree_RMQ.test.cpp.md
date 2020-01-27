---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :heavy_check_mark: test/aoj/DynamicSetgree_RMQ.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/DynamicSetgree_RMQ.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-27 00:26:08+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A">https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/datastructure/SegmentTree/DynamicSegTree.cpp.html">動的セグメント木</a>
* :heavy_check_mark: <a href="../../../library/math/msb_pos.cpp.html">msb の位置を調べる</a>
* :heavy_check_mark: <a href="../../../library/monoid/min_monoid.cpp.html">monoid/min_monoid.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/SegmentTree/DynamicSegTree.cpp"
#include "../../monoid/min_monoid.cpp"

int main() {
	int N, Q;
	cin >> N >> Q;
	DynamicSegTree<min_monoid<int>> S(-100, N+100);
	for (int i = 0; i < Q; i++) {
		int q, x, y; cin >> q >> x >> y;
		if (q == 0) {
			x -= 50;
			S.set(x, y);
		} else {
			x -= 50; y -= 50;
			y++;
			cout << S.get(x, y) << endl;
		}
	}
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj/DynamicSetgree_RMQ.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A"

#include<bits/stdc++.h>

using namespace std;

#line 1 "test/aoj/../../datastructure/SegmentTree/../../math/msb_pos.cpp"
struct upper_bit {
	using u64 = uint_fast64_t;
	u64 val[65];
	constexpr upper_bit() : val() {
		val[64] = 0;
		val[63] = u64(1) << 63;
		for (size_t i = 62; ~i; i--) {
			val[i] = (val[i+1] >> 1) | val[63];
		}
	}
};
/**
 * @title msb の位置を調べる
 * @brief __lg の代用関数で、msb が何桁目かを返す (0-indexed で msb が無い場合は -1) ($O(\log \log N)$)
 */
template<class T>
constexpr enable_if_t<is_integral<T>::value, int> msb_pos(T x) {
	static_assert(numeric_limits<make_unsigned_t<T>>::digits < 65, "");
	constexpr auto ub = upper_bit();
	int ok = numeric_limits<make_unsigned_t<T>>::digits, ng = -1;
	while (ok - ng != 1) {
		int mid = (ok + ng) >> 1;
		(ub.val[mid] & x ? ng : ok) = mid;
	}
	return ok - 1;
}#line 2 "test/aoj/../../datastructure/SegmentTree/DynamicSegTree.cpp"
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
};#line 1 "test/aoj/../../monoid/min_monoid.cpp"
template<class T>
struct min_monoid {
	using mono = min_monoid;
	min_monoid() : min_monoid(numeric_limits<T>::max()) {}
	explicit min_monoid(T x) : val(x) {}
	T val;
	mono operator+(const mono& rhs) const {
		return mono(min(val, rhs.val));
	}
	friend istream& operator>>(istream& lhs, mono& rhs) {
		lhs >> rhs.val;
		return lhs;
	}
	friend ostream& operator<<(ostream& lhs, mono& rhs) {
		lhs << rhs.val;
		return lhs;
	}
	using monoid_type = T;
};#line 9 "test/aoj/DynamicSetgree_RMQ.test.cpp"

int main() {
	int N, Q;
	cin >> N >> Q;
	DynamicSegTree<min_monoid<int>> S(-100, N+100);
	for (int i = 0; i < Q; i++) {
		int q, x, y; cin >> q >> x >> y;
		if (q == 0) {
			x -= 50;
			S.set(x, y);
		} else {
			x -= 50; y -= 50;
			y++;
			cout << S.get(x, y) << endl;
		}
	}
}
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

