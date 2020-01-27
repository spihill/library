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


# :heavy_check_mark: test/aoj/FibHeap_Dijkstra.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/FibHeap_Dijkstra.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-27 18:45:58+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/datastructure/FibHeap.cpp.html">フィボナッチヒープ (Key)</a>
* :heavy_check_mark: <a href="../../../library/for_include/has_shortest_path_graph_tag.cpp.html">for_include/has_shortest_path_graph_tag.cpp</a>
* :heavy_check_mark: <a href="../../../library/template/Graph.cpp.html">template/Graph.cpp</a>
* :heavy_check_mark: <a href="../../../library/template/ShortestPathGraph.cpp.html">template/ShortestPathGraph.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja"

#include <bits/stdc++.h>

using namespace std;

namespace fibdijkstra_n {
#include "../../datastructure/FibHeap.cpp"
#include "../../for_include/has_shortest_path_graph_tag.cpp"
using u32 = uint_fast32_t;
template<class Graph, class WEIGHT = typename Graph::WEIGHT_TYPE>
enable_if_t<has_shortest_path_graph_tag_v<Graph>> FibDijkstra(Graph& G, u32 start, WEIGHT INF_COST) {
	auto& e = G.e;
	for (u32 i = 0; i < G.size(); i++) {
		G.dist(i) = INF_COST;
		G.valid(i) = false;
	}
	using heap = FibHeap<pair<WEIGHT, u32>, greater<>>;
	heap q;
	vector<typename heap::np> node(G.size(), nullptr);
	q.emplace(0, start); G.dist(start) = 0;
	while (!q.empty()) {
		auto a = q.top(); q.pop();
		for (auto& p : e[a.second]) {
			if (p.weight == INF_COST) continue;
			G.valid(a.second) = 1;
			WEIGHT w = G.dist(a.second) + p.weight;
			if (w < G.dist(p.to)) {
				G.dist(p.to) = w;
				if (!node[p.to]) node[p.to] = q.emplace(w, p.to);
				q.prioritize_emplace(node[p.to], w, p.to);
			}
		}
	}
}
}
using fibdijkstra_n::FibDijkstra;

#include "../../template/ShortestPathGraph.cpp"

int main() {
	int V, E, S;
	scanf("%d%d%d", &V, &E, &S);
	auto D = make_shortest_path_graph(V);
	for (int i = 0; i < E; i++) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		D.add_edge(a, b, c);
	}
	FibDijkstra(D, S, INT_MAX);
	for (int i = 0; i < V; i++) {
		if (D.dist(i) == INT_MAX) cout << "INF" << endl;
		else cout << D.dist(i) << endl;
	}
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj/FibHeap_Dijkstra.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja"

#include <bits/stdc++.h>

using namespace std;

