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
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: datastructure/FibHeapMap.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#8dc87745f885a4cc532acd7b15b8b5fe">datastructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/datastructure/FibHeapMap.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-15 01:52:18+09:00




## Required by

* :heavy_check_mark: <a href="../graph/FibDijkstra.cpp.html">graph/FibDijkstra.cpp</a>
* :heavy_check_mark: <a href="../graph/FibPrim.cpp.html">graph/FibPrim.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/FibHeapMap_Dijkstra.test.cpp.html">test/aoj/FibHeapMap_Dijkstra.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/FibPrim.test.cpp.html">test/aoj/FibPrim.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<class Key, class Val, class Compare = less<Key>>
struct FibHeapMap {
	struct node; using np = node*;
	using u32 = uint_fast32_t;
	struct node {
		pair<Key, Val> value;
		np left, right;
		np par, child;
		u32 degree;
		bool mark;
		node(pair<Key, Val> v) : value(move(v)), left(this), right(this), par(nullptr), child(nullptr), degree(0), mark(false) {}
		node() : value(), left(this), right(this), par(nullptr), child(nullptr), degree(0), mark(false) {}
		const Key& get_key() const {
			return value.first;
		}
		const Val& get_value() const {
			return value.second;
		}
	};
	np maximum;
	np roots;
	u32 n;
	FibHeapMap() : maximum(nullptr), n(0) {
		roots = new node();
	}
	np push(Key k, Val v) { return push(pair<Key, Val>(move(k), move(v)));}
	np push(pair<Key, Val> value) {
		n++;
		return push(new node(move(value)));
	}
	inline np push(np x) {
		insert_node_to_roots(x);
		if (!maximum) maximum = x;
		update_maximum(x);
		return x;
	}
	np pop() {
		np z = maximum;
		if (z) {
			if (np x = z->child) do {
				np next = x->right;
				insert_node_to_roots(x);
				x = next;
			} while (x != z->child);
			cut_par(z); cut_list_sub(z);
			if (roots == roots->right) maximum = nullptr;
			else Consolidate();
			n--;
		}
		return z;
	}
	const pair<Key, Val>& top() const {
		return maximum->value;
	}
	void check() const {
		bool f = roots == roots->right;
		for (np x = roots->right; x != roots; x = x->right) {
			assert(!x->par);
			f = f || x == maximum;
		}
		assert(f);
		check_dfs(roots);
	}
	u32 size() const {return n;}
	np increase_key(np x, Key k) {
		assert(!compare(k, x->value.first));
		x->value.first = move(k);
		np y = x->par;
		if (y && compare(y->value.first, x->value.first)) {
			cut(x, y);
			cascading_cut(y);
		}
		update_maximum(x);
		return x;
	}
	bool empty() const {
		return n == 0;
	}
private:
	inline bool compare(const Key& x, const Key& y) const {
		return Compare()(x, y);
	}
	void cut(np child, np par) {
		par->degree--;
		if (par->child == child) {
			if (child->right == child) par->child = nullptr;
			else par->child = child->right;
		}
		cut_list_sub(child);
		insert_node_to_roots(child);
		child->mark = false;
	}
	void cascading_cut(np y) {
		if (np z = y->par) {
			if (y->mark) {
				cut(y, z);
				cascading_cut(z);
			}
			else y->mark = true;
		}
	}
	int check_dfs(np n) const {
		if (!n) return 0;
		if (n != roots) assert(!compare(maximum->value.first, n->value.first));
		vector<np> ls = make_list_vector(n);
		int d = ls.size();
		for (auto x : ls) {
			assert(x->left->right == x);
			assert(x->degree == u32(check_dfs(x->child)));
			if (x->child) assert(x->child->par == x);
		}
		return d;
	}
	inline void cut_par(np x) {
		if (!x->par) return;
		x->par->degree--;
		if (x->par->child == x) {
			if (x->right == x) x->par->child = nullptr;
			else x->par->child = x->right;
		}
	}
	inline void insert_node_to_roots(np x) {
		x->par = nullptr;
		x->left = roots;
		x->right = roots->right;
		roots->right = roots->right->left = x;
	}
	inline void insert_node_to_list(np& list, np n) {
		if (!list) list = n->left = n->right = n;
		else {
			n->left = list;
			n->right = list->right;
			list->right = list->right->left = n;
		}
	}
	inline void update_maximum(np x) {
		if (compare(maximum->value.first, x->value.first)) maximum = x;
	}
	inline void cut_list_sub(np x) {
		x->left->right = x->right;
		x->right->left = x->left;
	}
	inline vector<np> make_list_vector(np n) const {
		if (!n) return move(vector<np>(0));
		vector<np> res(1, n);
		for (np nn = n->right; nn != n; nn = nn->right) {
			res.push_back(nn);
		}
		return move(res);
	}
	inline void Consolidate() {
		const double phi = (1 + sqrt(5)) / 2;
		int sz = 2;
		for (double p = phi; p < n; p *= phi, sz++);
		vector<np> A(sz, nullptr);
		for (np x = roots->right; x != roots;) {
			np next = x->right;
			u32 d = x->degree;
			while (np y = A[d]) {
				if (compare(x->value.first, y->value.first)) swap(x, y);
				Link(y, x);
				A[d] = nullptr;
				d++;
			}
			A[d] = x;
			x = next;
		}
		maximum = roots->right;
		for (np x = roots->right->right; x != roots; x = x->right) update_maximum(x);
	}
	inline void Link(np child, np par) {
		cut_list_sub(child);
		insert_node_to_list(par->child, child);
		child->par = par;
		par->degree++;
		child->mark = false;
	}
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "datastructure/FibHeapMap.cpp"
template<class Key, class Val, class Compare = less<Key>>
struct FibHeapMap {
	struct node; using np = node*;
	using u32 = uint_fast32_t;
	struct node {
		pair<Key, Val> value;
		np left, right;
		np par, child;
		u32 degree;
		bool mark;
		node(pair<Key, Val> v) : value(move(v)), left(this), right(this), par(nullptr), child(nullptr), degree(0), mark(false) {}
		node() : value(), left(this), right(this), par(nullptr), child(nullptr), degree(0), mark(false) {}
		const Key& get_key() const {
			return value.first;
		}
		const Val& get_value() const {
			return value.second;
		}
	};
	np maximum;
	np roots;
	u32 n;
	FibHeapMap() : maximum(nullptr), n(0) {
		roots = new node();
	}
	np push(Key k, Val v) { return push(pair<Key, Val>(move(k), move(v)));}
	np push(pair<Key, Val> value) {
		n++;
		return push(new node(move(value)));
	}
	inline np push(np x) {
		insert_node_to_roots(x);
		if (!maximum) maximum = x;
		update_maximum(x);
		return x;
	}
	np pop() {
		np z = maximum;
		if (z) {
			if (np x = z->child) do {
				np next = x->right;
				insert_node_to_roots(x);
				x = next;
			} while (x != z->child);
			cut_par(z); cut_list_sub(z);
			if (roots == roots->right) maximum = nullptr;
			else Consolidate();
			n--;
		}
		return z;
	}
	const pair<Key, Val>& top() const {
		return maximum->value;
	}
	void check() const {
		bool f = roots == roots->right;
		for (np x = roots->right; x != roots; x = x->right) {
			assert(!x->par);
			f = f || x == maximum;
		}
		assert(f);
		check_dfs(roots);
	}
	u32 size() const {return n;}
	np increase_key(np x, Key k) {
		assert(!compare(k, x->value.first));
		x->value.first = move(k);
		np y = x->par;
		if (y && compare(y->value.first, x->value.first)) {
			cut(x, y);
			cascading_cut(y);
		}
		update_maximum(x);
		return x;
	}
	bool empty() const {
		return n == 0;
	}
private:
	inline bool compare(const Key& x, const Key& y) const {
		return Compare()(x, y);
	}
	void cut(np child, np par) {
		par->degree--;
		if (par->child == child) {
			if (child->right == child) par->child = nullptr;
			else par->child = child->right;
		}
		cut_list_sub(child);
		insert_node_to_roots(child);
		child->mark = false;
	}
	void cascading_cut(np y) {
		if (np z = y->par) {
			if (y->mark) {
				cut(y, z);
				cascading_cut(z);
			}
			else y->mark = true;
		}
	}
	int check_dfs(np n) const {
		if (!n) return 0;
		if (n != roots) assert(!compare(maximum->value.first, n->value.first));
		vector<np> ls = make_list_vector(n);
		int d = ls.size();
		for (auto x : ls) {
			assert(x->left->right == x);
			assert(x->degree == u32(check_dfs(x->child)));
			if (x->child) assert(x->child->par == x);
		}
		return d;
	}
	inline void cut_par(np x) {
		if (!x->par) return;
		x->par->degree--;
		if (x->par->child == x) {
			if (x->right == x) x->par->child = nullptr;
			else x->par->child = x->right;
		}
	}
	inline void insert_node_to_roots(np x) {
		x->par = nullptr;
		x->left = roots;
		x->right = roots->right;
		roots->right = roots->right->left = x;
	}
	inline void insert_node_to_list(np& list, np n) {
		if (!list) list = n->left = n->right = n;
		else {
			n->left = list;
			n->right = list->right;
			list->right = list->right->left = n;
		}
	}
	inline void update_maximum(np x) {
		if (compare(maximum->value.first, x->value.first)) maximum = x;
	}
	inline void cut_list_sub(np x) {
		x->left->right = x->right;
		x->right->left = x->left;
	}
	inline vector<np> make_list_vector(np n) const {
		if (!n) return move(vector<np>(0));
		vector<np> res(1, n);
		for (np nn = n->right; nn != n; nn = nn->right) {
			res.push_back(nn);
		}
		return move(res);
	}
	inline void Consolidate() {
		const double phi = (1 + sqrt(5)) / 2;
		int sz = 2;
		for (double p = phi; p < n; p *= phi, sz++);
		vector<np> A(sz, nullptr);
		for (np x = roots->right; x != roots;) {
			np next = x->right;
			u32 d = x->degree;
			while (np y = A[d]) {
				if (compare(x->value.first, y->value.first)) swap(x, y);
				Link(y, x);
				A[d] = nullptr;
				d++;
			}
			A[d] = x;
			x = next;
		}
		maximum = roots->right;
		for (np x = roots->right->right; x != roots; x = x->right) update_maximum(x);
	}
	inline void Link(np child, np par) {
		cut_list_sub(child);
		insert_node_to_list(par->child, child);
		child->par = par;
		par->degree++;
		child->mark = false;
	}
};
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

