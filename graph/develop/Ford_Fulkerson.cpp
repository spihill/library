struct Ford_Fulkerson {
	edges& v;
	vector<bool> used;
	int n;
	const int INF = INT_MAX;
// a:Vertex(|V|)
	Ford_Fulkerson(edges& a) : v(a) {
		n = a.size();
		used.resize(n);
	}
// x:from y:to z:capacity
	void add_edge(int x, int y, int z) {
		v.add_edge(edge(x, y, z, v[y].size()));
		v.add_edge(edge(y, x, 0, v[x].size()-1));
	}
	int dfs(int s, int t, int f) {
		if (used[s]) return 0;
		used[s] = true;
		if (s == t) return f;
		for (auto& x : v[s]) {
			if (x.cap == 0) continue;
			int ret = dfs(x.to, t, min(f, x.cap));
			if (ret > 0) {
				x.cap -= ret;
				v[x.to][x.rev].cap += ret;
				return ret;
			}
		}
		return 0;
	}
	int calc(int s, int t) {
		int res = 0;
		while (true){
			fill(used.begin(), used.end(), false);
			int r = dfs(s, t, INF);
			if (r == 0) break;
			res += r;
		}
		return res;
	}
};
/*
	Depends on
		- Edge_Cap_Rev
		- Edges_List
*/