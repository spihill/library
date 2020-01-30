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


# :heavy_check_mark: test/aoj/FibPrim.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/FibPrim.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-27 18:45:58+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A&lang=jp">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A&lang=jp</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/datastructure/FibHeapMap.cpp.html">フィボナッチヒープ (Key and Value)</a>
* :heavy_check_mark: <a href="../../../library/for_include/has_weighted_graph_tag.cpp.html">for_include/has_weighted_graph_tag.cpp</a>
* :heavy_check_mark: <a href="../../../library/graph/FibPrim.cpp.html">graph/FibPrim.cpp</a>
* :heavy_check_mark: <a href="../../../library/template/Graph.cpp.html">template/Graph.cpp</a>
* :heavy_check_mark: <a href="../../../library/template/WeightedGraph.cpp.html">template/WeightedGraph.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A&lang=jp"

#include<bits/stdc++.h>

using namespace std;

#include "../../graph/FibPrim.cpp"
#include "../../template/WeightedGraph.cpp"

int main() {
	int V, E;
	cin >> V >> E;
	auto P = make_weighted_graph(V);
	for (int i = 0; i < E; i++) {
		int s, t, w;
		cin >> s >> t >> w;
		P.add_edge(s, t, w);
		P.add_edge(t, s, w);
	}
	cout << FibPrim(P) << endl;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj/FibPrim.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A&lang=jp"

#include<bits/stdc++.h>

using namespace std;

#line 1 "test/aoj/../../graph/FibPrim.cpp"
namespace fibprim_n {
#line 1 "test/aoj/../../graph/../datastructure/FibHeapMap.cpp"
/**
 * @title フィボナッチヒープ (Key and Value)
 * @brief std::priority_queue に合わせて、Compare に less<Key> を渡すと top が最大値になります。比較に使う Key と 使わない Val を保持します。
 */
template<class Key, class Val, class Compare = less<Key>>
struct FibHeapMap {
	struct node; using np = node*;
	using u32 = uint_fast32_t;
	struct node {
		pair<Key, Val> value;
		np left, right;
		np par, child;
		u32 degree;
		bool mark;
		node(pair<Key, Val> v) : value(move(v)), left(this), right(this), par(nullptr), child(nullptr), degree(0), mark(false) {}
		node() : value(), left(this), right(this), par(nullptr), child(nullptr), degree(0), mark(false) {}
		const Key& get_key() const {
			return value.first;
		}
		const Val& get_value() const {
			return value.second;
		}
	};
	np maximum;
	np roots;
	u32 n;
	FibHeapMap() : maximum(nullptr), n(0) {
		roots = new node();
	}
	np push(Key k, Val v) { return push(pair<Key, Val>(move(k), move(v)));}
	np push(pair<Key, Val> value) {
		n++;
		return push(new node(move(value)));
	}
	inline np push(np x) {
		insert_node_to_roots(x);
		if (!maximum) maximum = x;
		update_maximum(x);
		return x;
	}
	np pop() {
		np z = maximum;
		if (z) {
			if (np x = z->child) do {
				np next = x->right;
				insert_node_to_roots(x);
				x = next;
			} while (x != z->child);
			cut_par(z); cut_list_sub(z);
			if (roots == roots->right) maximum = nullptr;
			else Consolidate();
			n--;
		}
		return z;
	}
	const pair<Key, Val>& top() const {
		return maximum->value;
	}
	void check() const {
		bool f = roots == roots->right;
		for (np x = roots->right; x != roots; x = x->right) {
			assert(!x->par);
			f = f || x == maximum;
		}
		assert(f);
		check_dfs(roots);
	}
	u32 size() const {return n;}
	np prioritize(np x, Key k) {
		assert(!compare(k, x->value.first));
		x->value.first = move(k);
		np y = x->par;
		if (y && compare(y->value.first, x->value.first)) {
			cut(x, y);
			cascading_cut(y);
		}
		update_maximum(x);
		return x;
	}
	bool empty() const {
		return n == 0;
	}
private:
	inline bool compare(const Key& x, const Key& y) const {
		return Compare()(x, y);
	}
	void cut(np child, np par) {
		par->degree--;
		if (par->child == child) {
			if (child->right == child) par->child = nullptr;
			else par->child = child->right;
		}
		cut_list_sub(child);
		insert_node_to_roots(child);
		child->mark = false;
	}
	void cascading_cut(np y) {
		if (np z = y->par) {
			if (y->mark) {
				cut(y, z);
				cascading_cut(z);
			}
			else y->mark = true;
		}
	}
	int check_dfs(np n) const {
		if (!n) return 0;
		if (n != roots) assert(!compare(maximum->value.first, n->value.first));
		vector<np> ls = make_list_vector(n);
		int d = ls.size();
		for (auto x : ls) {
			assert(x->left->right == x);
			assert(x->degree == u32(check_dfs(x->child)));
			if (x->child) assert(x->child->par == x);
		}
		return d;
	}
	inline void cut_par(np x) {
		if (!x->par) return;
		x->par->degree--;
		if (x->par->child == x) {
			if (x->right == x) x->par->child = nullptr;
			else x->par->child = x->right;
		}
	}
	inline void insert_node_to_roots(np x) {
		x->par = nullptr;
		x->left = roots;
		x->right = roots->right;
		roots->right = roots->right->left = x;
	}
	inline void insert_node_to_list(np& list, np n) {
		if (!list) list = n->left = n->right = n;
		else {
			n->left = list;
			n->right = list->right;
			list->right = list->right->left = n;
		}
	}
	inline void update_maximum(np x) {
		if (compare(maximum->value.first, x->value.first)) maximum = x;
	}
	inline void cut_list_sub(np x) {
		x->left->right = x->right;
		x->right->left = x->left;
	}
	inline vector<np> make_list_vector(np n) const {
		if (!n) return move(vector<np>(0));
		vector<np> res(1, n);
		for (np nn = n->right; nn != n; nn = nn->right) {
			res.push_back(nn);
		}
		return move(res);
	}
	inline void Consolidate() {
		constexpr double phi = 1.6180339887498948482072100296669248109537875279784;
		int sz = 2;
		for (double p = phi; p < n; p *= phi, sz++);
		vector<np> A(sz, nullptr);
		for (np x = roots->right; x != roots;) {
			np next = x->right;
			u32 d = x->degree;
			while (np y = A[d]) {
				if (compare(x->value.first, y->value.first)) swap(x, y);
				Link(y, x);
				A[d] = nullptr;
				d++;
			}
			A[d] = x;
			x = next;
		}
		maximum = roots->right;
		for (np x = roots->right->right; x != roots; x = x->right) update_maximum(x);
	}
	inline void Link(np child, np par) {
		cut_list_sub(child);
		insert_node_to_list(par->child, child);
		child->par = par;
		par->degree++;
		child->mark = false;
	}
};
#line 1 "test/aoj/../../graph/../for_include/has_weighted_graph_tag.cpp"
template <class T>
class has_weighted_graph_tag {
	template <class U> static constexpr std::true_type check(typename U::weighted_graph_tag*);
	template <class U> static constexpr std::false_type check(...);
public:
	static constexpr bool value = decltype(check<T>(nullptr))::value;
};
template <class T> constexpr bool has_weighted_graph_tag_v = has_weighted_graph_tag<T>::value;
#line 4 "test/aoj/../../graph/FibPrim.cpp"
using u32 = uint_fast32_t;
template<class Graph, class WEIGHT = typename Graph::WEIGHT_TYPE>
enable_if_t<has_weighted_graph_tag_v<Graph>, WEIGHT> FibPrim(Graph& G, u32 start = 0, const WEIGHT INF_COST = numeric_limits<WEIGHT>::max()) {
	auto& e = G.e;
	WEIGHT res = 0;
	vector<char> used(G.size(), 0);
	using heap = FibHeapMap<WEIGHT, u32, greater<>>;
	heap q;
	vector<typename heap::np> node(G.size(), nullptr);
	q.push(0, start);
	while (!q.empty()) {
		auto p = q.top(); q.pop();
		if (used[p.second]) continue;
		used[p.second] = true;
		res += p.first;
		for (auto& x : e[p.second]) {
			if (x.weight == INF_COST) continue;
			q.push(x.weight, x.to);
			if (!used[x.to]) {
				if (!node[x.to]) node[x.to] = q.push(x.weight, x.to);
				if (x.weight< node[x.to]->get_key()) q.prioritize(node[x.to], x.weight);
			}
		}
	}
	return res;
}
}
using fibprim_n::FibPrim;
// template<class W> using graph = fibprim_n::Edges<W>;
// namespace prim_n {
// #include "../for_include/has_weighted_graph_tag.cpp"
// template<class Graph, class WEIGHT = typename Graph::WEIGHT_TYPE>
// enable_if_t<has_weighted_graph_tag_v<Graph>, WEIGHT> Prim(Graph& G) {
// 	WEIGHT res = 0;
// 	vector<char> used(G.size(), 0);
// 	priority_queue<pair<WEIGHT, int>, vector<pair<WEIGHT, int>>, greater<>> q;
// 	q.emplace(0, 0);
// 	while (!q.empty()) {
// 		auto p = q.top(); q.pop();
// 		if (used[p.second] != 0) continue;
// 		used[p.second] = 1;
// 		res += p.first;
// 		for (auto& x : G.e[p.second]) {
// 			q.emplace(x.weight, x.to);
// 		}
// 	}
// 	return res;
// }
// }
// using prim_n::Prim;
#line 1 "test/aoj/../../template/WeightedGraph.cpp"
namespace weighted_graph_n{
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
#line 3 "test/aoj/../../template/WeightedGraph.cpp"
using u32 = uint_fast32_t;
using i64 = int_fast64_t;
struct Vertex {};
template<class WEIGHT>
struct Edge {
	u32 to;
	WEIGHT weight;
	Edge(u32 x, WEIGHT w) : to(x), weight(w) {}
};
template<class WEIGHT>
struct WeightedGraph : public Graph<Edge<WEIGHT>, Vertex> {
	struct weighted_graph_tag {};
	WeightedGraph(u32 N) : Graph<Edge<WEIGHT>, Vertex>(N) {}
	using WEIGHT_TYPE = WEIGHT;
};
template<class WEIGHT = i64>
WeightedGraph<WEIGHT> make_weighted_graph(u32 N) {
	return WeightedGraph<WEIGHT>(N);
}
} // weighted_graph_n
using weighted_graph_n::WeightedGraph;
using weighted_graph_n::make_weighted_graph;
#line 9 "test/aoj/FibPrim.test.cpp"

int main() {
	int V, E;
	cin >> V >> E;
	auto P = make_weighted_graph(V);
	for (int i = 0; i < E; i++) {
		int s, t, w;
		cin >> s >> t >> w;
		P.add_edge(s, t, w);
		P.add_edge(t, s, w);
	}
	cout << FibPrim(P) << endl;
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

