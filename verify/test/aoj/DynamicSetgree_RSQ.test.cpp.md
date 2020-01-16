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


# :heavy_check_mark: test/aoj/DynamicSetgree_RSQ.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/DynamicSetgree_RSQ.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-16 20:29:09+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B">https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/datastructure/SegmentTree/DynamicSegTree.cpp.html">datastructure/SegmentTree/DynamicSegTree.cpp</a>
* :heavy_check_mark: <a href="../../../library/monoid/plus_monoid.cpp.html">monoid/plus_monoid.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B"

#include<bits/stdc++.h>
using namespace std;

#include "../../datastructure/SegmentTree/DynamicSegTree.cpp"
#include "../../monoid/plus_monoid.cpp"

int main() {
	int N, Q;
	cin >> N >> Q;
	DynamicSegTree<plus_monoid<int>> S(-2e18, 2e18, 3);
	for (int i = 0; i < Q; i++) {
		int q, x, y; cin >> q >> x >> y;
		if (q == 0) {
			x -= 50;
			S.set(x, S[x] + y);
		} else {
			x -= 50; y -= 50;
			y++;
			cout << S.get(x, y) - 3 * (y - x) << endl;
		}
	}
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj/DynamicSetgree_RSQ.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B"

#include<bits/stdc++.h>
using namespace std;

#line 1 "test/aoj/../../datastructure/SegmentTree/DynamicSegTree.cpp"
template<class Monoid, class index_type = long long>
struct DynamicSegTree {
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
	DynamicSegTree (index_type l, index_type r, Monoid_T x = Monoid().val) : min_index(l), max_index(l + calc_n(r - l)) {build(x);}
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
	void build(Monoid_T x) {
		const index_type len = max_index - min_index;
		sum.clear(); sum.resize(__lg(len) + 1);
		sum[0].node.val = x;
		for (size_t i = 0; i + 1 < sum.size(); i++) {
			sum[i+1] = sum[i] + sum[i];
		}
		root = new Monoid_TREE(sum[__lg(len)]);
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
	void set(index_type p, Monoid_T v) {
		 set(p, v, root, min_index, max_index, sum.size()-1);
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
	Monoid_T get(index_type a, index_type b) {
		return get(a, b, root, min_index, max_index, sum.size()-1).node.val;
	}
	Monoid_T operator[](index_type a) {
		return get(a, a + 1, root, min_index, max_index, sum.size()-1).node.val;
	}
	index_type calc_n(index_type n_, index_type t = 1) {return n_ > t ? calc_n(n_, t << 1) : t;}
};#line 1 "test/aoj/../../monoid/plus_monoid.cpp"
template<class T>
struct plus_monoid {
	using mono = plus_monoid;
	plus_monoid() : plus_monoid(T()) {}
	explicit plus_monoid(T x) : val(x) {}
	T val;
	mono operator+(const mono& rhs) const {
		return mono(val + rhs.val);
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
};#line 8 "test/aoj/DynamicSetgree_RSQ.test.cpp"

int main() {
	int N, Q;
	cin >> N >> Q;
	DynamicSegTree<plus_monoid<int>> S(-2e18, 2e18, 3);
	for (int i = 0; i < Q; i++) {
		int q, x, y; cin >> q >> x >> y;
		if (q == 0) {
			x -= 50;
			S.set(x, S[x] + y);
		} else {
			x -= 50; y -= 50;
			y++;
			cout << S.get(x, y) - 3 * (y - x) << endl;
		}
	}
}
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

