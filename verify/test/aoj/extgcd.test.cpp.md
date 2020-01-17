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


# :heavy_check_mark: test/aoj/extgcd.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/extgcd.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-18 02:21:46+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_E&lang=jp">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_E&lang=jp</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/math/extgcd.cpp.html">拡張ユークリッドの互除法</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_E&lang=jp"

#include<bits/stdc++.h>

using namespace std;
#include "../../math/extgcd.cpp"

int main() {
	int a, b;
	cin >> a >> b;
	int x, y;
	extgcd(a, b, x, y);
	cout << x << " " << y << endl;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj/extgcd.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_E&lang=jp"

#include<bits/stdc++.h>

using namespace std;
#line 1 "test/aoj/../../math/extgcd.cpp"
/**
 * @title 拡張ユークリッドの互除法
 * @brief ax + by = gcd(a, b) を解く
 */
template<class T>
T extgcd(T a, T b, T& x, T& y) {
	T d = a;
	if (b == 0) {
		x = 1;
		y = 0;
	} else {
		d = extgcd(b, a%b, y, x);
		y -= a / b * x;
	}
	return d;
}#line 7 "test/aoj/extgcd.test.cpp"

int main() {
	int a, b;
	cin >> a >> b;
	int x, y;
	extgcd(a, b, x, y);
	cout << x << " " << y << endl;
}
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

