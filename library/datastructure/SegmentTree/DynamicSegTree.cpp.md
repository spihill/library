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


# :heavy_check_mark: datastructure/SegmentTree/DynamicSegTree.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#cbada5aa9c548d7605cff951f3e28eda">datastructure/SegmentTree</a>
* <a href="{{ site.github.repository_url }}/blob/master/datastructure/SegmentTree/DynamicSegTree.cpp">View this file on GitHub</a>
    - Last commit date: 2019-11-11 22:57:51+09:00




## Verified with

* :heavy_check_mark: <a href="../../../verify/test/aoj/DynamicSetgree_RMQ.test.cpp.html">test/aoj/DynamicSetgree_RMQ.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/test/aoj/DynamicSetgree_RSQ.test.cpp.html">test/aoj/DynamicSetgree_RSQ.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<class NODE>
struct DynamicSegTree {
	using NODE_T = typename NODE::NODE_T;
	using ASSIGN_T = typename NODE::ASSIGN_T;
	using index_type = typename NODE::index_type;
	struct NODE_TREE {
		NODE node;
		NODE_TREE *left = nullptr, *right = nullptr;
		explicit NODE_TREE(const NODE& x) : node(x) {}
		explicit NODE_TREE() : node() {}
		explicit NODE_TREE(index_type) : node() {}
		NODE_TREE(const NODE_TREE& x) = default;
		inline void assign(ASSIGN_T x) {
			node.assign(x);
		}
		inline NODE_TREE& operator=(const NODE_TREE& x) {
			node = x.node;
			return *this;
		}
		inline NODE_TREE operator+(const NODE_TREE& rhs) const {
			return NODE_TREE(node + rhs.node);
		}
	};
	index_type min_index, max_index;
	NODE_TREE* root;
	vector<NODE_TREE> sum;
	DynamicSegTree (index_type l, index_type r) {build(l, r+1);}
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
	void build(index_type l, index_type r) {
		min_index = l;
		max_index = l + calc_n(r - l);
		const index_type len = max_index - min_index;
		sum.clear(); sum.resize(__lg(len) + 1);
		sum[0].node.initial_value();
		for (size_t i = 0; i + 1 < sum.size(); i++) {
			sum[i+1] = sum[i] + sum[i];
		}
		root = new NODE_TREE(sum[__lg(len)]);
	}
	inline NODE_TREE sum_binary(index_type len) {
		NODE_TREE nt;
		for (int p = 0; len; p++, len >>= 1) {
			if (len & 1) nt = nt + sum[p];
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
	explicit Node(); // 単位元設定
	inline void initial_value(); // 初期値設定 
	inline Node operator+(const Node& rhs) const; // valとrhs.valの演算(nodeのマージ)
	inline void assign(const U v); // setクエリで代入する際の処理
	using NODE_T = T; using ASSIGN_T = U;
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "datastructure/SegmentTree/DynamicSegTree.cpp"
template<class NODE>
struct DynamicSegTree {
	using NODE_T = typename NODE::NODE_T;
	using ASSIGN_T = typename NODE::ASSIGN_T;
	using index_type = typename NODE::index_type;
	struct NODE_TREE {
		NODE node;
		NODE_TREE *left = nullptr, *right = nullptr;
		explicit NODE_TREE(const NODE& x) : node(x) {}
		explicit NODE_TREE() : node() {}
		explicit NODE_TREE(index_type) : node() {}
		NODE_TREE(const NODE_TREE& x) = default;
		inline void assign(ASSIGN_T x) {
			node.assign(x);
		}
		inline NODE_TREE& operator=(const NODE_TREE& x) {
			node = x.node;
			return *this;
		}
		inline NODE_TREE operator+(const NODE_TREE& rhs) const {
			return NODE_TREE(node + rhs.node);
		}
	};
	index_type min_index, max_index;
	NODE_TREE* root;
	vector<NODE_TREE> sum;
	DynamicSegTree (index_type l, index_type r) {build(l, r+1);}
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
	void build(index_type l, index_type r) {
		min_index = l;
		max_index = l + calc_n(r - l);
		const index_type len = max_index - min_index;
		sum.clear(); sum.resize(__lg(len) + 1);
		sum[0].node.initial_value();
		for (size_t i = 0; i + 1 < sum.size(); i++) {
			sum[i+1] = sum[i] + sum[i];
		}
		root = new NODE_TREE(sum[__lg(len)]);
	}
	inline NODE_TREE sum_binary(index_type len) {
		NODE_TREE nt;
		for (int p = 0; len; p++, len >>= 1) {
			if (len & 1) nt = nt + sum[p];
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
	explicit Node(); // 単位元設定
	inline void initial_value(); // 初期値設定 
	inline Node operator+(const Node& rhs) const; // valとrhs.valの演算(nodeのマージ)
	inline void assign(const U v); // setクエリで代入する際の処理
	using NODE_T = T; using ASSIGN_T = U;
};
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

