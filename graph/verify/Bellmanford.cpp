#include<bits/stdc++.h>

using namespace std;

using bellman_cost = long long;
template<class V, class E>
struct Graph
{
	int sz;
	vector<V> v;
	vector<vector<E>> e;
	vector<E> edges;
	Graph(int n) : sz(n), v(n), e(n) {}
	template<class... Args>
	inline void assign_vertex(int pos, Args... args) {
		v[pos] = V(args...);
	}
	// from, to, cost
	template<class... Args>
	inline void add_edge(int pos, Args... args) {
		e[pos].emplace_back(args...);
		edges.emplace_back(pos, args...);
	}
	inline int size() {
		return sz;
	}
};

template<class T>
struct Vertex
{
	T cost;
	bool valid = false; // 到達不能または無限にコストが減るときfalse
	Vertex(T v1) : cost(v1) {}
	Vertex() {}
};
using vertex = Vertex<bellman_cost>;

template<class T>
struct Edge
{
	int from;
	int to;
	T cost;
	Edge(int t, T c) : to(t), cost(c) {}
	Edge(int t, int u, T c) : from(t), to(u), cost(c) {}
	Edge() {}
};
using edge = Edge<bellman_cost>;
using graph = Graph<vertex, edge>;

struct Bellmanford : public graph {
	Bellmanford(int n) : graph(n) {};
	void Bellman_solve(int s, bellman_cost INF_COST) {
		for (auto& vv : v) vv.cost = INF_COST, vv.valid = false;
		v[s].cost = 0, v[s].valid = true;
		for (int i = 0; i + 1 < (int) v.size(); i++) {
			for (auto& x: edges) {
				if (v[x.from].cost == INF_COST) continue;
				v[x.to].cost = min(v[x.to].cost, v[x.from].cost + x.cost);
				v[x.to].valid = true;
			}
		}
		auto valid_check = [&](auto f, int pos) {
			if (!v[pos].valid) return;
			v[pos].valid = false;
			for (auto& y: e[pos]) {
				f(f, y.to);
			}
		};
		for (int i = 0; i < (int) v.size(); i++) {
			for (auto& x: e[i]) {
				if (v[i].cost == INF_COST) continue;
				if (v[x.to].cost > v[i].cost + x.cost) {
					valid_check(valid_check, x.to);
				}
			}
		}
	}
};

/*
template<class V, class E>
void Bellmanford(Graph<V, E>& G, int s, bellman_cost INF_COST)
{
}
*/

void ABC137_E() {
	int N, M, P;
	cin >> N >> M >> P;
	Bellmanford B(N);
	for (int i = 0; i < M; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		B.add_edge(a-1, b-1, P-c);
	}
	B.Bellman_solve(0, LLONG_MAX);
	if (B.v[N-1].valid) {
		cout << max(0LL, -B.v[N-1].cost) << endl;
	} else {
		cout << -1 << endl;
	}
}

int main() {
	ABC137_E();
}