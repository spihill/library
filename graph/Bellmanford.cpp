namespace bellman_n {
#include "../for_include/has_shortest_path_graph_tag.cpp"
template<class Graph, class V, class W = typename Graph::weight_type>
enable_if_t<has_shortest_path_graph_tag_v<Graph>> Bellmanford(Graph& G, V Start, W INF_COST) {
	size_t start = Graph::index(Start);
	auto& dist = G.dist;
	auto& valid = G.valid;
	auto& edge = G.edge;
	auto& weight = G.weight;
	for (auto& d : dist) d = INF_COST;
	for (auto& v: valid) v = 0;
	dist[start] = 0, valid[start] = 1;
	for (size_t i = 0; i + 1 < G.size(); i++) {
		for (size_t j = 0; j < G.size(); j++) {
			for (size_t k = 0; k < edge[j].size(); k++) {
				if (dist[j] == INF_COST) continue;
				dist[edge[j][k]] = min(dist[edge[j][k]], dist[j] + weight[j][k]);
				valid[edge[j][k]] = true;
			}
		}
	}
	auto valid_check = [&](auto f, int pos) {
		if (!valid[pos]) return;
		valid[pos] = false;
		for (auto& y: edge[pos]) {
			f(f, y);
		}
	};
	for (size_t i = 0; i < G.size(); i++) {
		for (size_t j = 0; j < edge[i].size(); j++) {
			if (dist[i] == INF_COST) continue;
			if (dist[edge[i][j]] > dist[i] + weight[i][j]) {
				valid_check(valid_check, edge[i][j]);
			}
		}
	}
}
}
using bellman_n::Bellmanford;