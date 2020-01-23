namespace scc_n{
using u32 = uint_fast32_t;
#include "../template/UnWeightedRevEdgeGraph.cpp"
#include "../for_include/has_graph_tag.cpp"
using super_graph = UnWeightedRevEdgeGraph;
struct SCC : super_graph {
	using EDGE = typename super_graph::EDGE_TYPE;
	using VERTEX = typename super_graph::VERTEX_TYPE;
	using graph = super_graph;
	vector<int> comp;
	SCC(u32 N) : super_graph(N), comp(N) {}
	template<class Graph>
	SCC(Graph& g_) : SCC(g_.size()) {
		static_assert(has_graph_tag_v<Graph>);
		construct_graph(g_);
	}
	const int& operator[](int i) { return comp[i];}
	void dfs(int n, vector<char>& used, stack<int>& order) {
		if (used[n]) return;
		used[n] = true;
		for (auto& x : this->e[n]) {
			dfs(x.to, used, order);
		}
		order.emplace(n);
	}
	void rdfs(int n, vector<int>& comp, int group) {
		if (comp[n] != -1) return;
		comp[n] = group;
		for (auto& x : this->re[n]) rdfs(x.to, comp, group);
	}
	graph build() {
		const u32 n = this->size();
		stack<int> order;
		vector<char> used(n, 0);
		for (u32 i = 0; i < n; i++) dfs(i, used, order);

		comp = vector<int>(n, -1);
		int group = 0;
		while (order.size()) {
			int i = order.top(); order.pop();
			if (comp[i] == -1) rdfs(i, comp, group++);
		}

		graph res(group);
		for (u32 i = 0; i < n; i++) {
			for (auto& x : this->e[i]) {
				int s = comp[i], t = comp[x.to];
				if (s == t) continue;
				res.add_edge(s, t);
			}
		}
		return res;
	}
private:
	template<class Graph>
	void construct_graph(const Graph& G) {
		for (u32 i = 0; i < G.size(); i++) {
			for (auto& x : G.e[i]) {
				this->e[i].push_back(x.to);
				this->re[x.to].push_back(i);
			}
		}
	}
};
SCC make_scc(u32 N) {
	return SCC(N);
}
} // scc_n
using scc_n::make_scc;
using scc_n::SCC;