#include <bits/stdc++.h>

using namespace std;

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
	// from, to, cost
	template<class... Args>
	inline void add_edge(int pos, Args... args) {
		e[pos].emplace_back(args...);
	}
	inline int size() {
		return sz;
	}
};

struct Vertex{};
using vertex = Vertex;

struct Edge
{
	int to;
	int cap;
	int rev;
	Edge(int x, int y, int z) : to(x), cap(y), rev(z) {}
};

using edge = Edge;
using graph = Graph<vertex, edge>;


struct Dinic : public graph {
	const int FLOW_INF = INT_MAX;
	vector<int> level;
	vector<int> iter;
// a:Vertex(|V|)
	Dinic(int n) : graph(n), level(n), iter(n) {}
// x:from y:to z:capacity
	void add_edge_dinic(int x, int y, int z) {
		add_edge(x, y, z, e[y].size());
		add_edge(y, x, 0, e[x].size()-1);
	}
	int dfs(int s, int t, int f) {
		if (s == t) return f;
		for (int& i = iter[s]; i < (int) e[s].size(); i++) {
			auto& x = e[s][i];
			if (x.cap == 0 || level[s] >= level[x.to]) continue;
			int d;
			if ((d = dfs(x.to, t, min(f, x.cap))) > 0) {
				x.cap -= d;
				e[x.to][x.rev].cap += d;
				return d;
			}
		}
		return 0;
	}
	void bfs(int s) {
		fill(level.begin(), level.end(), -1);
		queue<pair<int, int>> q;
		q.push(make_pair(s, 0));
		while (!q.empty()) {
			auto x = q.front();
			q.pop();
			int a = x.first;
			int b = x.second;
			if (level[a] != -1) continue;
			level[a] = b;
			for (auto y : e[a]) {
				if (y.cap > 0) q.push(make_pair(y.to, b+1));
			}
		}
	}
	int Dinic_solve(int s, int t) {
		int res = 0;
		while (true){
			bfs(s);
			if (level[t] < 0) return res;
			fill(iter.begin(), iter.end(), 0);
			int r;
			do {
				r = dfs(s, t, FLOW_INF);
				res += r;
			} while (r);
		}
	}
};

void AOJ_GRL_6_A() {
	int n, m;
	cin >> n >> m;
	Dinic D(n);
	for (int i = 0; i < m; i++) {
		int u, v, c;
		cin >> u >> v >> c;
		D.add_edge_dinic(u, v, c);
	}
	cout << D.Dinic_solve(0, n-1) << endl;
}

int main() {
	AOJ_GRL_6_A();
}