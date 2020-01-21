namespace kruskal_n {
#include "../datastructure/UnionFind.cpp"
#include "../for_include/has_weighted_graph_tag.cpp"
template<class Graph, class W = typename Graph::weight_type>
enable_if_t<has_weighted_graph_tag_v<Graph>, W> Kruskal(const Graph& G) {
	using u64 = uint64_t;
	using u32 = uint32_t;
	vector<u64> idx;
	for (size_t i = 0; i < G.size(); i++) {
		for (size_t j = 0; j < G.edge[i].size(); j++) {
			idx.push_back(static_cast<u64>(i) << 32 | j);
		}
	}
	sort(idx.begin(), idx.end(), [&](u64 a, u64 b) {
		return G.weight[a >> 32][a & numeric_limits<u32>::max()] < G.weight[b >> 32][b & numeric_limits<u32>::max()];
	});
	UnionFind u(G.size());
	W res = 0;
	for (u64 i : idx) {
		if (u.unite(i >> 32, G.edge[i >> 32][i & numeric_limits<u32>::max()])) res += G.weight[i >> 32][i & numeric_limits<u32>::max()];
	}
	return res;
}
}
using kruskal_n::Kruskal;