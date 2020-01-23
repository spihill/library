namespace prim_n {
#include "../for_include/has_weighted_graph_tag.cpp"
template<class Graph, class WEIGHT = typename Graph::WEIGHT_TYPE>
enable_if_t<has_weighted_graph_tag_v<Graph>, WEIGHT> Prim(Graph& G) {
	WEIGHT res = 0;
	vector<char> used(G.size(), 0);
	priority_queue<pair<WEIGHT, int>, vector<pair<WEIGHT, int>>, greater<>> q;
	q.emplace(0, 0);
	while (!q.empty()) {
		auto p = q.top(); q.pop();
		if (used[p.second] != 0) continue;
		used[p.second] = 1;
		res += p.first;
		for (auto& x : G.e[p.second]) {
			q.emplace(x.weight, x.to);
		}
	}
	return res;
}
}
using prim_n::Prim;