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
    - Last commit date: 2020-01-19 20:47:29+09:00




## Depends on

* :heavy_check_mark: <a href="../for_include/make_graph.cpp.html">for_include/make_graph.cpp</a>
* :heavy_check_mark: <a href="../helper/tag.cpp.html">helper/tag.cpp</a>
* :heavy_check_mark: <a href="../template/UnWeightedGraph.cpp.html">template/UnWeightedGraph.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/is_Biparite.test.cpp.html">test/aoj/is_Biparite.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
namespace is_biparite_n {
#include "../template/UnWeightedGraph.cpp"
#include "../helper/tag.cpp"
template<class T> using graph = UnWeightedGraph<T>;
#include "../for_include/make_graph.cpp"
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
using is_biparite_n::is_Biparite;
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/is_Biparite.cpp"
namespace is_biparite_n {
#line 1 "graph/../template/UnWeightedGraph.cpp"
template<class VertexType = long long>
struct UnWeightedGraph {
	template<class T> static enable_if_t<is_integral<T>::value, size_t>  index(T x) {return x;}
	template<class T> static enable_if_t<is_integral<T>::value, T>     restore(T x) {return x;}
	template<class T> static enable_if_t<!is_integral<T>::value, size_t> index(T x) {return x.index();}
	template<class T> static enable_if_t<!is_integral<T>::value, T>    restore(T x) {return x.restore();}
	struct graph_tag {};
	vector<vector<size_t>> edge;
	UnWeightedGraph(size_t N) : edge(N) {}
	template<class T, class U> void add_edge(T from, U to) {
		edge[index(from)].push_back(index(to));
	}
	size_t size() const {
		return edge.size();
	}
	void clear() {
		edge.clear();
	}
	using vertex_type = VertexType;
};#line 1 "graph/../helper/tag.cpp"
template <class T>
class has_graph_tag {
	template <class U, typename O = typename U::graph_tag> static constexpr std::true_type check(int);
	template <class U> static constexpr std::false_type check(long);
public:
	static constexpr bool value = decltype(check<T>(0))::value;
};
template <class T> constexpr bool has_graph_tag_v = has_graph_tag<T>::value;#line 4 "graph/is_Biparite.cpp"
template<class T> using graph = UnWeightedGraph<T>;
#line 1 "graph/../for_include/make_graph.cpp"
template<class T = long long>
graph<T> make_graph(size_t N) {
	return move(graph<T>(N));
}#line 6 "graph/is_Biparite.cpp"
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
using is_biparite_n::is_Biparite;
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

