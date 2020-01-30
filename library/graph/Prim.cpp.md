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


# :heavy_check_mark: graph/Prim.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/Prim.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-27 18:45:58+09:00




## Depends on

* :heavy_check_mark: <a href="../for_include/has_weighted_graph_tag.cpp.html">for_include/has_weighted_graph_tag.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/Prim.test.cpp.html">test/aoj/Prim.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/Prim_2.test.cpp.html">test/aoj/Prim_2.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
namespace prim_n {
#include "../for_include/has_weighted_graph_tag.cpp"
template<class Graph, class WEIGHT = typename Graph::WEIGHT_TYPE>
enable_if_t<has_weighted_graph_tag_v<Graph>, WEIGHT> Prim(Graph& G) {
	WEIGHT res = 0;
	vector<char> used(G.size(), 0);
	priority_queue<pair<WEIGHT, int>, vector<pair<WEIGHT, int>>, greater<>> q;
	q.emplace(0, 0);
	while (!q.empty()) {
		auto p = q.top(); q.pop();
		if (used[p.second] != 0) continue;
		used[p.second] = 1;
		res += p.first;
		for (auto& x : G.e[p.second]) {
			q.emplace(x.weight, x.to);
		}
	}
	return res;
}
}
using prim_n::Prim;
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/Prim.cpp"
namespace prim_n {
#line 1 "graph/../for_include/has_weighted_graph_tag.cpp"
template <class T>
class has_weighted_graph_tag {
	template <class U> static constexpr std::true_type check(typename U::weighted_graph_tag*);
	template <class U> static constexpr std::false_type check(...);
public:
	static constexpr bool value = decltype(check<T>(nullptr))::value;
};
template <class T> constexpr bool has_weighted_graph_tag_v = has_weighted_graph_tag<T>::value;
#line 3 "graph/Prim.cpp"
template<class Graph, class WEIGHT = typename Graph::WEIGHT_TYPE>
enable_if_t<has_weighted_graph_tag_v<Graph>, WEIGHT> Prim(Graph& G) {
	WEIGHT res = 0;
	vector<char> used(G.size(), 0);
	priority_queue<pair<WEIGHT, int>, vector<pair<WEIGHT, int>>, greater<>> q;
	q.emplace(0, 0);
	while (!q.empty()) {
		auto p = q.top(); q.pop();
		if (used[p.second] != 0) continue;
		used[p.second] = 1;
		res += p.first;
		for (auto& x : G.e[p.second]) {
			q.emplace(x.weight, x.to);
		}
	}
	return res;
}
}
using prim_n::Prim;

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

