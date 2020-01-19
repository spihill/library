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
    - Last commit date: 2020-01-19 14:01:04+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2370">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2370</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/dp/PartialSum_limited.cpp.html">dp/PartialSum_limited.cpp</a>
* :heavy_check_mark: <a href="../../../library/for_include/make_graph.cpp.html">for_include/make_graph.cpp</a>
* :heavy_check_mark: <a href="../../../library/graph/is_Biparite.cpp.html">graph/is_Biparite.cpp</a>
* :heavy_check_mark: <a href="../../../library/helper/tag.cpp.html">helper/tag.cpp</a>
* :heavy_check_mark: <a href="../../../library/template/UnWeightedGraph.cpp.html">template/UnWeightedGraph.cpp</a>


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
	auto B = make_graph(V);
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
#line 1 "test/aoj/../../graph/../template/UnWeightedGraph.cpp"
template<class VertexType = long long>
struct UnWeightedGraph {
	template<class T> static enable_if_t<is_integral<T>::value, size_t>  index(T x) {return x;}
	template<class T> static enable_if_t<is_integral<T>::value, T>     restore(T x) {return x;}
	template<class T> static enable_if_t<!is_integral<T>::value, size_t> index(T x) {return x.index();}
	template<class T> static enable_if_t<!is_integral<T>::value, T>    restore(T x) {return x.restore();}
	struct graph_tag {};
	vector<vector<size_t>> edge;
	UnWeightedGraph(size_t N) : edge(N) {}
	template<class T, class U = T> void add_edge(T from, U to) {
		edge[index(from)].push_back(index(to));
	}
	size_t size() const {
		return edge.size();
	}
	using vertex_type = VertexType;
};#line 1 "test/aoj/../../graph/../helper/tag.cpp"
template <class T>
class has_graph_tag {
	template <class U, typename O = typename U::graph_tag> static constexpr std::true_type check(int);
	template <class U> static constexpr std::false_type check(long);
public:
	static constexpr bool value = decltype(check<T>(0))::value;
};
template <class T> constexpr bool has_graph_tag_v = has_graph_tag<T>::value;#line 4 "test/aoj/../../graph/is_Biparite.cpp"
template<class T> using graph = UnWeightedGraph<T>;
#line 1 "test/aoj/../../graph/../for_include/make_graph.cpp"
template<class T = long long>
graph<T> make_graph(size_t N) {
	return move(graph<T>(N));
}#line 6 "test/aoj/../../graph/is_Biparite.cpp"
template<class T>
enable_if_t<has_graph_tag_v<graph<T>>, vector<pair<int, int>>> is_Biparite(graph<T>& G) {
	const int V = G.size();
	vector<pair<int, int>> res;
	auto& e = G.edge;
	vector<char> color(V, -1);
	int count[2] = {0, 0};
	auto dfs = [&] (auto f, int v, int c) {
		if (color[v] == c) return true;
		if (color[v] != -1) return false;
		color[v] = c;
		count[c]++;
		for (auto& x: e[v]) {
			if (!f(f, x, 1 - c)) return false;
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
template<class T = long long> using graph = is_biparite_n::graph<T>;
using is_biparite_n::make_graph;
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
	auto B = make_graph(V);
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

