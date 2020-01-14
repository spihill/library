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


# :heavy_check_mark: graph/is_Biparite.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/is_Biparite.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-15 01:52:18+09:00




## Depends on

* :heavy_check_mark: <a href="../for_include/vec.cpp.html">for_include/vec.cpp</a>
* :heavy_check_mark: <a href="../snippet/Edge.cpp.html">snippet/Edge.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/is_Biparite.test.cpp.html">test/aoj/is_Biparite.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
namespace is_biparite_n {
#include "../snippet/Edge.cpp"
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
using is_biparite_n::is_Biparite;
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/is_Biparite.cpp"
namespace is_biparite_n {
#line 1 "graph/../snippet/Edge.cpp"
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
#line 1 "graph/../snippet/../for_include/vec.cpp"
	using type::begin; using type::end; using type::rbegin; using type::rend;
	using type::cbegin; using type::cend; using type::crbegin; using type::crend;
	using type::size; using type::operator[]; using type::at; using type::back; using type::front;
	using type::reserve; using type::resize; using type::assign; using type::shrink_to_fit;
	using type::clear; using type::erase; using type::insert; using type::swap; 
	using type::push_back; using type::pop_back; using type::emplace_back; using type::empty;
	using typename vector<typename type::value_type, allocator<typename type::value_type>>::iterator;#line 12 "graph/../snippet/Edge.cpp"
};#line 3 "graph/is_Biparite.cpp"
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
using is_biparite_n::is_Biparite;
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

