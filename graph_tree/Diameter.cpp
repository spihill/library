namespace diameter_n {
#include "../template/WeightedGraph.cpp"
#include "../for_include/has_weighted_graph_tag.cpp"
using u32 = uint_fast32_t;
template<class Graph, class WEIGHT = typename Graph::WEIGHT_TYPE>
WEIGHT Diameter(Graph& G) {
	auto dfs = [&](auto f, u32 start, u32& goal, u32 par = numeric_limits<u32>::max()) -> WEIGHT {
		goal = start;
		WEIGHT res = 0;
		for (auto& i: G.e[start]) {
			if (i.to == par) continue;
			u32 t;
			WEIGHT r = f(f, i.to, t, start);
			r += i.weight;
			if (r > res) {
				res = r;
				goal = t;
			}
		}
		return res;
	};
	u32 g;
	dfs(dfs, 0, g);
	return dfs(dfs, g, g);
}
}
using diameter_n::Diameter;