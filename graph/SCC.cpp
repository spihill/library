namespace scc_n{
#include "../template/UnWeightedGraph.cpp"
#include "../helper/tag.cpp"
template<class T> using graph = UnWeightedGraph<T>;
#include "../for_include/make_graph.cpp"
template<class Graph>
struct SCC {
	graph<long long> g, rg;
	vector<int> comp;
	SCC(Graph& g_) : g(g_.size()), rg(g_.size()), comp(g_.size()) {
		static_assert(has_graph_tag_v<Graph>);
		for (size_t i = 0; i < g_.size(); i++) {
			for (auto& x : g_.edge[i]) {
				g.add_edge(i, x);
				rg.add_edge(x, i);
			}
		}
	}
	const int& operator[](int i) { return comp[i];}
	void dfs(int n, vector<char>& used, stack<int>& order) {
		if (used[n]) return;
		used[n] = true;
		for (auto x : g.edge[n]) {
			dfs(x, used, order);
		}
		order.emplace(n);
	}
	void rdfs(int n, vector<int>& comp, int group) {
		if (comp[n] != -1) return;
		comp[n] = group;
		for (auto x : rg.edge[n]) rdfs(x, comp, group);
	}
	Graph build() {
		const size_t n = g.size();
		stack<int> order;
		vector<char> used(n, 0);
		for (size_t i = 0; i < n; i++) dfs(i, used, order);

		comp = vector<int>(n, -1);
		int group = 0;
		while (order.size()) {
			int i = order.top(); order.pop();
			if (comp[i] == -1) rdfs(i, comp, group++);
		}

		Graph res(group);
		for (size_t i = 0; i < n; i++) {
			for (auto& x : g.edge[i]) {
				int s = comp[i], t = comp[x];
				if (s == t) continue;
				res.add_edge(s, t);
			}
		}
		return res;
	}
};
} // scc_n
template<class T = long long> using graph = scc_n::graph<T>;
using scc_n::make_graph;
using scc_n::SCC;