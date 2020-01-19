namespace is_biparite_n {
#include "../template/UnWeightedGraph.cpp"
#include "../helper/tag.cpp"
template<class T> using graph = UnWeightedGraph<T>;
#include "../for_include/make_graph.cpp"
template<class T>
enable_if_t<has_graph_tag_v<graph<T>>, vector<pair<int, int>>> is_Biparite(graph<T>& G) {
	const int V = G.size();
	vector<pair<int, int>> res;
	auto& e = G.edge;
	vector<char> color(V, -1);
	int count[2] = {0, 0};
	auto dfs = [&] (auto f, int v, int c) {
		if (color[v] == c) return true;
		if (color[v] != -1) return false;
		color[v] = c;
		count[c]++;
		for (auto& x: e[v]) {
			if (!f(f, x, 1 - c)) return false;
		}
		return true;
	};
	for (int i = 0; i < V; i++) {
		if (color[i] == -1 && !dfs(dfs, i, 0)) return vector<pair<int, int>>(0);
		if (count[0]) res.emplace_back(count[0], count[1]);
		count[0] = count[1] = 0;
	}
	return res;
}
}
template<class T = long long> using graph = is_biparite_n::graph<T>;
using is_biparite_n::make_graph;
using is_biparite_n::is_Biparite;