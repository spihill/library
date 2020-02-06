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


# :heavy_check_mark: test/aoj/Knapsack.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/Knapsack.test.cpp">View this file on GitHub</a>
    - Last commit date: 2019-09-20 21:46:21+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_1_C">https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_1_C</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/dp/Knapsack.cpp.html">dp/Knapsack.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_1_C"

#include<bits/stdc++.h>

using namespace std;

#include "../../dp/Knapsack.cpp"

int main() {
	int n, W; cin >> n >> W;
	vector<int> v(n), w(n);
	for (int i = 0; i < n; i++) {
		cin >> v[i] >> w[i];
	}
	cout << Knapsack(W, v, w) << endl;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj/Knapsack.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_1_C"

#include<bits/stdc++.h>

using namespace std;

#line 1 "test/aoj/../../dp/Knapsack.cpp"
template<class T, class U>
T Knapsack(const T W_total, const vector<U>& value, const vector<T>& weight) {
	vector<U> dp(W_total+1);
	for (size_t i = 0; i < value.size(); i++) {
		for (size_t j = weight[i]; j <= (size_t) W_total; j++) {
			dp[j] = max(dp[j], dp[j-weight[i]] + value[i]);
		}
	}
	return dp[W_total];
}
#line 8 "test/aoj/Knapsack.test.cpp"

int main() {
	int n, W; cin >> n >> W;
	vector<int> v(n), w(n);
	for (int i = 0; i < n; i++) {
		cin >> v[i] >> w[i];
	}
	cout << Knapsack(W, v, w) << endl;
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>
