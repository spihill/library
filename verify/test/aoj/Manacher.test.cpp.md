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


# :heavy_check_mark: test/aoj/Manacher.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/Manacher.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-17 23:28:42+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2934">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2934</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/string/Manacher.cpp.html">string/Manacher.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2934"

#include<bits/stdc++.h>

using namespace std;

#include "../../string/Manacher.cpp"

int solve() {
	int N; cin >> N;
	string s;
	vector<int> ss;

	for (int i = 0; i < N; i++) {
		char c; cin >> c;
		s += c; s += '$';
		ss.push_back(c);
		ss.push_back('$');
	}
	s.pop_back();
	ss.pop_back();
	assert(s.size() == ss.size());
	auto mn = manacher(s);
	auto mn2 = manacher(ss);
	for (size_t i = 0; i < mn.size(); i++) {
		assert(mn[i] == mn2[i]);
	}
	for (int i = 2; i < N * 2; i += 2) {
		int p;
		for (p = i; mn[p] == p + 1; p += mn[p] - 1);
		if (p + mn[p] == N * 2 - 1) return i / 2 + 1;
	}
	assert(0);
}

int main() {
	cout << solve() << endl;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj/Manacher.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2934"

#include<bits/stdc++.h>

using namespace std;

#line 1 "test/aoj/../../string/Manacher.cpp"
template<class T>
vector<int> manacher(const vector<T>& s) {
	const int n = s.size();
	vector<int> res(n);
	int pos = 0, len = 0;
	while (pos < n) {
		while (pos - len >= 0 && pos + len < n && s[pos - len] == s[pos + len]) len++;
		res[pos] = len;
		int i;
		for (i = 1; pos - i >= 0 && pos + i < n && i + res[pos-i] < len; i++) res[pos+i] = res[pos-i];
		pos += i; len -= i;
	}
	return res;
}
vector<int> manacher(const string& s) {
	return manacher(vector<char>(s.begin(), s.end()));
}#line 8 "test/aoj/Manacher.test.cpp"

int solve() {
	int N; cin >> N;
	string s;
	vector<int> ss;

	for (int i = 0; i < N; i++) {
		char c; cin >> c;
		s += c; s += '$';
		ss.push_back(c);
		ss.push_back('$');
	}
	s.pop_back();
	ss.pop_back();
	assert(s.size() == ss.size());
	auto mn = manacher(s);
	auto mn2 = manacher(ss);
	for (size_t i = 0; i < mn.size(); i++) {
		assert(mn[i] == mn2[i]);
	}
	for (int i = 2; i < N * 2; i += 2) {
		int p;
		for (p = i; mn[p] == p + 1; p += mn[p] - 1);
		if (p + mn[p] == N * 2 - 1) return i / 2 + 1;
	}
	assert(0);
}

int main() {
	cout << solve() << endl;
}
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

