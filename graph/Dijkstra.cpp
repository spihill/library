namespace dijkstra_n {
#include "../for_include/has_shortest_path_graph_tag.cpp"
template<class Graph, class V, class W = typename Graph::weight_type>
enable_if_t<has_shortest_path_graph_tag_v<Graph>> Dijkstra(Graph& g, V start, W INF_COST) {
	auto& dist = g.dist;
	auto& valid = g.valid;
	auto& e = g.edge;
	auto& w = g.weight;
	int s = Graph::index(start);
	fill(dist.begin(), dist.end(), INF_COST);
	fill(valid.begin(), valid.end(), 0);
	using Q_T = pair<W, int>;
	priority_queue<Q_T, vector<Q_T>, greater<>> q;
	q.emplace(0, s);
	while (!q.empty()) {
		auto a = q.top(); q.pop();
		assert(a.second < (int) g.size());
		valid[a.second] = 1;
		if (a.first >= dist[a.second]) continue;
		dist[a.second] = a.first;
		for (size_t i = 0; i < e[a.second].size(); i++) {
			if (w[a.second][i] == INF_COST) continue;
			if (a.first + w[a.second][i] < dist[e[a.second][i]]) q.emplace(a.first + w[a.second][i], e[a.second][i]);
		}
	}
}
}
using dijkstra_n::Dijkstra;