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


# :heavy_check_mark: test/aoj/Levenshtein.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/Levenshtein.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-14 12:20:47+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_1_E">https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_1_E</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/dp/Levenshtein.cpp.html">dp/Levenshtein.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp

#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_1_E"

#include<bits/stdc++.h>

using namespace std;

#include "../../dp/Levenshtein.cpp"

int main() {
	string a, b;
	cin >> a >> b;
	cout << Levenshtein(a, b) << endl;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj/Levenshtein.test.cpp"

#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_1_E"

#include<bits/stdc++.h>

using namespace std;

#line 1 "test/aoj/../../dp/Levenshtein.cpp"
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
}#line 9 "test/aoj/Levenshtein.test.cpp"

int main() {
	string a, b;
	cin >> a >> b;
	cout << Levenshtein(a, b) << endl;
}
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

