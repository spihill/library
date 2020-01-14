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


# :heavy_check_mark: dp/Knapsack_01.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#95687afb5d9a2a9fa39038f991640b0c">dp</a>
* <a href="{{ site.github.repository_url }}/blob/master/dp/Knapsack_01.cpp">View this file on GitHub</a>
    - Last commit date: 2019-10-06 01:45:43+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/Knapsack_01.test.cpp.html">test/aoj/Knapsack_01.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<class T, class U>
T Knapsack_01(const T W_total, const vector<U>& value, const vector<T>& weight) {
	vector<U> dp(W_total+1);
	for (size_t i = 0; i < value.size(); i++) {
		for (T j = W_total; j >= weight[i]; j--) {
			dp[j] = max(dp[j], dp[j-weight[i]] + value[i]);
		}
	}
	return dp[W_total];
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "dp/Knapsack_01.cpp"
template<class T, class U>
T Knapsack_01(const T W_total, const vector<U>& value, const vector<T>& weight) {
	vector<U> dp(W_total+1);
	for (size_t i = 0; i < value.size(); i++) {
		for (T j = W_total; j >= weight[i]; j--) {
			dp[j] = max(dp[j], dp[j-weight[i]] + value[i]);
		}
	}
	return dp[W_total];
}
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

