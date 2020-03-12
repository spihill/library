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


# :heavy_check_mark: ポテンシャル付き Union Find Tree

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#8dc87745f885a4cc532acd7b15b8b5fe">datastructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/datastructure/WeightedUnionFind.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-21 01:56:02+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/WeightedUnionFind.test.cpp.html">test/aoj/WeightedUnionFind.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/** 
 * @title ポテンシャル付き Union Find Tree
 * @brief 初期化以外の各操作がほぼ$O(1)$で完了すると思ってよい。 0-indexed
 */
template<class Abel>
struct WeightedUnionFind {
	vector<int> par;
	vector<Abel> diff_weight;
	WeightedUnionFind(int N, Abel SUM_UNITY = 0) : par(N, -1), diff_weight(N, SUM_UNITY) {}
// 頂点 x の親を返す
	int root(int x) {
		if (par[x] < 0) return x;
		int r = root(par[x]);
		diff_weight[x] += diff_weight[par[x]];
		return par[x] = r;
	}
// @brief 頂点 x のポテンシャル を返す
	Abel weight(int x) {
		root(x);
		return diff_weight[x];
	}
// @brief weight(y) - weight(x) を返す
	Abel diff(int x, int y) {
		return weight(y) - weight(x);
	}
// @brief 頂点 x と 頂点 y が連結されているか
	bool same(int x, int y) {
		return root(x) == root(y);
	}
// @brief weight(y) - weight(x) = w となるように連結する。連結されなかったら false
	bool unite(int x, int y, Abel w) {
		w += weight(x);
		w -= weight(y);
		x = root(x);
		y = root(y);
		if (x == y) return false;
		if (size(x) < size(y)) swap(x, y), w = -w;
		par[x] += par[y];
		par[y] = x;
		diff_weight[y] = w;
		return true;
	}
// @brief 頂点 x が所属しているグループのサイズを返す
	int size(int x) {
		x = root(x);
		return -par[x];
	}
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "datastructure/WeightedUnionFind.cpp"
/** 
 * @title ポテンシャル付き Union Find Tree
 * @brief 初期化以外の各操作がほぼ$O(1)$で完了すると思ってよい。 0-indexed
 */
template<class Abel>
struct WeightedUnionFind {
	vector<int> par;
	vector<Abel> diff_weight;
	WeightedUnionFind(int N, Abel SUM_UNITY = 0) : par(N, -1), diff_weight(N, SUM_UNITY) {}
// 頂点 x の親を返す
	int root(int x) {
		if (par[x] < 0) return x;
		int r = root(par[x]);
		diff_weight[x] += diff_weight[par[x]];
		return par[x] = r;
	}
// @brief 頂点 x のポテンシャル を返す
	Abel weight(int x) {
		root(x);
		return diff_weight[x];
	}
// @brief weight(y) - weight(x) を返す
	Abel diff(int x, int y) {
		return weight(y) - weight(x);
	}
// @brief 頂点 x と 頂点 y が連結されているか
	bool same(int x, int y) {
		return root(x) == root(y);
	}
// @brief weight(y) - weight(x) = w となるように連結する。連結されなかったら false
	bool unite(int x, int y, Abel w) {
		w += weight(x);
		w -= weight(y);
		x = root(x);
		y = root(y);
		if (x == y) return false;
		if (size(x) < size(y)) swap(x, y), w = -w;
		par[x] += par[y];
		par[y] = x;
		diff_weight[y] = w;
		return true;
	}
// @brief 頂点 x が所属しているグループのサイズを返す
	int size(int x) {
		x = root(x);
		return -par[x];
	}
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

