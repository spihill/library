#include <bits/stdc++.h>

using namespace std;

using dijkstra_cost = long long;

template<class V, class E>
struct Graph
{
	int sz;
	vector<V> v;
	vector<vector<E>> e;
	Graph(int n) : sz(n), v(n), e(n) {}
	template<class... Args>
	inline void assign_vertex(int pos, Args... args) {
		v[pos] = V(args...);
	}
	template<class... Args>
	inline void add_edge(int pos, Args... args) {
		e[pos].emplace_back(args...);
	}
	inline int size() {
		return sz;
	}
};

template<class T>
struct Vertex
{
	T cost;
	Vertex(T v1) : cost(v1) {}
	Vertex() {}
};
using vertex = Vertex<dijkstra_cost>;

template<class T>
struct Edge
{
	int to;
	T cost;
	Edge(int t, T c) : to(t), cost(c) {}
	Edge() {}
};
using edge = Edge<dijkstra_cost>;
using graph = Graph<vertex, edge>;

struct Dijkstra : public graph {
	Dijkstra(int n) : graph(n) {}
	void Dijkstra_solve(int s, dijkstra_cost INF_COST) {
		for (auto& vv : v) vv.cost = INF_COST;
		using Q_T = pair<dijkstra_cost, int>;
		priority_queue<Q_T, vector<Q_T>, greater<>> q;
		q.emplace(0, s);
		while (!q.empty()) {
			auto a = q.top();
			q.pop();
			if (a.first >= v[a.second].cost) continue;
			v[a.second].cost = a.first;
			for (auto& p : e[a.second]) {
				if (p.cost == INF_COST) continue;
				if (a.first + p.cost < v[p.to].cost) q.emplace(a.first + p.cost, p.to);
			}
		}
	}
};

void SoundHound2018_D() {
	int N, M, s, t;
	cin >> N >> M >> s >> t;
	s--;t--;
	Dijkstra G(N), G2(N);
	for (int i = 0; i < M; i++) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		a--;b--;
		G.add_edge(a, b, c);
		G.add_edge(b, a, c);
		G2.add_edge(a, b, d);
		G2.add_edge(b, a, d);
	}
	G.Dijkstra_solve(s, LLONG_MAX);
	G2.Dijkstra_solve(t, LLONG_MAX);
	vector<long long> ans(N);
	for (int i = 0; i < N; i++) {
		ans[i] = G.v[i].cost + G2.v[i].cost;
	}
	for (int i = N - 1; i > 0; i--) {
		ans[i-1] = min(ans[i], ans[i-1]);
	}
	for (int i = 0; i < N; i++) {
		cout << (long long) 1e15 - ans[i] << endl;
	}
}

int main() {
	SoundHound2018_D();
}