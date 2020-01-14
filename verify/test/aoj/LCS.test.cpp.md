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


# :heavy_check_mark: test/aoj/LCS.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/LCS.test.cpp">View this file on GitHub</a>
    - Last commit date: 2019-09-20 18:44:08+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_10_C&lang=ja">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_10_C&lang=ja</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/dp/LCS.cpp.html">dp/LCS.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_10_C&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#include "../../dp/LCS.cpp"

int main() {
	int n; cin >> n;
	while (n--) {
		string s, t;
		cin >> s >> t;
		cout << LCS(s, t) << endl;
	}
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj/LCS.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_10_C&lang=ja"

#include<bits/stdc++.h>

using namespace std;

#line 1 "test/aoj/../../dp/LCS.cpp"
template<class T>
int LCS(const T& a, const T& b) {
	vector<vector<int>> dp(a.size() + 1, vector<int>(b.size() + 1));
	for (size_t i = 0; i < a.size(); i++) {
		for (size_t j = 0; j < b.size(); j++) {
			dp[i+1][j+1] = max({dp[i][j+1], dp[i+1][j], dp[i][j]+(a[i]==b[j])});
		}
	}
	return dp[a.size()][b.size()];
}#line 8 "test/aoj/LCS.test.cpp"

int main() {
	int n; cin >> n;
	while (n--) {
		string s, t;
		cin >> s >> t;
		cout << LCS(s, t) << endl;
	}
}
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

