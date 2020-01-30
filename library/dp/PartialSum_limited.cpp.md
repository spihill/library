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


# :heavy_check_mark: dp/PartialSum_limited.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#95687afb5d9a2a9fa39038f991640b0c">dp</a>
* <a href="{{ site.github.repository_url }}/blob/master/dp/PartialSum_limited.cpp">View this file on GitHub</a>
    - Last commit date: 2019-10-06 01:32:13+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/is_Biparite.test.cpp.html">test/aoj/is_Biparite.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
vector<int> PartialSum_limited(const vector<int>& w, const vector<int>& c, int w_max) {
	assert(w.size() == c.size());
	vector<int> dp(w_max + 1, -1);
	dp[0] = 0;
	for (int i = 0; i < (int) w.size(); i++) {
		for (int j = 0; j < (int) dp.size(); j++) {
			if (w[i] >= 0) {
				if (dp[j] >= 0) {
					dp[j] = c[i];
				} else if (j < w[i] || dp[j-w[i]] <= 0) {
					dp[j] = -1;
				} else {
					dp[j] = dp[j-w[i]] - 1;
				}
			}
		}
	}
	return dp;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "dp/PartialSum_limited.cpp"
vector<int> PartialSum_limited(const vector<int>& w, const vector<int>& c, int w_max) {
	assert(w.size() == c.size());
	vector<int> dp(w_max + 1, -1);
	dp[0] = 0;
	for (int i = 0; i < (int) w.size(); i++) {
		for (int j = 0; j < (int) dp.size(); j++) {
			if (w[i] >= 0) {
				if (dp[j] >= 0) {
					dp[j] = c[i];
				} else if (j < w[i] || dp[j-w[i]] <= 0) {
					dp[j] = -1;
				} else {
					dp[j] = dp[j-w[i]] - 1;
				}
			}
		}
	}
	return dp;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

