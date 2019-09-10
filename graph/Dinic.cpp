template<class T>
struct Graph
{
	struct Vertex{};
	struct Edge {
		int to;
		T cap;
		int rev;
		Edge(int x, T y, int z) : to(x), cap(y), rev(z) {}
	};
	int sz;
	vector<Vertex> v;
	vector<vector<Edge>> e;
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


template<class T>
struct Dinic : public Graph<T> {
	const int FLOW_INF = INT_MAX;
	vector<int> level;
	vector<int> iter;
// a:Vertex(|V|)
	Dinic(int n) : Graph<T>(n), level(n), iter(n) {}
// x:from y:to z:capacity
	void add_edge_dinic(int x, int y, T z) {
		this->add_edge(x, y, z, this->e[y].size());
		this->add_edge(y, x, 0, this->e[x].size()-1);
	}
	T dfs(int s, int t, T f) {
		if (s == t) return f;
		for (int& i = iter[s]; i < (int) this->e[s].size(); i++) {
			auto& x = this->e[s][i];
			if (x.cap == 0 || level[s] >= level[x.to]) continue;
			T d;
			if ((d = dfs(x.to, t, min(f, x.cap))) > 0) {
				x.cap -= d;
				this->e[x.to][x.rev].cap += d;
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
			for (auto y : this->e[a]) {
				if (y.cap > 0) q.push(make_pair(y.to, b+1));
			}
		}
	}
	T Dinic_solve(int s, int t) {
		T res = 0;
		while (true){
			bfs(s);
			if (level[t] < 0) return res;
			fill(iter.begin(), iter.end(), 0);
			T r;
			do {
				r = dfs(s, t, FLOW_INF);
				res += r;
			} while (r);
		}
	}
};