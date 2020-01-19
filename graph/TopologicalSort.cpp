/**
 * @title トポロジカルソート
 * @brief グラフが DAG であるとき、頂点のトポロジカル順序を求める。
 * @brief 戻り値は、トポロジカル順序に並んだ頂点番号の列。
 * @brief DAG でないときは戻り値は空の vector になる。
 * @brief AOJ では模範解を下のようなアルゴリズムで作っているらしく、Output が完全に一致する。
 */
namespace topological_sort_n {
#include "../template/UnWeightedGraph.cpp"
#include "../helper/tag.cpp"
template<class T> using graph = UnWeightedGraph<T>;
#include "../for_include/make_graph.cpp"
template<class T>
enable_if_t<has_graph_tag_v<graph<T>>, vector<int>> TopologicalSort(graph<T>& G) {
	const size_t V = G.size();
	auto& e = G.edge;
	vector<char> visited(V, 0);
	vector<int> res;
	auto dfs = [&](auto&& dfs, int v) -> void {
		visited[v] = true;
		for (auto& x : e[v]) {
			if (!visited[x]) dfs(dfs, x);
		}
		res.push_back(v);
	};
	for (size_t i = 0; i < V; i++) {
		if (!visited[i]) dfs(dfs, i);
	}
	if (res.size() < V) return vector<int>(0);
	reverse(res.begin(), res.end());
	return move(res);
}
} // namespace topological_sort_n
template<class T = long long> using graph = topological_sort_n::graph<T>;
using topological_sort_n::make_graph;
using topological_sort_n::TopologicalSort;