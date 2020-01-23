/**
 * @title 最大流 (Dinic)
 * @brief 最大流を求める $O(V^2E)$
 */
namespace dinic_n {
#include "../template/FlowGraph.cpp"
#include "../for_include/has_flow_graph_tag.cpp"
using u32 = uint_fast32_t;
template<class Graph, class CAPACITY = typename Graph::CAPACITY_TYPE>
enable_if_t<has_flow_graph_tag_v<Graph>, CAPACITY> Dinic(Graph& G, u32 start, u32 goal) {
	constexpr CAPACITY FLOW_INF = numeric_limits<CAPACITY>::max();
	vector<int> level(G.size());
	vector<u32> iter(G.size());
	auto dfs = [&](auto&& f, u32 s, u32 g, CAPACITY flow) -> CAPACITY {
		if (s == g) return flow;
		for (u32& i = iter[s]; i < G.e[s].size(); i++) {
			auto& to = G.e[s][i].to;
			auto& cap = G.e[s][i].capacity;
			auto& rev = G.e[s][i].rev;
			if (cap == 0 || level[s] >= level[to]) continue;
			CAPACITY d;
			if ((d = f(f, to, g, min(flow, cap))) > 0) {
				cap -= d;
				G.e[to][rev].capacity += d;
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
			for (auto& x : G.e[a]) {
				if (x.capacity > 0) q.push(make_pair(x.to, b+1));
			}
		}
	};
	CAPACITY res = 0;
	for (;;) {
		bfs(start);
		if (level[goal] < 0) return res;
		fill(iter.begin(), iter.end(), 0);
		for (CAPACITY r = 1; r;) {
			r = dfs(dfs, start, goal, FLOW_INF);
			res += r;
		}
	}
}
}
using dinic_n::Dinic;