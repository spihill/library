namespace kruskal_n {
#include "../datastructure/UnionFind.cpp"
#include "../for_include/has_weighted_graph_tag.cpp"
using u32 = uint32_t;
using u64 = uint64_t;
constexpr u32 upper_bits(u64 x) {return x >> 32;}
constexpr u32 lower_bits(u64 x) {return static_cast<u32>(x & numeric_limits<u32>::max());}
template<class Graph, class WEIGHT = typename Graph::WEIGHT_TYPE>
enable_if_t<has_weighted_graph_tag_v<Graph>, WEIGHT> Kruskal(const Graph& G) {
	auto idx = G.idx;
	sort(idx.begin(), idx.end(), [&](u64 a, u64 b) {
		return G.e[upper_bits(a)][lower_bits(a)].weight < G.e[upper_bits(b)][lower_bits(b)].weight;
	});
	UnionFind u(G.size());
	WEIGHT res = 0;
	for (u64 i : idx) {
		if (u.unite(upper_bits(i), G.e[upper_bits(i)][lower_bits(i)].to)) res += G.e[upper_bits(i)][lower_bits(i)].weight;
	}
	return res;
}
}
using kruskal_n::Kruskal;