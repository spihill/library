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


# :heavy_check_mark: test/aoj/meguru_2.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/meguru_2.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-18 15:06:00+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_4_D&lang=ja">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_4_D&lang=ja</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/algorithm/meguru.cpp.html">algorithm/meguru.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_4_D&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#include "../../algorithm/meguru.cpp"

int main() {
	int n, k;
	cin >> n >> k;
	vector<int> v(n);
	for (auto& x: v) cin >> x;
	auto isok = [&](int x) -> bool {
		int cnt = 1;
		int w = 0;
		for (int i = 0; i < n && cnt <= k; i++) {
			w += v[i];
			if (w > x) w = 0, cnt++, i--;
		}
		return cnt <= k;
	};
	cout << meguru<int>(INT_MAX, 0, isok) << endl;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj/meguru_2.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_4_D&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#line 1 "test/aoj/../../algorithm/meguru.cpp"
// meguru<T>(ok, ng, isok)で呼ぶ
template<class T, class F>
T meguru(T ok, T ng, F isok) {
	static_assert(is_same<decltype(declval<F>()(declval<T>())), bool>::value, ""); 
	while (abs(ok - ng) > 1) {
		T mid = (ok + ng) / 2;
		(isok(mid) ? ok : ng) = mid;
	}
	return ok;
}
#line 8 "test/aoj/meguru_2.test.cpp"

int main() {
	int n, k;
	cin >> n >> k;
	vector<int> v(n);
	for (auto& x: v) cin >> x;
	auto isok = [&](int x) -> bool {
		int cnt = 1;
		int w = 0;
		for (int i = 0; i < n && cnt <= k; i++) {
			w += v[i];
			if (w > x) w = 0, cnt++, i--;
		}
		return cnt <= k;
	};
	cout << meguru<int>(INT_MAX, 0, isok) << endl;
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

