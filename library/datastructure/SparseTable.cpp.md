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


# :x: Sparse Table

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#8dc87745f885a4cc532acd7b15b8b5fe">datastructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/datastructure/SparseTable.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-21 01:56:02+09:00




## Verified with

* :x: <a href="../../verify/test/yosupo/SparseTable_RMQ.test.cpp.html">test/yosupo/SparseTable_RMQ.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * @title Sparse Table
 */
template<class T, class F = function<T(T, T)>>
struct SparseTable {
	using index_type = uint_fast32_t;
	vector<vector<T>> table;
	vector<index_type> L;
	const F f;
	SparseTable(F f) : f(f) {}
	SparseTable(F f, const vector<T>& v) : SparseTable(f) { build(v);}
	void build(const vector<T>& v) {
		table.clear();
		const index_type sz = v.size(); 
		table.emplace_back(sz);
		for (index_type i = 0; i < sz; i++) table[0][i] = v[i];
		for (index_type len = 2, pos = 1; len < sz; len <<= 1, pos++) {
			table.emplace_back(sz - len / 2);
			for (index_type i = 0; i + len / 2 < sz; i++) {
				table[pos][i] = f(table[pos-1][i], table[pos-1][i+len/2]);
			}
		}
		L.clear(); L.resize(sz+1);
		index_type len = 1;
		for (index_type i = 1; i <= sz; i++) {
			if ((index_type(1) << len) < i) len++;
			L[i] = len-1;
		}
	}
	T get(index_type l, index_type r) const {
		return f(table[L[r-l]][l], table[L[r-l]][r-(1 << L[r-l])]);
	}
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "datastructure/SparseTable.cpp"
/**
 * @title Sparse Table
 */
template<class T, class F = function<T(T, T)>>
struct SparseTable {
	using index_type = uint_fast32_t;
	vector<vector<T>> table;
	vector<index_type> L;
	const F f;
	SparseTable(F f) : f(f) {}
	SparseTable(F f, const vector<T>& v) : SparseTable(f) { build(v);}
	void build(const vector<T>& v) {
		table.clear();
		const index_type sz = v.size(); 
		table.emplace_back(sz);
		for (index_type i = 0; i < sz; i++) table[0][i] = v[i];
		for (index_type len = 2, pos = 1; len < sz; len <<= 1, pos++) {
			table.emplace_back(sz - len / 2);
			for (index_type i = 0; i + len / 2 < sz; i++) {
				table[pos][i] = f(table[pos-1][i], table[pos-1][i+len/2]);
			}
		}
		L.clear(); L.resize(sz+1);
		index_type len = 1;
		for (index_type i = 1; i <= sz; i++) {
			if ((index_type(1) << len) < i) len++;
			L[i] = len-1;
		}
	}
	T get(index_type l, index_type r) const {
		return f(table[L[r-l]][l], table[L[r-l]][r-(1 << L[r-l])]);
	}
};
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

