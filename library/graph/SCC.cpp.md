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


# :heavy_check_mark: graph/SCC.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/SCC.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-19 20:47:29+09:00




## Depends on

* :heavy_check_mark: <a href="../for_include/make_graph.cpp.html">for_include/make_graph.cpp</a>
* :heavy_check_mark: <a href="../helper/tag.cpp.html">helper/tag.cpp</a>
* :heavy_check_mark: <a href="../template/UnWeightedGraph.cpp.html">template/UnWeightedGraph.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/yosupo/SCC.test.cpp.html">test/yosupo/SCC.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
namespace scc_n{
#include "../template/UnWeightedGraph.cpp"
#include "../helper/tag.cpp"
template<class T> using super_graph = UnWeightedGraph<T>;
template<class T>
struct SCC : super_graph<T> {
	using super_graph<T>::index;
	using graph = UnWeightedGraph<long long>;
	vector<vector<T>> redge;
	vector<int> comp;
	SCC(size_t N) : super_graph<T>(N), redge(N), comp(N) {}
	template<class Graph>
	SCC(Graph& g_) : SCC(g_.size()) {
		static_assert(has_graph_tag_v<Graph>);
		construct_graph(g_);
	}
	template<class X, class Y> void add_edge(X from, Y to) {
		this->edge[index(from)].push_back(index(to));
		redge[index(to)].push_back(index(from));
	}
	const int& operator[](int i) { return comp[i];}
	void dfs(int n, vector<char>& used, stack<int>& order) {
		if (used[n]) return;
		used[n] = true;
		for (auto x : this->edge[n]) {
			dfs(x, used, order);
		}
		order.emplace(n);
	}
	void rdfs(int n, vector<int>& comp, int group) {
		if (comp[n] != -1) return;
		comp[n] = group;
		for (auto x : redge[n]) rdfs(x, comp, group);
	}
	graph build() {
		const size_t n = this->edge.size();
		stack<int> order;
		vector<char> used(n, 0);
		for (size_t i = 0; i < n; i++) dfs(i, used, order);

		comp = vector<int>(n, -1);
		int group = 0;
		while (order.size()) {
			int i = order.top(); order.pop();
			if (comp[i] == -1) rdfs(i, comp, group++);
		}

		graph res(group);
		for (size_t i = 0; i < n; i++) {
			for (auto& x : this->edge[i]) {
				int s = comp[i], t = comp[x];
				if (s == t) continue;
				res.add_edge(s, t);
			}
		}
		return res;
	}
private:
	template<class Graph>
	void construct_graph(const Graph& G) {
		for (size_t i = 0; i < G.size(); i++) {
			for (auto& x : G.edge[i]) {
				this->edge[i].push_back(x);
				redge[x].push_back(i);
			}
		}
	}
};
template<class T> using graph = SCC<T>;
#include "../for_include/make_graph.cpp"

} // scc_n
template<class T> using graph = scc_n::graph<T>;
using scc_n::make_graph;
using scc_n::SCC;
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/SCC.cpp"
namespace scc_n{
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
template <class T> constexpr bool has_graph_tag_v = has_graph_tag<T>::value;#line 4 "graph/SCC.cpp"
template<class T> using super_graph = UnWeightedGraph<T>;
template<class T>
struct SCC : super_graph<T> {
	using super_graph<T>::index;
	using graph = UnWeightedGraph<long long>;
	vector<vector<T>> redge;
	vector<int> comp;
	SCC(size_t N) : super_graph<T>(N), redge(N), comp(N) {}
	template<class Graph>
	SCC(Graph& g_) : SCC(g_.size()) {
		static_assert(has_graph_tag_v<Graph>);
		construct_graph(g_);
	}
	template<class X, class Y> void add_edge(X from, Y to) {
		this->edge[index(from)].push_back(index(to));
		redge[index(to)].push_back(index(from));
	}
	const int& operator[](int i) { return comp[i];}
	void dfs(int n, vector<char>& used, stack<int>& order) {
		if (used[n]) return;
		used[n] = true;
		for (auto x : this->edge[n]) {
			dfs(x, used, order);
		}
		order.emplace(n);
	}
	void rdfs(int n, vector<int>& comp, int group) {
		if (comp[n] != -1) return;
		comp[n] = group;
		for (auto x : redge[n]) rdfs(x, comp, group);
	}
	graph build() {
		const size_t n = this->edge.size();
		stack<int> order;
		vector<char> used(n, 0);
		for (size_t i = 0; i < n; i++) dfs(i, used, order);

		comp = vector<int>(n, -1);
		int group = 0;
		while (order.size()) {
			int i = order.top(); order.pop();
			if (comp[i] == -1) rdfs(i, comp, group++);
		}

		graph res(group);
		for (size_t i = 0; i < n; i++) {
			for (auto& x : this->edge[i]) {
				int s = comp[i], t = comp[x];
				if (s == t) continue;
				res.add_edge(s, t);
			}
		}
		return res;
	}
private:
	template<class Graph>
	void construct_graph(const Graph& G) {
		for (size_t i = 0; i < G.size(); i++) {
			for (auto& x : G.edge[i]) {
				this->edge[i].push_back(x);
				redge[x].push_back(i);
			}
		}
	}
};
template<class T> using graph = SCC<T>;
#line 1 "graph/../for_include/make_graph.cpp"
template<class T = long long>
graph<T> make_graph(size_t N) {
	return move(graph<T>(N));
}#line 71 "graph/SCC.cpp"

} // scc_n
template<class T> using graph = scc_n::graph<T>;
using scc_n::make_graph;
using scc_n::SCC;
```
{% endraw %}

<a href="../../index.html">Back to top page</a>

