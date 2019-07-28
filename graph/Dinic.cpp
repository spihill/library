template<class T>
// O(|E||V|^2)
struct Dinic {
	const T FLOW_INF = INT_MAX;
	edges v;
	vector<int> level;
	vector<int> iter;
// a:Vertex(|V|)
	Dinic(int a) : level(a), iter(a) {
		v.init(a);
	}
// x:from y:to z:capacity
	void add_edge(int x, int y, T z) {
		v.add_edge(edge(x, y, z, v[y].size()));
		v.add_edge(edge(y, x, 0, v[x].size()-1));
	}
	T dfs(int s, int t, T f) {
		if (s == t) return f;
		for (int& i = iter[s]; i < (int) v[s].size(); i++) {
			auto& x = v[s][i];
			if (x.cap == 0 || level[s] >= level[x.to]) continue;
			T d;
			if ((d = dfs(x.to, t, min(f, x.cap))) > 0) {
				x.cap -= d;
				v[x.to][x.rev].cap += d;
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
			for (auto y : v[a]) {
				if (y.cap > 0) q.push(make_pair(y.to, b+1));
			}
		}
	}
	T calc(int s, int t) {
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