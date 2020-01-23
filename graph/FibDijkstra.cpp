namespace fibdijkstra_n {
#include "../datastructure/FibHeapMap.cpp"
#include "../for_include/has_shortest_path_graph_tag.cpp"
using u32 = uint_fast32_t;
template<class Graph, class WEIGHT = typename Graph::WEIGHT_TYPE>
enable_if_t<has_shortest_path_graph_tag_v<Graph>> FibDijkstra(Graph& G, u32 start, WEIGHT INF_COST) {
	auto& e = G.e;
	for (u32 i = 0; i < G.size(); i++) {
		G.dist(i) = INF_COST;
		G.valid(i) = false;
	}
	using heap = FibHeapMap<WEIGHT, uint_fast32_t, greater<>>;
	heap q;
	vector<typename heap::np> node(G.size(), nullptr);
	q.push(0, start); G.dist(start) = 0;
	while (!q.empty()) {
		auto a = q.top(); q.pop();
		for (auto& p : e[a.second]) {
			if (p.weight == INF_COST) continue;
			G.valid(a.second) = 1;
			WEIGHT w = G.dist(a.second) + p.weight;
			if (w < G.dist(p.to)) {
				G.dist(p.to) = w;
				if (!node[p.to]) node[p.to] = q.push(w, p.to);
				q.prioritize(node[p.to], w);
			}
		}
	}
}
}
using fibdijkstra_n::FibDijkstra;