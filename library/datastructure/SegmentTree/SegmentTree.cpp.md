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


# :heavy_check_mark: datastructure/SegmentTree/SegmentTree.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#cbada5aa9c548d7605cff951f3e28eda">datastructure/SegmentTree</a>
* <a href="{{ site.github.repository_url }}/blob/master/datastructure/SegmentTree/SegmentTree.cpp">View this file on GitHub</a>
    - Last commit date: 2019-11-11 21:56:13+09:00




## Verified with

* :heavy_check_mark: <a href="../../../verify/test/aoj/SegmentTree_RMQ.test.cpp.html">test/aoj/SegmentTree_RMQ.test.cpp</a>
* :x: <a href="../../../verify/test/aoj/SegmentTree_RSQ.test.cpp.html">test/aoj/SegmentTree_RSQ.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "datastructure/SegmentTree/SegmentTree.cpp"
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

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

