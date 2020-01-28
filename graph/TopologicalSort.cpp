/**
 * @title トポロジカルソート
 * @brief グラフが DAG であるとき、頂点のトポロジカル順序を求める。
 * @brief 戻り値は、トポロジカル順序に並んだ頂点番号の列。
 * @brief DAG でないときは戻り値は空の vector になる。
 * @brief AOJ では模範解を下のようなアルゴリズムで作っているらしく、Output が完全に一致する。
 */
namespace topological_sort_n {
#include "../for_include/has_graph_tag.cpp"
using u32 = uint_fast32_t;
template<class Graph>
enable_if_t<has_graph_tag_v<Graph>, vector<u32>> TopologicalSort(const Graph& G) {
	const u32 n = G.size();
	auto& e = G.e;
	vector<char> visited(n, 0);
	vector<u32> res;
	auto dfs = [&](auto&& dfs, int v) -> void {
		visited[v] = true;
		for (auto& x : e[v]) {
			if (!visited[x.to]) dfs(dfs, x.to);
		}
		res.push_back(v);
	};
	for (u32 i = 0; i < n; i++) {
		if (!visited[i]) dfs(dfs, i);
	}
	if (res.size() < n) return vector<u32>(0);
	reverse(res.begin(), res.end());
	return move(res);
}
} // namespace topological_sort_n

using topological_sort_n::TopologicalSort;