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
    - Last commit date: 2020-01-17 02:16:41+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/datastructure/FibHeap.cpp.html">フィボナッチヒープ (01)</a>
* :heavy_check_mark: <a href="../../../library/for_include/compare_operators.cpp.html">for_include/compare_operators.cpp</a>
* :heavy_check_mark: <a href="../../../library/for_include/vec.cpp.html">for_include/vec.cpp</a>
* :heavy_check_mark: <a href="../../../library/graph/develop/test/FibDijkstra.cpp.html">graph/develop/test/FibDijkstra.cpp</a>
* :heavy_check_mark: <a href="../../../library/snippet/WeightedEdge.cpp.html">snippet/WeightedEdge.cpp</a>
* :heavy_check_mark: <a href="../../../library/snippet/WeightedGraph.cpp.html">snippet/WeightedGraph.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja"

#include <bits/stdc++.h>

using namespace std;

#include "../../graph/develop/test/FibDijkstra.cpp"

int main() {
	int V, E, S;
	scanf("%d%d%d", &V, &E, &S);
	graph<int> D(V);
	for (int i = 0; i < E; i++) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		D.add_edge(a, b, c);
	}
	FibDijkstra(D, S, INT_MAX);
	for (int i = 0; i < V; i++) {
		if (D.dist[i] == INT_MAX) cout << "INF" << endl;
		else cout << D.dist[i] << endl;
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

#line 1 "test/aoj/../../graph/develop/test/../../../datastructure/FibHeap.cpp"
/**
 * @title フィボナッチヒープ
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
	np increase_key(np x, Key k) {
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
	template<class... Args> np increase_key_emplace(np x, Args... args) {
		return increase_key(move(x), move(Key(args...)));
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
};#line 2 "test/aoj/../../graph/develop/test/FibDijkstra.cpp"
namespace fibdijkstra_n {
#line 1 "test/aoj/../../graph/develop/test/../../../snippet/WeightedEdge.cpp"
template<class W>
struct Edge {
	using type = Edge<W>;
	int to;
	W w;
	template<class... Args> Edge(int t, Args... args) : to(t), w(args...) {}
	inline bool operator<(const Edge& rhs) const { return w < rhs.w; }
#line 1 "test/aoj/../../graph/develop/test/../../../snippet/../for_include/compare_operators.cpp"
	inline bool operator>(const type& rhs) const { return rhs < *this; }
	inline bool operator>=(const type& rhs) const { return !(*this < rhs); }
	inline bool operator<=(const type& rhs) const { return !(rhs < *this); }
	inline bool operator==(const type& rhs) const { return !(*this < rhs) && !(rhs < *this); }
	inline bool operator!=(const type& rhs) const { return (*this < rhs) || (rhs < *this); }#line 9 "test/aoj/../../graph/develop/test/../../../snippet/WeightedEdge.cpp"
};
template<class W>
struct Edges : private vector<vector<Edge<W>>> {
	using type = vector<vector<Edge<W>>>;
	template<class... Args> Edges(Args... args) : type(args...) {}
	template<class... Args> void add_edge(int u, int v, Args... args) {
		(*this)[u].emplace_back(v, args...);
	}
#line 1 "test/aoj/../../graph/develop/test/../../../snippet/../for_include/vec.cpp"
	using type::begin; using type::end; using type::rbegin; using type::rend;
	using type::cbegin; using type::cend; using type::crbegin; using type::crend;
	using type::size; using type::operator[]; using type::at; using type::back; using type::front;
	using type::reserve; using type::resize; using type::assign; using type::shrink_to_fit;
	using type::clear; using type::erase; using type::insert; using type::swap; 
	using type::push_back; using type::pop_back; using type::emplace_back; using type::empty;
	using typename vector<typename type::value_type, allocator<typename type::value_type>>::iterator;#line 18 "test/aoj/../../graph/develop/test/../../../snippet/WeightedEdge.cpp"
};#line 2 "test/aoj/../../graph/develop/test/../../../snippet/WeightedGraph.cpp"
template<class W>
struct Graph {
	const int sz;
	Edges<W> e;
	Graph(int n) : sz(n), e(sz) {}
	template<class... Args> void add_edge(int u, int v, Args... args) {
		e.add_edge(u, v, args...);
	}
	int size() {
		return sz;
	}
};#line 4 "test/aoj/../../graph/develop/test/FibDijkstra.cpp"
template<class W, class T = W>
struct Graph_D : public Graph<W> {
	vector<T> dist;
	Graph_D(int n) : Graph<W>(n), dist(n) {}
};
template<class W, class T>
void FibDijkstra(Graph_D<W, T>& g, int start, T INF_COST) {
	auto& dist = g.dist;
	auto& e = g.e;
	for (auto& ww : dist) ww = INF_COST;
	using Q_T = pair<T, int>;
	using heap = FibHeap<Q_T, greater<>>;
	heap q;
	vector<typename heap::np> node(g.size(), nullptr);
	q.emplace(0, start); dist[start] = 0;
	while (!q.empty()) {
		auto a = q.top(); q.pop();
		for (auto& p : e[a.second]) {
			if (p.w == INF_COST) continue;
			W w = dist[a.second] + p.w;
			if (w < dist[p.to]) {
				dist[p.to] = w;
				if (!node[p.to]) node[p.to] = q.emplace(w, p.to);
				q.increase_key_emplace(node[p.to], w, p.to);
			}
		}
	}
}
}
using fibdijkstra_n::FibDijkstra;
template<class T, class U = T> using graph = fibdijkstra_n::Graph_D<T, U>;#line 8 "test/aoj/FibHeap_Dijkstra.test.cpp"

int main() {
	int V, E, S;
	scanf("%d%d%d", &V, &E, &S);
	graph<int> D(V);
	for (int i = 0; i < E; i++) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		D.add_edge(a, b, c);
	}
	FibDijkstra(D, S, INT_MAX);
	for (int i = 0; i < V; i++) {
		if (D.dist[i] == INT_MAX) cout << "INF" << endl;
		else cout << D.dist[i] << endl;
	}
}
```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

