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


# :heavy_check_mark: string/Manacher.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#b45cffe084dd3d20d928bee85e7b0f21">string</a>
* <a href="{{ site.github.repository_url }}/blob/master/string/Manacher.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-17 23:28:42+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/Manacher.test.cpp.html">test/aoj/Manacher.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "string/Manacher.cpp"
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
}
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

