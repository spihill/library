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


# :heavy_check_mark: test/aoj/is_Biparite.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/is_Biparite.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-15 01:52:18+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2370">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2370</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/dp/PartialSum_limited.cpp.html">dp/PartialSum_limited.cpp</a>
* :heavy_check_mark: <a href="../../../library/for_include/vec.cpp.html">for_include/vec.cpp</a>
* :heavy_check_mark: <a href="../../../library/graph/is_Biparite.cpp.html">graph/is_Biparite.cpp</a>
* :heavy_check_mark: <a href="../../../library/snippet/Edge.cpp.html">snippet/Edge.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2370"

#include <bits/stdc++.h>
using namespace std;

#include "../../graph/is_Biparite.cpp"
#include "../../dp/PartialSum_limited.cpp"

int main() {
	int V, E;
	cin >> V >> E;
	graph B(V);
	for (int i = 0; i < E; i++) {
		int a, b; cin >> a >> b; a--; b--;
		B.add_edge(a, b);
		B.add_edge(b, a);
	}
	auto res = is_Biparite(B);
	if (res.size() == 0) {
		cout << -1 << endl;
		return 0;
	}
	map<int, int> m;
	int zero = 0;
	vector<int> w;
	vector<int> cnt;
	for (auto& x: res) {
		int diff = abs(x.first - x.second);
		zero += diff;
		m[diff]++;
	}
	for (auto& x: m) {
		w.push_back(x.first*2);
		cnt.push_back(x.second);
	}
	auto dp = PartialSum_limited(w, cnt, zero * 2 + 1);
	for (int i = 0; i <= zero; i++) {
		if (dp[zero+i] >= 0 || dp[zero-i] >= 0) {
			long long a = V + i;
			long long b = V - i;
			cout << a * b / 4 - E << endl;
			return 0;
		}
	}
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj/is_Biparite.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2370"

#include <bits/stdc++.h>
using namespace std;

#line 1 "test/aoj/../../graph/is_Biparite.cpp"
namespace is_biparite_n {
#line 1 "test/aoj/../../graph/../snippet/Edge.cpp"
struct Edge {
	int to;
	Edge(int t) : to(t) {}
};
struct Edges : private vector<vector<Edge>> {
	using type = vector<vector<Edge>>;
	void add_edge(int u, int v) {
		(*this)[u].emplace_back(v);
	}
	template<class... Args> Edges(Args... args) : vector<vector<Edge>>(args...) {}
#line 1 "test/aoj/../../graph/../snippet/../for_include/vec.cpp"
	using type::begin; using type::end; using type::rbegin; using type::rend;
	using type::cbegin; using type::cend; using type::crbegin; using type::crend;
	using type::size; using type::operator[]; using type::at; using type::back; using type::front;
	using type::reserve; using type::resize; using type::assign; using type::shrink_to_fit;
	using type::clear; using type::erase; using type::insert; using type::swap; 
	using type::push_back; using type::pop_back; using type::emplace_back; using type::empty;
	using typename vector<typename type::value_type, allocator<typename type::value_type>>::iterator;#line 12 "test/aoj/../../graph/../snippet/Edge.cpp"
};#line 3 "test/aoj/../../graph/is_Biparite.cpp"
vector<pair<int, int>> is_Biparite(Edges& e) {
	const int V = e.size();
	vector<pair<int, int>> res;
	vector<char> color(V, -1);
	int count[2] = {0, 0};
	auto dfs = [&] (auto f, int v, int c) {
		if (color[v] == c) return true;
		if (color[v] != -1) return false;
		color[v] = c;
		count[c]++;
		for (auto& x: e[v]) {
			if (!f(f, x.to, 1 - c)) return false;
		}
		return true;
	};
	for (int i = 0; i < V; i++) {
		if (color[i] == -1 && !dfs(dfs, i, 0)) return vector<pair<int, int>>(0);
		if (count[0]) res.emplace_back(count[0], count[1]);
		count[0] = count[1] = 0;
	}
	return res;
}
}
using graph = is_biparite_n::Edges;
using is_biparite_n::is_Biparite;#line 1 "test/aoj/../../dp/PartialSum_limited.cpp"
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
}#line 8 "test/aoj/is_Biparite.test.cpp"

int main() {
	int V, E;
	cin >> V >> E;
	graph B(V);
	for (int i = 0; i < E; i++) {
		int a, b; cin >> a >> b; a--; b--;
		B.add_edge(a, b);
		B.add_edge(b, a);
	}
	auto res = is_Biparite(B);
	if (res.size() == 0) {
		cout << -1 << endl;
		return 0;
	}
	map<int, int> m;
	int zero = 0;
	vector<int> w;
	vector<int> cnt;
	for (auto& x: res) {
		int diff = abs(x.first - x.second);
		zero += diff;
		m[diff]++;
	}
	for (auto& x: m) {
		w.push_back(x.first*2);
		cnt.push_back(x.second);
	}
	auto dp = PartialSum_limited(w, cnt, zero * 2 + 1);
	for (int i = 0; i <= zero; i++) {
		if (dp[zero+i] >= 0 || dp[zero-i] >= 0) {
			long long a = V + i;
			long long b = V - i;
			cout << a * b / 4 - E << endl;
			return 0;
		}
	}
}
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

