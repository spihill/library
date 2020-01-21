/**
 * @title 最大流 (Dinic)
 * @brief 最大流を求める $O(V^2E)$
 */
namespace dinic_n {
#include "../template/FlowGraph.cpp"
#include "../for_include/has_flow_graph_tag.cpp"
template<class Graph, class T, class U, class C = typename Graph::capacity_type>
enable_if_t<has_flow_graph_tag_v<Graph>, C> Dinic(Graph& G, T Start, U Goal) {
	constexpr C FLOW_INF = numeric_limits<C>::max();
	size_t start = Graph::index(Start);
	size_t goal = Graph::index(Goal);
	vector<int> level(G.size());
	vector<size_t> iter(G.size());
	auto dfs = [&](auto&& f, size_t s, size_t g, C flow) -> C {
		if (s == g) return flow;
		for (size_t& i = iter[s]; i < G.edge[s].size(); i++) {
			auto& to = G.edge[s][i];
			auto& cap = G.capacity[s][i];
			auto& rev = G.revedge[s][i];
			if (cap == 0 || level[s] >= level[to]) continue;
			C d;
			if ((d = f(f, to, g, min(flow, cap))) > 0) {
				cap -= d;
				G.capacity[to][rev] += d;
				return d;
			}
		}
		return 0;
	};
	auto bfs = [&] (int s) -> void {
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
			for (size_t i = 0; i < G.edge[a].size(); i++) {
				if (G.capacity[a][i] > 0) q.push(make_pair(G.edge[a][i], b+1));
			}
		}
	};
	C res = 0;
	for (;;) {
		bfs(start);
		if (level[goal] < 0) return res;
		fill(iter.begin(), iter.end(), 0);
		for (C r = 1; r;) {
			r = dfs(dfs, start, goal, FLOW_INF);
			res += r;
		}
	}
}
}
using dinic_n::Dinic;