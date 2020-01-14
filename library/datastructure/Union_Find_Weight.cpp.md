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


# :warning: datastructure/Union_Find_Weight.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#8dc87745f885a4cc532acd7b15b8b5fe">datastructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/datastructure/Union_Find_Weight.cpp">View this file on GitHub</a>
    - Last commit date: 2019-07-28 13:56:32+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<class Abel> struct Union_Find_Weight
{
	vector<int> par;
	vector<Abel> diff_weight;
	int n;
	Union_Find_Weight(int a, Abel SUM_UNITY = 0) {init(a, SUM_UNITY);}
	void init(int a, Abel SUM_UNITY) {
		n = a;
		par.resize(n, -1);
		diff_weight.resize(n, SUM_UNITY);
	}
	int root(int x) {
		if (par[x] < 0) return x;
		int r = root(par[x]);
		diff_weight[x] += diff_weight[par[x]];
		return par[x] = r;
	}
	Abel weight(int x) {
		root(x);
		return diff_weight[x];
	}
	Abel diff(int x, int y) {
		return weight(y) - weight(x);
	}
	bool same(int x, int y) {
		return root(x) == root(y);
	}
// weight(y) - weight(x) = w
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
#line 1 "datastructure/Union_Find_Weight.cpp"
template<class Abel> struct Union_Find_Weight
{
	vector<int> par;
	vector<Abel> diff_weight;
	int n;
	Union_Find_Weight(int a, Abel SUM_UNITY = 0) {init(a, SUM_UNITY);}
	void init(int a, Abel SUM_UNITY) {
		n = a;
		par.resize(n, -1);
		diff_weight.resize(n, SUM_UNITY);
	}
	int root(int x) {
		if (par[x] < 0) return x;
		int r = root(par[x]);
		diff_weight[x] += diff_weight[par[x]];
		return par[x] = r;
	}
	Abel weight(int x) {
		root(x);
		return diff_weight[x];
	}
	Abel diff(int x, int y) {
		return weight(y) - weight(x);
	}
	bool same(int x, int y) {
		return root(x) == root(y);
	}
// weight(y) - weight(x) = w
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
	int size(int x) {
		x = root(x);
		return -par[x];
	}
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

