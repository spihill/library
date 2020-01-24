/**
 * @title 最大流 (Ford-Fulkerson)
 * @brief 最大流を求める $O(Ef)$
 */
namespace fordfulkerson_n {
#include "../template/FlowGraph.cpp"
#include "../for_include/has_flow_graph_tag.cpp"
using u32 = uint_fast32_t;
template<class Graph, class CAPACITY = typename Graph::CAPACITY_TYPE>
enable_if_t<has_flow_graph_tag_v<Graph>, CAPACITY> FordFulkerson(Graph& G, u32 start, u32 goal) {
	constexpr CAPACITY FLOW_INF = numeric_limits<CAPACITY>::max();
	vector<char> used(G.size(), 0);
	auto dfs = [&](auto&& f, u32 s, u32 t, CAPACITY c) -> CAPACITY {
		if (used[s]) return 0;
		used[s] = true;
		if (s == t) return c;
		for (auto& x : G.e[s]) {
			if (x.capacity == 0) continue;
			CAPACITY res = f(f, x.to, t, min(c, x.capacity));
			if (res > 0) {
				x.capacity -= res;
				G.e[x.to][x.rev].capacity += res;
				return res;
			}
		}
		return 0;
	};
	CAPACITY res = 0;
	for (;;) {
		fill(used.begin(), used.end(), 0);
		CAPACITY r = dfs(dfs, start, goal, FLOW_INF);
		if (r == 0) break;
		res += r;
	}
	return res;
}
} // fordfulkerson_n
using fordfulkerson_n::FordFulkerson;