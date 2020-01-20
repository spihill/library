/**
 * @title トポロジカルソート
 * @brief グラフが DAG であるとき、頂点のトポロジカル順序を求める。
 * @brief 戻り値は、トポロジカル順序に並んだ頂点番号の列。
 * @brief DAG でないときは戻り値は空の vector になる。
 * @brief AOJ では模範解を下のようなアルゴリズムで作っているらしく、Output が完全に一致する。
 */
namespace topological_sort_n {
#include "../helper/tag.cpp"
template<class Graph, class V = typename Graph::vertex_type>
enable_if_t<has_graph_tag_v<Graph>, vector<V>> TopologicalSort(Graph& G) {
	const size_t n = G.size();
	auto& e = G.edge;
	vector<char> visited(n, 0);
	vector<V> res;
	auto dfs = [&](auto&& dfs, int v) -> void {
		visited[v] = true;
		for (auto& x : e[v]) {
			if (!visited[x]) dfs(dfs, x);
		}
		res.push_back(Graph::restore(v));
	};
	for (size_t i = 0; i < n; i++) {
		if (!visited[i]) dfs(dfs, i);
	}
	if (res.size() < n) return vector<V>(0);
	reverse(res.begin(), res.end());
	return move(res);
}
} // namespace topological_sort_n
using topological_sort_n::TopologicalSort;