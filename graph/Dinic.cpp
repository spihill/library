namespace dinic_n {
#include "../snippet/FlowGraph.cpp"
template<class F>
struct Dinic : public Graph<F> {
	const F FLOW_INF = numeric_limits<F>::max();
	vector<int> level;
	vector<int> iter;
// a:Vertex(|V|)
	Dinic(int n) : Graph<F>(n), level(n), iter(n) {}
	F dfs(int s, int t, F f) {
		if (s == t) return f;
		for (int& i = iter[s]; i < (int) this->e[s].size(); i++) {
			auto& x = this->e[s][i];
			if (x.cap == 0 || level[s] >= level[x.to]) continue;
			F d;
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
	F solve(int s, int t) {
		F res = 0;
		while (true) {
			bfs(s);
			if (level[t] < 0) return res;
			fill(iter.begin(), iter.end(), 0);
			for (F r = 1; r;) {
				r = dfs(s, t, FLOW_INF);
				res += r;
			}
		}
	}
};
}
template<class F> using dinic = dinic_n::Dinic<F>;