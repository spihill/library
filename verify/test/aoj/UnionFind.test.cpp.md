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


# :heavy_check_mark: test/aoj/UnionFind.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#0d0c91c0cca30af9c1c9faef0cf04aa9">test/aoj</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/UnionFind.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-21 01:56:02+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_11_D&lang=ja">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_11_D&lang=ja</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/datastructure/UnionFind.cpp.html">Union Find Tree</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_11_D&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/UnionFind.cpp"

int main() {
	int n, m;
	cin >> n >> m;
	UnionFind uf(n);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		uf.unite(a, b);
	}
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		int a, b;
		cin >> a >> b;
		if (uf.same(a, b)) cout << "yes" << endl;
		else cout << "no" << endl;
	}
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj/UnionFind.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_11_D&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#line 1 "test/aoj/../../datastructure/UnionFind.cpp"
/** 
 * @title Union Find Tree
 * @brief 初期化以外の各操作がほぼ$O(1)$で完了すると思ってよい。 0-indexed
 */
struct UnionFind {
	vector<int> par;
	UnionFind(int a) : par(a, -1) {}
// 頂点 x の親を返す
	int root(int x) { return par[x] < 0 ? x : par[x] = root(par[x]);}
// @brief 頂点 x と 頂点 y が連結されているか
	bool same(int x, int y) { return root(x) == root(y);}
// @brief 頂点 x と 頂点 y を連結する。すでに連結していたら false
	bool unite(int x, int y) {
		x = root(x);
		y = root(y);
		if (x == y) return false;
		if (size(x) < size(y)) swap(x, y);
		par[x] += par[y];
		par[y] = x;
		return true;
	}
// @brief 頂点 x が所属しているグループのサイズを返す
	int size(int x) { return -par[root(x)];}
};
#line 8 "test/aoj/UnionFind.test.cpp"

int main() {
	int n, m;
	cin >> n >> m;
	UnionFind uf(n);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		uf.unite(a, b);
	}
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		int a, b;
		cin >> a >> b;
		if (uf.same(a, b)) cout << "yes" << endl;
		else cout << "no" << endl;
	}
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

