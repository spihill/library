namespace warshall_floyd_n {
#include "../template/AllShortestPathGraph.cpp"
#include "../for_include/has_all_shortest_path_graph_tag.cpp"
template<class Graph, class WEIGHT = typename Graph::WEIGHT_TYPE>
enable_if_t<has_all_shortest_path_graph_tag_v<Graph>, bool> WarshallFloyd(Graph& G) {
	const WEIGHT inf = numeric_limits<WEIGHT>::max();
	const int n = G.size();
	auto& dist = G.dist;
	auto& valid = G.valid;
	auto& e = G.e;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			dist[i][j] = inf;
			valid[i][j] = false;
		}
		dist[i][i] = 0;
		valid[i][i] = true;
	}
	for (int i = 0; i < n; i++) {
		for (auto& d : e[i]) {
			dist[i][d.to] = d.weight;
			valid[i][d.to] = 1;
		}
	}
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (valid[i][k] && valid[k][j]) {
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
					valid[i][j] = 1;
				}
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (dist[i][i] < 0) valid[i][i] = 0;
	}
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (dist[i][k] != inf && dist[k][j] != inf) valid[i][j] = valid[i][j] && valid[i][k] && valid[k][j];
			}
		}
	}
	bool res = true;
	for (int i = 0; i < n; i++) {
		res = res && valid[i][i];
	}
	return res;
}
}
using warshall_floyd_n::WarshallFloyd;