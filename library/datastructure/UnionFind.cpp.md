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


# :heavy_check_mark: datastructure/UnionFind.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#8dc87745f885a4cc532acd7b15b8b5fe">datastructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/datastructure/UnionFind.cpp">View this file on GitHub</a>
    - Last commit date: 2019-09-19 13:47:11+09:00




## Required by

* :heavy_check_mark: <a href="../graph/Kruskal.cpp.html">graph/Kruskal.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/Kruskal.test.cpp.html">test/aoj/Kruskal.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/Kruskal_2.test.cpp.html">test/aoj/Kruskal_2.test.cpp</a>
* :x: <a href="../../verify/test/aoj/UnionFind.test.cpp.html">test/aoj/UnionFind.test.cpp</a>
* :x: <a href="../../verify/test/yosupo/UnionFind.test.cpp.html">test/yosupo/UnionFind.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct UnionFind {
	int sz;
	vector<int> par;
	UnionFind(int a) : sz(a), par(sz, -1) {}
	int root(int x) { return par[x] < 0 ? x : par[x] = root(par[x]);}
	bool same(int x, int y) { return root(x) == root(y);}
	bool unite(int x, int y) {
		x = root(x);
		y = root(y);
		if (x == y) return false;
		if (size(x) < size(y)) swap(x, y);
		par[x] += par[y];
		par[y] = x;
		return true;
	}
	int size(int x) { return -par[root(x)];}
	int size() { return sz;}
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "datastructure/UnionFind.cpp"
struct UnionFind {
	int sz;
	vector<int> par;
	UnionFind(int a) : sz(a), par(sz, -1) {}
	int root(int x) { return par[x] < 0 ? x : par[x] = root(par[x]);}
	bool same(int x, int y) { return root(x) == root(y);}
	bool unite(int x, int y) {
		x = root(x);
		y = root(y);
		if (x == y) return false;
		if (size(x) < size(y)) swap(x, y);
		par[x] += par[y];
		par[y] = x;
		return true;
	}
	int size(int x) { return -par[root(x)];}
	int size() { return sz;}
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

