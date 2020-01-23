namespace fibprim_n {
#include "../datastructure/FibHeapMap.cpp"
#include "../for_include/has_weighted_graph_tag.cpp"
using u32 = uint_fast32_t;
template<class Graph, class WEIGHT = typename Graph::WEIGHT_TYPE>
enable_if_t<has_weighted_graph_tag_v<Graph>, WEIGHT> FibPrim(Graph& G, u32 start = 0, const WEIGHT INF_COST = numeric_limits<WEIGHT>::max()) {
	auto& e = G.e;
	WEIGHT res = 0;
	vector<char> used(G.size(), 0);
	using heap = FibHeapMap<WEIGHT, u32, greater<>>;
	heap q;
	vector<typename heap::np> node(G.size(), nullptr);
	q.push(0, start);
	while (!q.empty()) {
		auto p = q.top(); q.pop();
		if (used[p.second]) continue;
		used[p.second] = true;
		res += p.first;
		for (auto& x : e[p.second]) {
			if (x.weight == INF_COST) continue;
			q.push(x.weight, x.to);
			if (!used[x.to]) {
				if (!node[x.to]) node[x.to] = q.push(x.weight, x.to);
				if (x.weight< node[x.to]->get_key()) q.prioritize(node[x.to], x.weight);
			}
		}
	}
	return res;
}
}
using fibprim_n::FibPrim;
// template<class W> using graph = fibprim_n::Edges<W>;
// namespace prim_n {
// #include "../for_include/has_weighted_graph_tag.cpp"
// template<class Graph, class WEIGHT = typename Graph::WEIGHT_TYPE>
// enable_if_t<has_weighted_graph_tag_v<Graph>, WEIGHT> Prim(Graph& G) {
// 	WEIGHT res = 0;
// 	vector<char> used(G.size(), 0);
// 	priority_queue<pair<WEIGHT, int>, vector<pair<WEIGHT, int>>, greater<>> q;
// 	q.emplace(0, 0);
// 	while (!q.empty()) {
// 		auto p = q.top(); q.pop();
// 		if (used[p.second] != 0) continue;
// 		used[p.second] = 1;
// 		res += p.first;
// 		for (auto& x : G.e[p.second]) {
// 			q.emplace(x.weight, x.to);
// 		}
// 	}
// 	return res;
// }
// }
// using prim_n::Prim;