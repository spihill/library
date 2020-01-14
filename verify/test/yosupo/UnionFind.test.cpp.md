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


# :heavy_check_mark: test/yosupo/UnionFind.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/yosupo/UnionFind.test.cpp">View this file on GitHub</a>
    - Last commit date: 2019-09-28 16:54:33+09:00


* see: <a href="https://judge.yosupo.jp/problem/unionfind">https://judge.yosupo.jp/problem/unionfind</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/datastructure/UnionFind.cpp.html">datastructure/UnionFind.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include<bits/stdc++.h>

using namespace std;

#include "../../datastructure/UnionFind.cpp"

int main() {
	int N, Q;
	cin >> N >> Q;
	UnionFind U(N);
	while (Q--) {
		int q, u, v;
		cin >> q >> u >> v;
		if (q == 0) {
			U.unite(u, v);
		} else {
			cout << U.same(u, v) << endl;
		}
	}
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yosupo/UnionFind.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include<bits/stdc++.h>

using namespace std;

#line 1 "test/yosupo/../../datastructure/UnionFind.cpp"
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
#line 8 "test/yosupo/UnionFind.test.cpp"

int main() {
	int N, Q;
	cin >> N >> Q;
	UnionFind U(N);
	while (Q--) {
		int q, u, v;
		cin >> q >> u >> v;
		if (q == 0) {
			U.unite(u, v);
		} else {
			cout << U.same(u, v) << endl;
		}
	}
}
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

