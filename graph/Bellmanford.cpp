namespace bellman_n {
using u32 = uint_fast32_t;
#include "../for_include/has_shortest_path_graph_tag.cpp"
template<class Graph, class WEIGHT = typename Graph::WEIGHT_TYPE>
enable_if_t<has_shortest_path_graph_tag_v<Graph>> Bellmanford(Graph& G, u32 start, WEIGHT INF_COST) {
	for (u32 i = 0; i < G.size(); i++) {
		G.dist(i) = INF_COST;
		G.valid(i) = false;
	}
	auto& e = G.e;
	G.dist(start) = 0, G.valid(start) = 1;
	for (u32 i = 0; i + 1 < G.size(); i++) {
		for (u32 j = 0; j < G.size(); j++) {
			for (auto& x : e[j]) {
				if (G.dist(j) == INF_COST) continue;
				G.dist(x.to) = min(G.dist(x.to), G.dist(j) + x.weight);
				G.valid(x.to) = true;
			}
		}
	}
	auto valid_check = [&](auto&& f, int pos) {
		if (!G.valid(pos)) return;
		G.valid(pos) = false;
		for (auto& x: e[pos]) {
			f(f, x.to);
		}
	};
	for (u32 i = 0; i < G.size(); i++) {
		for (auto& x : e[i]) {
			if (G.dist(i) == INF_COST) continue;
			if (G.dist(x.to) > G.dist(i) + x.weight) {
				valid_check(valid_check, x.to);
			}
		}
	}
}
}
using bellman_n::Bellmanford;