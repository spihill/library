namespace dijkstra_n {
using u32 = uint_fast32_t;
#include "../for_include/has_shortest_path_graph_tag.cpp"
template<class Graph, class WEIGHT = typename Graph::WEIGHT_TYPE>
enable_if_t<has_shortest_path_graph_tag_v<Graph>> Dijkstra(Graph& G, u32 start, WEIGHT INF_COST) {
	auto& e = G.e;
	for (u32 i = 0; i < G.size(); i++) {
		G.dist(i) = INF_COST;
		G.valid(i) = false;
	}
	using Q_T = pair<WEIGHT, int>;
	priority_queue<Q_T, vector<Q_T>, greater<>> q;
	q.emplace(WEIGHT(0), start);
	while (!q.empty()) {
		auto a = q.top(); q.pop();
		G.valid(a.second) = 1;
		if (a.first >= G.dist(a.second)) continue;
		G.dist(a.second) = a.first;
		for (auto& x : e[a.second]) {
			if (x.weight == INF_COST) continue;
			if (a.first + x.weight < G.dist(x.to)) q.emplace(a.first + x.weight, x.to);
		}
	}
}
}
using dijkstra_n::Dijkstra;