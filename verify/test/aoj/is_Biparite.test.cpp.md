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
    - Last commit date: 2020-01-31 13:16:32+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2370">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2370</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/dp/PartialSum_limited.cpp.html">dp/PartialSum_limited.cpp</a>
* :heavy_check_mark: <a href="../../../library/for_include/has_graph_tag.cpp.html">for_include/has_graph_tag.cpp</a>
* :heavy_check_mark: <a href="../../../library/graph/is_Biparite.cpp.html">graph/is_Biparite.cpp</a>
* :heavy_check_mark: <a href="../../../library/template/Graph.cpp.html">template/Graph.cpp</a>
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
#include "../../template/UnWeightedGraph.cpp"

int main() {
	int V, E;
	cin >> V >> E;
	auto G = make_unweighted_graph(V); 
	for (int i = 0; i < E; i++) {
		int a, b; cin >> a >> b; a--; b--;
		G.add_edge(a, b);
		G.add_edge(b, a);
	}

	auto res = is_Biparite(G);
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
#line 1 "test/aoj/../../graph/../for_include/has_graph_tag.cpp"
template <class T>
class has_graph_tag {
	template <class U> static constexpr std::true_type check(typename U::graph_tag*);
	template <class U> static constexpr std::false_type check(...);
public:
	static constexpr bool value = decltype(check<T>(nullptr))::value;
};
template <class T> constexpr bool has_graph_tag_v = has_graph_tag<T>::value;
#line 3 "test/aoj/../../graph/is_Biparite.cpp"
template<class Graph>
enable_if_t<has_graph_tag_v<Graph>, vector<pair<int, int>>> is_Biparite(Graph& G) {
	const int V = G.size();
	vector<pair<int, int>> res;
	auto& e = G.e;
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
using is_biparite_n::is_Biparite;
#line 1 "test/aoj/../../dp/PartialSum_limited.cpp"
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
#line 1 "test/aoj/../../template/UnWeightedGraph.cpp"
namespace unweighted_graph_n {
#line 1 "test/aoj/../../template/Graph.cpp"
template<class EDGE, class VERTEX>
struct Graph {
	using u32 = uint_fast32_t;
	using i32 = int_fast32_t;
	using u64 = uint_fast64_t;
	struct graph_tag {};
	const u32 n;
	vector<vector<EDGE>> e;
	vector<VERTEX> v;
	vector<u64> idx;
	Graph(u32 N) : n(N), e(n), v(n) {}
	template<class...  Args> void add_edge(u32 from, u32 to, Args... args) {
		idx.push_back((static_cast<u64>(from) << 32) | e[from].size());
		e[from].emplace_back(to, args...);
	}
	u32 size() const {return n;}
	using EDGE_TYPE = EDGE;
	using VERTEX_TYPE = VERTEX;
};
#line 3 "test/aoj/../../template/UnWeightedGraph.cpp"
using u32 = uint_fast32_t;
struct Vertex {};
struct Edge {
	u32 to;
	Edge(u32 x) : to(x) {}
};
using UnWeightedGraph = Graph<Edge, Vertex>;
UnWeightedGraph make_unweighted_graph(u32 N) {
	return UnWeightedGraph(N);
}
}
using unweighted_graph_n::UnWeightedGraph;
using unweighted_graph_n::make_unweighted_graph;
#line 9 "test/aoj/is_Biparite.test.cpp"

int main() {
	int V, E;
	cin >> V >> E;
	auto G = make_unweighted_graph(V); 
	for (int i = 0; i < E; i++) {
		int a, b; cin >> a >> b; a--; b--;
		G.add_edge(a, b);
		G.add_edge(b, a);
	}

	auto res = is_Biparite(G);
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