namespace fibdijkstra_n {
#line 1 "test/aoj/../../datastructure/FibHeap.cpp"
/**
 * @title フィボナッチヒープ (Key)
 * @brief std::priority_queue に合わせて、Compare に less<Key> を渡すと top が最大値になります。
 */
template<class Key, class Compare = less<Key>>
struct FibHeap {
	struct node; using np = node*;
	using u32 = uint_fast32_t;
	struct node {
		Key key;
		np left, right;
		np par, child;
		u32 degree;
		bool mark;
		node(Key k) : key(k), left(this), right(this), par(nullptr), child(nullptr), degree(0), mark(false) {}
		node() : key(), left(this), right(this), par(nullptr), child(nullptr), degree(0), mark(false) {}
	};
	np maximum;
	np roots;
	u32 n;
	FibHeap() : maximum(nullptr), n(0) {
		roots = new node();
	}
	np push(Key k) {
		n++;
		return push(new node(move(k)));
	}
	template<class... Args> np emplace(Args... args) {
		return push(move(Key(args...)));
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
	const Key& top() const {
		return maximum->key;
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
		assert(!Compare()(k, x->key));
		x->key = move(k);
		np y = x->par;
		if (y && Compare()(y->key, x->key)) {
			cut(x, y);
			cascading_cut(y);
		}
		update_maximum(x);
		return x;
	}
	template<class... Args> np prioritize_emplace(np x, Args... args) {
		return prioritize(move(x), move(Key(args...)));
	}
	bool empty() const {
		return n == 0;
	}
private:
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
		if (n != roots) assert(!Compare()(maximum->key, n->key));
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
		if (Compare()(maximum->key, x->key)) maximum = x;
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
				if (Compare()(x->key, y->key)) swap(x, y);
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
};#line 1 "test/aoj/../../for_include/has_shortest_path_graph_tag.cpp"
template <class T>
class has_shortest_path_graph_tag {
	template <class U> static constexpr std::true_type check(typename U::shortest_path_graph_tag*);
	template <class U> static constexpr std::false_type check(...);
public:
	static constexpr bool value = decltype(check<T>(nullptr))::value;
};
template <class T> constexpr bool has_shortest_path_graph_tag_v = has_shortest_path_graph_tag<T>::value;#line 10 "test/aoj/FibHeap_Dijkstra.test.cpp"
using u32 = uint_fast32_t;
template<class Graph, class WEIGHT = typename Graph::WEIGHT_TYPE>
enable_if_t<has_shortest_path_graph_tag_v<Graph>> FibDijkstra(Graph& G, u32 start, WEIGHT INF_COST) {
	auto& e = G.e;
	for (u32 i = 0; i < G.size(); i++) {
		G.dist(i) = INF_COST;
		G.valid(i) = false;
	}
	using heap = FibHeap<pair<WEIGHT, u32>, greater<>>;
	heap q;
	vector<typename heap::np> node(G.size(), nullptr);
	q.emplace(0, start); G.dist(start) = 0;
	while (!q.empty()) {
		auto a = q.top(); q.pop();
		for (auto& p : e[a.second]) {
			if (p.weight == INF_COST) continue;
			G.valid(a.second) = 1;
			WEIGHT w = G.dist(a.second) + p.weight;
			if (w < G.dist(p.to)) {
				G.dist(p.to) = w;
				if (!node[p.to]) node[p.to] = q.emplace(w, p.to);
				q.prioritize_emplace(node[p.to], w, p.to);
			}
		}
	}
}
}
using fibdijkstra_n::FibDijkstra;

#line 1 "test/aoj/../../template/ShortestPathGraph.cpp"
namespace shortest_path_graph_n {
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
};#line 3 "test/aoj/../../template/ShortestPathGraph.cpp"
using u32 = uint_fast32_t;
using i64 = int_fast64_t;
template<class WEIGHT>
struct Vertex {
	WEIGHT dist;
	bool valid;
};
template<class WEIGHT>
struct Edge {
	u32 to;
	WEIGHT weight;
	Edge(u32 x, WEIGHT w) : to(x), weight(w) {}
};
template<class WEIGHT>
struct ShortestPathGraph : Graph<Edge<WEIGHT>, Vertex<WEIGHT>> {
	struct shortest_path_graph_tag {};
	ShortestPathGraph(u32 N) : Graph<Edge<WEIGHT>, Vertex<WEIGHT>>(N) {}
	WEIGHT& dist(u32 i) {return this->v[i].dist;}
	bool& valid(u32 i) {return this->v[i].valid;}
	using WEIGHT_TYPE = WEIGHT;
};
template<class WEIGHT = long long>
ShortestPathGraph<WEIGHT> make_shortest_path_graph(u32 N) {
	return move(ShortestPathGraph<WEIGHT>(N));
}
} // shortest_path_graph_n
using shortest_path_graph_n::ShortestPathGraph;
using shortest_path_graph_n::make_shortest_path_graph;
#line 40 "test/aoj/FibHeap_Dijkstra.test.cpp"

int main() {
	int V, E, S;
	scanf("%d%d%d", &V, &E, &S);
	auto D = make_shortest_path_graph(V);
	for (int i = 0; i < E; i++) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		D.add_edge(a, b, c);
	}
	FibDijkstra(D, S, INT_MAX);
	for (int i = 0; i < V; i++) {
		if (D.dist(i) == INT_MAX) cout << "INF" << endl;
		else cout << D.dist(i) << endl;
	}
}
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

