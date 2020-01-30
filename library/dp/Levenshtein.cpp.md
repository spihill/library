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


# :heavy_check_mark: dp/Levenshtein.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#95687afb5d9a2a9fa39038f991640b0c">dp</a>
* <a href="{{ site.github.repository_url }}/blob/master/dp/Levenshtein.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-14 12:20:47+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/Levenshtein.test.cpp.html">test/aoj/Levenshtein.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<class T>
int Levenshtein(const T& a, const T& b) {
vector<vector<int>> dp(a.size() + 1, vector<int>(b.size() + 1, INT_MAX));
	for (size_t i = 0; i <= a.size(); i++) dp[i][0] = i;
	for (size_t i = 0; i <= b.size(); i++) dp[0][i] = i;
	for (size_t i = 0; i < a.size(); i++) {
		for (size_t j = 0; j < b.size(); j++) {
			dp[i+1][j+1] = min({dp[i+1][j] + 1, dp[i][j+1] + 1, dp[i][j] + (a[i] != b[j])});
		}
	}
	return dp[a.size()][b.size()];
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "dp/Levenshtein.cpp"
template<class T>
int Levenshtein(const T& a, const T& b) {
vector<vector<int>> dp(a.size() + 1, vector<int>(b.size() + 1, INT_MAX));
	for (size_t i = 0; i <= a.size(); i++) dp[i][0] = i;
	for (size_t i = 0; i <= b.size(); i++) dp[0][i] = i;
	for (size_t i = 0; i < a.size(); i++) {
		for (size_t j = 0; j < b.size(); j++) {
			dp[i+1][j+1] = min({dp[i+1][j] + 1, dp[i][j+1] + 1, dp[i][j] + (a[i] != b[j])});
		}
	}
	return dp[a.size()][b.size()];
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

